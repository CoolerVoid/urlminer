#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alloca.h>
#include "mem_ops.h"
#include "string_ops.h"
#include "validate.h"


void extract_url(char *response,char *domain)
{
 int lenbuf=strlen(response)*sizeof(char),x=0;
 char *p=response;
 char *str=xmalloc(lenbuf+1);
 char *url=alloca(lenbuf),*act=p,*src=p;
 
 memset(str,0,lenbuf);
 p=RmSpace(p);
 memset(url,0,lenbuf-1);

//parse href=
 do{	
	if(p[0]=='h' && p[1]=='r'&& p[2]=='e' && p[4]=='=')
	{
		p+=6;

		do{
			str[x]=*p;
			p++;
			x++;
		} while((*p != '>' && *p != '"' && *p != '\'') && x != lenbuf);
		str[x]='\0';

        	url=validate_url(str,domain);
		printf("href = %s \n",url);

		x=0;
	}

	p++;

 }while(p[5]!='\0');



 memset(str,0,strlen(str));
 memset(url,0,strlen(url));

// parse action=
 do{

	if(act[0]=='a' && act[1]=='c'&& act[2]=='t' && act[6]=='=')
	{
		act+=8;

		do{
			str[x]=*act;
			act++;
			x++;
		} while((*act != '>' && *act != '"' && *act != '\'') && x != lenbuf);
                str[x]='\0';
		url=validate_url(str,domain);
		printf("action = %s \n",url);
//		memset(str,0,lenbuf);
//		memset(url,0,strlen(url));

		x=0;
	}

	act++;

 }while(act[7]!='\0');

 memset(str,0,strlen(str));
 memset(url,0,strlen(url));

 // parse src=
 do{	

	if(src[0]=='s' && src[1]=='r'&& src[2]=='c' && src[3]=='=')
	{
		src+=5;

		do{
			str[x]=*src;
			src++;
			x++;
		} while((*src != '>' && *src != '"' && *src != '\'' ) && x != lenbuf);
		str[x]='\0';

		url=validate_url(str,domain);
		printf("src = %s \n",url);
		memset(url,0,strlen(url));
		x=0;
	}

	src++;

 }while(src[4]!='\0');


 xfree((void **)&str);
}
