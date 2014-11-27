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
		int sizeurl=strlen(gamma)+strlen(domain)*5;
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

	//	free(newurl);

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

int char_type_counter(char *string,char type)
{
	int counter=0;
 
	while(*string != '\0')
	{
		if(*string==type) 
			counter++;
		string++;
	}
  
	return counter;
}

// to remove blank
char *RmSpace(char* input)                                                  
{
	int i=0,j=0,len=strlen(input),buf=len-char_type_counter(input,' ');
	char *output=NULL;
	output = malloc(buf*sizeof(char)+1);

	while (i!=len)                       
	{
		if (input[i]!=' ')                                                  
			output[j]=input[i];                                            
		else
			j--;   
		i++;
		j++;                                                      
	}

	output[j] ='\0';

	free(output);

	return output;                                                     
}

void extract_url(char *response,char *domain)
{
 int lenbuf=strlen(response)*sizeof(char),x=0;
 char *p=response;
 char *str=malloc(lenbuf+1);
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



 free(str);

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
	extract_url(chunk.memory,"http://www.vulcan.com.br");
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
