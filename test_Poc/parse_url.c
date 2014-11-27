#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <alloca.h>  // some times i think, use alloca is a good idea...

void RemoveSpaces(char *str1)  
{
    char *str2; 
    str2=str1;  
    while (*str2==' ') str2++;  
    if (str2!=str1) memmove(str1,str2,strlen(str2)+1);  
}

// simple DFA to validate URL and path
char *validate_url(char* p, char *domain)
{
	unsigned char yych;

// ret same domain...
	if(strcasestr(p,"http"))
		if(strcasestr(p,domain))
	 		return p;
		else
			return "";
	char *gamma=p;
	yych = (unsigned char)*p;
	switch (yych) {
	case '.':
	case '/':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
	case '|':	goto yy3;
	default:	goto yy2;
	}
yy2:
	{ 
		int sizeurl=strlen(gamma)+strlen(domain)+200;
		char *newurl=alloca(sizeof(char)*sizeurl);
		memset(newurl,0,sizeurl-1);
		if(*(domain+(strlen(domain)-1))=='/')
		{
			if(gamma[0]=='/') 
				gamma++;
			strncpy(newurl,domain,sizeurl);
			strcat(newurl,gamma);
			
		} else {
			strncpy(newurl,domain,sizeurl );	
			if(gamma[0]!='/')
				strcat(newurl,"/");
			strcat(newurl,gamma);
		}
		return newurl; 
	}
yy3:
	++p;
	yych = (unsigned char)*p;
	switch (yych) {
	case '.':
	case '/':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
	case '|':	goto yy3;
	default:	goto yy2;
	}


}

// extract_urls
void extract_urls(char * inputBuffer,char *domain)
{
// this trick is not common, i think use other thing at the future
	int lenbuf=strlen(inputBuffer),lendomain=strlen(domain),i=0,x=0;
 	char *p=NULL,*tmp=NULL,*s=malloc(lenbuf*sizeof(char)+1);
	RemoveSpaces(inputBuffer);
	p=inputBuffer;

	
		do{
			i=0;
//
//TODO: add "src=" to parse too
			if( p[0]=='h' && p[1] == 'r' && p[2] == 'e' && p[3]=='f' && p[4] == '=' )
			{
				p += 6;
				
				do{
					s[i] = *p;
					p++;
					i++;
				}while( ( *p != '>' && *p != '"' && *p != '\'') && i < lenbuf);

				s[i] = '\n';

					if(s)
					{ 
						tmp=validate_url(s,domain);
					 	if(tmp && tmp != NULL)	
						{
							printf("href = %s \n",tmp);
							memset(tmp,0,strlen(tmp));
							tmp=NULL;
						}
					}
				
				memset(s,0,strlen(s));
					
			}

			if( strcasestr(p,"acti") && (p[6] == '=' ))
			{	if(p[6]=='=')
					p += 8;
				
				do{
					s[i] = *p;
					p++;
					i++;
				}while( (*p != ' ' && *p != '>' && *p != '"' && *p != '\'') && i < lenbuf);

				s[i] = '\n';

					if(s)
					{ 
						tmp=validate_url(s,domain);
					 	if(tmp && tmp != NULL)	
						{
							printf("action = %s\n",tmp);
							memset(tmp,0,strlen(tmp));
						}
					}
				
				memset(s,0,strlen(s));
			p++;	
			}

			if( strcasestr(p," src") && (p[4] == '=' ))
			{	if(p[4]=='=')
					p += 6;
				do{
					s[i] = *p;
					p++;
					i++;
				}while( (*p != ' ' && *p != '>' && *p != '"' && *p != '\'') && i < lenbuf);

				s[i] = '\n';

					if(s)
					{ 
						tmp=validate_url(s,domain);
					 	if(tmp && tmp != NULL)	
						{
							printf("src = %s\n",tmp);
							memset(tmp,0,strlen(tmp));
						}
					}
				
				memset(s,0,strlen(s));
					
				
			}

			p++;
		}while(*p != '\0' && i < lenbuf);

	free(s);
	s=NULL;
}

int main(void)
{
	char *response="<a href =\"/test/algo\" >   \n<a href = \"/abra/cadabra/site.php\"> \n < href='teste/5003'> \n <form action = 'kaboom.php?remove'> ";

	extract_urls(response,"http://www.vulcan.com.br");
  return 0;
}
