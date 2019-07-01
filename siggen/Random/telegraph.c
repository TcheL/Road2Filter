/*
 *                            COPYRIGHT
 *
 *  telegraph.c
 *  Copyright (C) 2014 Exstrom Laboratories LLC
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  A copy of the GNU General Public License is available on the internet at:
 *  http://www.gnu.org/copyleft/gpl.html
 *
 *  or you can write to:
 *
 *  The Free Software Foundation, Inc.
 *  675 Mass Ave
 *  Cambridge, MA 02139, USA
 *
 *  Exstrom Laboratories LLC contact:
 *  stefan(AT)exstrom.com
 *
 *  Exstrom Laboratories LLC
 *  Longmont, CO 80503, USA
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Compile: gcc -lm -o telegraph telegraph.c

int main( int argc, char *argv[] )
{
  if( argc < 3 )
    {
      printf("usage: %s s a\n", argv[0]);
      printf("  Reads random numbers from stdin and outputs a telegraph process\n");
      printf("  s = sampling rate\n");
      printf("  a = amplitude\n");
      exit( -1 );
    }

  double s = strtod(argv[1], NULL);
  double a = -strtod(argv[2], NULL);
  double x;
  unsigned long int i, m;

  while(scanf("%lf", &x)!=EOF){
    m = s*x;
    for(i=0; i<m; ++i) printf("%lf\n", a);
    a = -a;}

  return(0);
}
