#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
//#include "mem_ops.h"
char *RmSpace(char* input); 
void *entropy_clock(void);
char *rand_str(char *dst, int size);
int char_type_counter(char *string,char type);
void chomp(char * str);
char *payload_injector(char * ptr,char * payload,int counter);
int strstr_regex(char *string, char *expression);

