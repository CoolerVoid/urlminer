#include "string_ops.h"
#include "mem_ops.h"


// to remove blank
char *RmSpace(char* input)                                                  
{
	int i=0,j=0,len=strlen(input),buf=len-char_type_counter(input,' ');
	char *output=NULL;
	output = xmalloc(buf*sizeof(char)+1);

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

	xfree((void **)&output);

	return output;                                                     
}


void *entropy_clock(void)
{
	double cpu_time;
	struct timeval tv;

	cpu_time = ((double) clock()) / CLOCKS_PER_SEC;
	gettimeofday(&tv, NULL);
	srandom((getpid() << 16) ^ tv.tv_sec ^ tv.tv_usec ^ (int)cpu_time);
  	return NULL;	
}


char *rand_str(char *dst, int size)
{
	static const char text[] =	"abcdefghijklmnopqrstuvwxyz"                     
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	entropy_clock();

	int i, len = random() % (size - 1);
  
	if( !len ) 
		len=8;
 
	for ( i=0; i<len; ++i )
		dst[i] = text[random() % (sizeof text - 1)];

   	dst[i] = '\0';

	return dst;
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


void chomp(char * str)
{
 
	while (*str) 
	{
		if ( *str == '\n' || *str == '\r' ) 
		{
			*str = 0;
			return;
		}
		str++;
	}
  
}

char *payload_injector(char * ptr,char * payload,int counter)
{
	char *new=xmalloc((strlen(ptr)+strlen(payload)+2)*sizeof(char));
	short i=0,x=1;
	memset(new, 0,sizeof(char)*(strlen(ptr)+strlen(payload)+1));

	while(*ptr != '\0')
	{
		if(*ptr == '^')
		{
			if(counter==x)
			{
				strncat(new,payload,strlen(payload));
				i+=strlen(payload);
			}
			x++;
		} 
		else 
		{ 
			*(new+i)=*ptr;
			i++;
		}
		ptr++;
	}

	return new;
}


int match_test(const char *string,const char *expression)
{
	const char *err;
	int errofs=0,offset=0;
	int ovector[100];

	pcre *re = pcre_compile(expression, 0, &err, &errofs, NULL);
	if (re == NULL) 
	{
		fprintf(stderr, " regex compilation failed\n");
		exit(EXIT_FAILURE);
	}
	const int rc = pcre_exec(re, NULL, string, strlen(string), offset, 0, ovector, array_elements(ovector));
	pcre_free(re);

	return rc > 0;

}


