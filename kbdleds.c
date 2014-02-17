Copyright 2003 Joel Kenny

This file is part of kbdleds.

kbdleds is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

kbdleds is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with kbdleds; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

/*
 * System includes
 */ 

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/kd.h>
#include <unistd.h>
#include <time.h>

/*
 * Custom Includes
 */

#include "leds.h"

/*
 * #define macros
 */

#define VERSION_STR "0.3"
#define PROGRAM_NAME "kbdleds"

/*
 * Prototypes
 */

void nanosecond_wait( long ms );

void disp_version();
void disp_help();
int open_con();

/*
 * Function Implementations
 */

int open_con()
{
	int con = init_console();
	if( con < 0 )
	{
		printf( "%s","Unable to open /dev/console!\n" );
		exit( 1 );
	}
	return con;
}

void nanosecond_wait( long ms )
{
 struct timespec st;
 st.tv_sec = ms / 1000;
 st.tv_nsec = ms % 1000 * 1000000;
 nanosleep( &st,NULL );
}

void disp_help()
{
	disp_version();
	printf( "Usage: %s [options]\n", PROGRAM_NAME );
	puts( "Options:" );
 	puts( "-v               Prints the version number to the screen." );
	puts( "-h               Prints this screen." );
	puts( "-g               Prints the current keyboard LED status." );
	puts( "-s<number>       Causes the keys to be set according to <number>, which" );
	puts( "                 is used to designate keys. <number> should be between 1" );
	puts( "                 and 7 inclusive." );
	puts( "-a<number>       Same as -s, but does a logical and with the current status of" );
	puts( "                 the LEDs." );
	puts( "-o<number>       Same as -s, but does a logical or with the current status of" );
	puts( "                 the LEDs." );
	puts( "-x<number>       Same as -s, but does a logical xor with the current status of" );
	puts( "                 the LEDs." );
	puts( "-d               Loops through the pattern forever." );
	puts( "-D               Forks into the background and loops through the pattern forever." );
	puts( "-w<number>       Waits <number> milliseconds before executing the next command." );

}

void disp_version()
{
	printf( "%s %s by Joel Kenny\n",PROGRAM_NAME,VERSION_STR );
}

int main( int argc, char* argv[] )
{
	int con;
	short daemon_mode = 0;
	int c;
	pid_t my_pid;
	do
	{
		c = 0;
		optind = 0;
		while( ( c = getopt( argc, argv, "Ddvhgs:a:o:x:w:" ) ) != EOF )
		{
			switch( c )
			{
				case 'v':
					disp_version();
					break;
				case 'h':
					disp_help();
					break;

				case 'g':
					con = open_con();
					printf( "%i\n",(int)get_leds( con )&7 );
					close( con );
					break;
				case 's':
					con = open_con();
					set_leds( con,atol(optarg)&7 );
					close( con );
					break;

				case 'a':
					con = open_con();
					and_leds( con,atol(optarg)&7 );
					close( con );
					break;

				case 'o':
					con = open_con();
					or_leds( con,atol(optarg)&7 );
					close( con );
					break;

				case 'x':
					con = open_con();
					xor_leds( con,atol(optarg)&7 );
					close( con );
					break;

				case 'D':
					daemon_mode = 1;
					my_pid = fork();
					if( my_pid != -1 && my_pid != 0 )
						exit( 0 );
					break;
				case 'd':
					daemon_mode = 1;
					break;
				case 'w':
					nanosecond_wait( atol(optarg) );
					break;
			}
		}
	}while( daemon_mode == 1 );
	return 0;
}
