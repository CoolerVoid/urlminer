#include "html_entities.h"
#include "mem_ops.h"

char* html_tbl = "<>\"\\'";    
char* repl_tbl[] = { "&lt;", "&gt;", "&quot;", "\\\\", "&lsquo;" };

int get_entity(char c) 
{
	char* ptr = html_tbl;
	unsigned idx = 0;

	while (*ptr) 
	{
 		if (*ptr == c)
 			return idx;
		ptr++;
		idx++;
	}
	
 	return -1;
}

char* html_entities(char* text) 
{
	char* ptr = text, *ret=NULL;
	unsigned retsize = 1;
	
 	ret = xrealloc(ret, retsize);
	
	memset(ret, 0, retsize);
	
	while (*ptr) 
	{
		char c = *ptr;
		int repl_idx = 0;

		if((repl_idx = get_entity(c)) != -1) 
		{
 			char* repl_str = repl_tbl[repl_idx];

			retsize += strlen(repl_str)+1;
			ret = xrealloc(ret, retsize);
			strncat(ret, repl_str,retsize); 
		} else {
			retsize++;
			ret = xrealloc(ret, retsize+1);
			sprintf(ret,"%s%c",ret,c); 
		}		
		ptr++;
	}
	
	return ret;
}


