#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <alloca.h>  // some times i think, use alloca is a good idea...

struct MemoryStruct {
  char *memory;
  size_t size;
};

// libcurl callback to write response
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
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

	p=inputBuffer;


		do{
			i=0;
//
//TODO: add "src=" to parse too
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
// TODO: add URL data at "Redis",hash table or SQLite...
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
// TODO: add URL data at "Redis",hash table or SQLite...
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
// TODO: add URL data at "Redis",hash table or SQLite...
							printf("src = %s",tmp);
							memset(tmp,0,strlen(tmp));
						}
					}
				
				memset(s,0,lenbuf);
					
				
			}

			p++;
		}while(p[5] != '\0' && i < lenbuf);

	free(s);
	s=NULL;
}

int main(void)
{
  CURL *curl;
  CURLcode res;
  struct MemoryStruct chunk;

  chunk.memory = malloc(1);  
  chunk.size = 0;    

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if(curl) {

    curl_easy_setopt(curl, CURLOPT_URL, "http://www.vulcan.com.br/Contato.aspx");

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }
    else {
      	printf("%s\n",chunk.memory);
	extract_urls(chunk.memory,"http://www.vulcan.com.br");
    }

    curl_easy_cleanup(curl);

    if(chunk.memory)
    {	
      free(chunk.memory);
      chunk.memory=NULL;
    }

    curl_global_cleanup();
  }
  return 0;
}
