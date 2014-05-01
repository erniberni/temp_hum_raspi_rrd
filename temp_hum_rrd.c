/*
 * serial.c:
 *	Example program to read bytes from the Serial line
 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>     /* atol */

#include <wiringSerial.h>

int main ()
{
  int fd ;

  if ((fd = serialOpen ("/dev/ttyAMA0", 115200)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

// Loop, getting and printing characters
  char ds[35]="dies ist ein Test";
  char *bar = ds;
  char *nodeID_str, *temp_str, *humidity_str, *supplyV_str;	
  int charcounter=0;

  for (;;)
  {
    int char1;
    if ((char1 = serialGetchar(fd)) > 0)
    {
      if (char1 != '\n') {
        ds[charcounter]=char1;
        charcounter++;
      }
      else {
        ds[charcounter]='\0';
        charcounter=0;
        printf("%s\n", bar);
        nodeID_str = strtok(bar, "\t");
        supplyV_str = strtok(NULL, "\t");
        temp_str = strtok(NULL, "\t");
        humidity_str = strtok(NULL, "\t");
	unsigned int btime = atoi(strtok(NULL, "\t"));
	printf("Time since boot = %i\n", btime);
	unsigned long rectime = atol(strtok(NULL, "\t"));
	printf("Time recorded = %ld\n", rectime);
	unsigned int difftime = atoi(strtok(NULL, "\t"));
	printf("Time since last = %i\n", difftime);
	char tmp[255];
	sprintf(tmp,"/usr/bin/rrdupdate /home/pi/rrd/sensor%s.rrd -t temp:hum:batt N:%s:%s:%s",nodeID_str,temp_str,humidity_str,supplyV_str); 
	printf("Ergebnis %s\n", tmp);
	system(tmp);
      }
    }
  }
}

