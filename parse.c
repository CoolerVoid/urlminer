#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem_ops.h"
#include "validate.h"

// extract_urls
void extract_urls(char * inputBuffer,char *domain)
{
// this trick is not common, i think use other thing at the future
	int href = *(int *)"href",lenbuf=strlen(inputBuffer),lendomain=strlen(domain),i=0,x=0;
 	char *p=NULL,*tmp=NULL,*s=xmalloc(lenbuf*sizeof(char)+1);

	p=inputBuffer;


		do{
 			x = *(int *)p;
			i=0;
//
//TODO: add "src=" to parse too
			if(x == href && (p[4] == '=' || (p[4] == ' ' && p[5] == '='  ) ))
			{	if(p[4]=='=')
					p += 6;
				else
					p+=7;
				do{
					s[i] = *p;
					p++;
					i++;
				}while( (*p != ' ' && *p != '>' && *p != '"') && i < lenbuf);

				s[i] = '\n';

					if(s)
					{ 
						tmp=validate_url(s,domain);
					 	if(tmp && tmp != NULL)	
						{
// TODO: add URL data at "Redis",hash table or SQLite, to make urls tree...
							printf("%s",tmp);
							memset(tmp,0,strlen(tmp));
						}
					}
				
				memset(s,0,lenbuf);
					
				
			}
			p++;
		}while(p[5] != '\0' && i < lenbuf);

	xfree((void **)&s);
}

