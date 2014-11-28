/*
Author:Antonio Costa aka " Cooler_ "
contact: c00f3r[at]gmail[dot]com


    Copyright (C) 2012 Url-Miner authors,
    
    This file is part of Url-Miner
    
    0d1n is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    0d1n is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.



What this IT ?
Recursive Web Bot to get URLs

need libcurl,lib sqlite3 to run

$ sudo apt-get install libcurl-dev sqlite3-dev
if rpm distro
$ sudo yum install libcurl-devel sqlite3-devel
$ make
$./urlminer


*/
#include <stdio.h> 
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/resource.h>
#include "web.h"
#include "validate.h"

void init_banner_odin()
{
 puts(
".     .       .  .   . .   .   . . . .  +  .  +.      \n"
"  .     .  :     .    .. :. ........ .... ......  ..   \n"
"       .  .   .    .  :.:. _'.^ .^ ^.  '.. :'....  \n"
"    .  :       .  .  .:../:            . .^  :.:\\.  \n"
"        .   . :: +. :.:/: .   .    .        . . .:\\    \n "
" .  :    .     . _ :::/:               .  ^ .  . .:\\    \n"
"  .. . .   . - : :.:./.                        .  .:\\   \n"
"  .      .     . :..|:                    .  .  ^. .:|   \n"
"    .       . : : ..||        .                . . !:|   \n"
"  .     . . . ::. ::\\(                           . :|   \n"
" .   .     : . : .:.|. 000000              .1010010::|  \n"
"  :.. .  :-  : .:  ::|.0101000           ...0000100 :|   \n"
" .  .  .  ..  .  .. :\\ 00010001          :00011000 :/   \n"
"  .        .+ :: : -.:\\ 00010001       . 01010001.:/   \n"
"    .  .+   . . . . :.:\\. 1001010       0011000..:/    \n"
"      :: . . . . ::.:..:.\\           .   .   ..:/      \n"
"   .   .   .  .. :  -::::.\\.       | |     . .:/       \n"
"      .  :  .  .  .-:.':.::.\\             ..:/        \n"
" .      -.   . . . .: .:::.:.\\.           .:/        \n" 
".   .   .  :      : ....::_:..:\\  .___.  :/         \n"
"   .   .  .   .:. .. .  .: :.:.:\\       :/        \n"
"     +   .   .   : . ::. :.:. .:.|\\  .:/|        \n"
"     .         +   .  .  ...:: ..|  --.:|        \n"
".      . . .   .  .  . ... :..:.........(  ..            \n"
" .   .       .      :  .   .: ::/  .  .::] \n"
".   .  . _  .  .    _   .   .   . . .. .....\n" 
" _ _ ___| |   _____|_|___ ___ ___  . + .......\n"
"| | |  _| |  |     | |   | -_|  _| . . . . ..\n"
"|___|_| |_|  |_|_|_|_|_|_|___|_|  . . . . .+. .\n"
". . . .+ .. .. .+ .. .. + .... .+ .... . .. .+ .\n"       
 YELLOW
 "...:::URL-MINER:::... \njust another web bot to extract URLs \n\n"
 LAST
 "--host :	 	Target to make recursive crawling\n"
 "--depth :	 	Define depth of URL paths \n"
 "--reject :     	Regex to reject URL\n"
 "--cookie :     	Set Cookie  param\n"
 "--cookie_jar:  	Cookie jar file to load\n"
 "--log :	 	Output of result\n"
 "--UserAgent :	 	Custom UserAgent\n"
 "--CA_certificate :	Load CA certificate to work with SSL\n"
 "--SSL_version :	choice SSL version  \n	1 = TLSv1\n	2 = SSLv2\n	3 = SSLv3\n"
 "--threads : 		Number of threads to use, default is 4\n"
 "--timeout :		Timeout to wait Response\n"
 "--proxy :   		Proxy_address:port to use single proxy tunnel\n	example: format [protocol://][user:password@]machine[:port]\n"
 "--proxy-rand :   	Use proxy list to use random proxy per Request\n	example: format [protocol://][user:password@]machine[:port]\n"
YELLOW
 "\nEnable-options-args:\n"
LAST
CYAN
 "Coded by Cooler_\n c00f3r[at]gmail[dot]com\n "
 );
 puts(LAST);
}

static struct option long_options[] =
{
	{"host", required_argument, NULL, 'h'},
	{"depth", required_argument, NULL, 'd'},
	{"reject", required_argument, NULL, 'r'},
	{"cookie", required_argument, NULL, 'f'},
	{"cookie_jar", required_argument, NULL, 'c'},
	{"log", required_argument, NULL, 'o'},
	{"UserAgent", required_argument, NULL, 'u'},
	{"CA_certificate", required_argument, NULL, 's'},
	{"SSL_version", required_argument, NULL, 'V'},
	{"threads", required_argument, NULL, 't'},
 	{"timeout", required_argument, NULL, 'T'}, 
 	{"proxy", required_argument, NULL, '1'}, 
 	{"proxy-rand", required_argument, NULL, '2'},
	{NULL, 0, NULL, 0}
};


int 
main(int argc, char ** argv)
{
 char c;
 char *pack[14]; 
 short y=13;

 	no_write_coredump ();
 	load_signal_alarm ();


	if(argc < 3) 
	{
		init_banner_miner();
		DEBUG(" Need more arguments.\n");
		exit(0);
	}
 

 	while(y>-1)
 	{
  		pack[y]=NULL;
  		y--;
 	}

 	opterr = 0;

 	while((c = getopt_long(argc, argv, "h:d:r:f:c:i:o:u:s:t:T:1:2:V",long_options,NULL)) != -1)
  		switch(c) 
  		{
// Host
   			case 'h':
    				
				if ( strnlen(optarg,256)<= 128 )
				{
    					pack[0] = optarg;
					validate_hostname(pack[0]);
    					printf("Host: %s \n",pack[0]);
    					
				} else {
					DEBUG("Error \nArgument Host very large \n");
					exit(1);
				}
				break;
// depth
			case 'd':
				if ( strnlen(optarg,2)<= 1 )
				{
    					pack[1] = optarg;
    					printf("Payloads: %s \n",optarg);
    					
				} else {
					DEBUG("Error \nArgument depth is very large  \n");
					exit(1);
				}
				break;

   			case 'r':
				if ( strnlen(optarg,256)<= 64 )
				{
    					pack[3] = optarg;
				} else {

					DEBUG("Error \nArgument Reject is very large  \n");
					exit(1);
				}
    				break;

   			
   			case 'c':
				if ( strnlen(optarg,256)<= 64 )
				{
    					pack[3] = optarg;
				} else {

					DEBUG("Error \nArgument cookie jar file is very large  \n");
					exit(1);
				}
    				break;



   			case 'i':
				if ( strnlen(optarg,256)<= 64 )
				{
    					pack[13] = optarg;
				} else {

					DEBUG("Error \nArgument cookie is very large  \n");
					exit(1);
				}
    				break;




   			case 'o':
				if ( strnlen(optarg,256)<= 128 )
				{
    					pack[5] = optarg;
    					printf("Log file: %s \n",optarg);
    				} else {
					DEBUG("Error \nArgument Log file very large \n");
					exit(1);
				}
				break;
   
   			case 'u':
				if ( strnlen(optarg,256)<= 128 )
				{
    					pack[6] = optarg;
    				} else {	
					DEBUG("Error \nArgument user agent is very large  \n");
					exit(1);
				}
				break;
 
   			case 's':
				if ( strnlen(optarg,256)<= 128 )
				{
    					pack[7] = optarg;
				} else {	
					DEBUG("Error \nArgument ca cert file name is very large  \n");
					exit(1);
				}
				break;

 
   			case 't':
				if ( strnlen(optarg,4)<= 2 )
				{
    					pack[11] = optarg;
				} else {	
					DEBUG("Error \nArgument threads is very large  \n");
					exit(1);
				}
				break;
 
   			case 'T':
				if ( strnlen(optarg,4)<= 3 )
				{	
    					pack[8] = optarg;
				} else {	
					DEBUG("Error \nArgument timeout is very large need 3 digit  \n");
					exit(1);
				}
				break;

// proxy single
   			case '1':
				if ( strnlen(optarg,47)<= 48 )
				{	
    					pack[17] = optarg;
				} else {	
					DEBUG("Error \nArgument proxy is very large \n");
					exit(1);
				}
				break;
//proxy list
   			case '2':
				if ( strnlen(optarg,63)<= 64 )
				{	
    					pack[18] = optarg;
				} else {	
					DEBUG("Error \nArgument proxy list is very large \n");
					exit(1);
				}
				break;

 			
 				
   			case 'V':
				if ( strnlen(optarg,3)<= 1 )
				{	
    					pack[9] = optarg;
				} else {	
					DEBUG("Error \nArgument SSL version one digit example 1,2 or 3 : \n1 is TLSv1\n2 is SSLv2\n3 is SSLv3\n 0 is default\n");
					exit(1);
				}
				break;

   			case '?':
    				if(optopt == 'h' || optopt == 'p' || optopt == 'f' || optopt == 'c' || optopt == 'P' || optopt == 'o' || optopt=='s') 
    				{
     					init_banner_odin();
     					puts(RED);
     					DEBUG("Option -%c requires an argument.\n", optopt); 
     					puts(LAST);
     					exit(1);
    				}
				break;
  		}



 	start_crawling(pack);
	
	

 	exit(0);
}

