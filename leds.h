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
	

int init_console();
long int get_leds( int console );

int set_leds( int console, long int state );
int and_leds( int console, long int state );
int or_leds ( int console, long int state );
int xor_leds( int console, long int state );

