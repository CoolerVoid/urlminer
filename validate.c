#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/resource.h>
#include <errno.h> 
#include <sys/types.h>
#include <unistd.h>
#include <curl/curl.h>

#include "validate.h"
#include "mem_ops.h"
#include <alloca.h>



// block ctrl+c 
void No_Pause_Scan ()
{
	DEBUG("\n When start Scan\n You Cannot be terminated using Ctrl+C or Ctrl+Z...\n Wait task ends... press <enter> to continue... \n");
	getchar();
	fflush(stdout);
}

void no_write_coredump (void) 
{
  	struct rlimit rlim;
   
	rlim.rlim_cur = 0; 
	rlim.rlim_max = 0; 
	setrlimit(RLIMIT_CORE, &rlim);

}

void load_signal_alarm (void)
{
 	struct sigaction sigIntHandler;

   	sigIntHandler.sa_handler = No_Pause_Scan;
   	sigemptyset(&sigIntHandler.sa_mask);
   	sigIntHandler.sa_flags = 0;

	if(sigemptyset(&sigIntHandler.sa_mask)!=0)
	{
		DEBUG("Error at signal");
		exit(1);
	}

   	if(sigaction(SIGINT, &sigIntHandler, NULL)!=0)
	{
		DEBUG("Error at signal");
		exit(1);
	}

   	if(sigaction(SIGTSTP, &sigIntHandler, NULL)!=0)
	{
		DEBUG("Error at signal");
		exit(1);
	}

   	if(sigaction(SIGQUIT, &sigIntHandler, NULL)!=0)
	{
		DEBUG("Error at signal");
		exit(1);
	}

}

void validate_hostname(const char *hostname)
{
	CURL *curl=NULL;
	CURLcode res;
 
	curl = curl_easy_init();

	if(curl) 
	{
		curl_easy_setopt(curl, CURLOPT_URL, hostname);
		curl_easy_setopt(curl, CURLOPT_HEADER, 1 );
                curl_easy_setopt(curl, CURLOPT_NOBODY, 1 );
                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1 );
		res = curl_easy_perform(curl);
 
		if(CURLE_OK != res) 
		{
			char choice;

			DEBUG("Error validating hostname");
			printf("Do you want to continue (y/N)? ");
			if(scanf("%1c", &choice) == EOF)
				choice = 'n';

			if(choice != 'y' && choice != 'Y')
			{
				curl_easy_cleanup(curl);
				exit(1);
			}
		}

		curl_easy_cleanup(curl);
  	}
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
