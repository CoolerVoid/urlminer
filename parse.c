#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem_ops.h"
#include "validate.h"

// extract_urls
void extract_urls(char * inputBuffer,char *domain)
{
	int lenbuf=strlen(inputBuffer),lendomain=strlen(domain),i=0,x=0;
 	char *p=NULL,*tmp=NULL,*s=xmalloc(lenbuf*sizeof(char)+1);

	p=inputBuffer;


		do{
			i=0;
			if( strcasestr(p,"href") && (p[4] == '=' || (p[4] == ' ' && p[5] == '='  ) ))
			{	if(p[4]=='=')
					p += 6;
				else
					p+=7;
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
							printf("href = %s",tmp);
							memset(tmp,0,strlen(tmp));
						}
					}
				
				memset(s,0,lenbuf);
					
				
			}

			i=0;
			if( strcasestr(p,"acti") && (p[6] == '=' || (p[6] == ' ' && p[7] == '='  ) ))
			{	if(p[6]=='=')
					p += 8;
				else
					p+=9;
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
							printf("action = %s",tmp);
							memset(tmp,0,strlen(tmp));
						}
					}
				
				memset(s,0,lenbuf);
					
				
			}

			i=0;
			if( strcasestr(p," src") && (p[4] == '=' || (p[4] == ' ' && p[5] == '='  ) ))
			{	if(p[4]=='=')
					p += 6;
				else
					p+=7;
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
							printf("src = %s",tmp);
							memset(tmp,0,strlen(tmp));
						}
					}
				
				memset(s,0,lenbuf);
					
				
			}




			p++;
		}while(p[5] != '\0' && i < lenbuf);

	xfree((void **)&s);
}

