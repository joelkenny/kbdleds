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

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/kd.h>

#include "leds.h"

int init_console()
{
	return open("/dev/console", 0);
}

long int get_leds( int console )
{
	long int led = 0;
	if( ioctl( console, KDGETLED, &led ) < 0 )
		return -1;
	led = led&7;
	return led;
}

int set_leds( int console, long int state )
{
	return ioctl( console, KDSETLED, state&7);
}

int and_leds( int console, long int state )
{
	return ioctl( console, KDSETLED, state&7&get_leds(console) );
}

int or_leds ( int console, long int state )
{
	return ioctl( console, KDSETLED, (state|get_leds(console))&7);
}

int xor_leds( int console, long int state )
{
	return ioctl( console, KDSETLED, (state^get_leds(console))&7);
}
