/*
 *                            COPYRIGHT
 *
 *  bwbp - Butterworth bandpass filter coefficient calculator
 *  Copyright (C) 2003, 2004, 2005, 2006 Exstrom Laboratories LLC
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
 *
 *  http://www.gnu.org/copyleft/gpl.html
 *
 *  or you can write to:
 *
 *  The Free Software Foundation, Inc.
 *  675 Mass Ave
 *  Cambridge, MA 02139, USA
 *
 *  You can contact Exstrom Laboratories LLC via Email at:
 *
 *  info(AT)exstrom.com
 *
 *  or you can write to:
 *
 *  Exstrom Laboratories LLC
 *  P.O. Box 7651
 *  Longmont, CO 80501, USA
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "iir.h"

int main( int argc, char *argv[] )
{
    int n;            // filter order
    int sff;          // scale flag: 1 to scale, 0 to not scale ccof
    int i;            // loop variables
    double f1f;       // lower cutoff frequency (fraction of pi)
    double f2f;       // upper cutoff frequency (fraction of pi)
    double sf;        // scaling factor
    double *dcof;     // d coefficients
    int *ccof;        // c coefficients
    FILE *fp;         // output file

    if( argc < 6 )
    {
	printf("\nbwbp calculates Butterworth bandpass filter coefficients\n");
	printf("\nUsage: bwbp n fc1 fc2 sf outfile\n");
	printf("  n = order of the filter\n");
	printf("  fc1 = lower cutoff frequency as a fraction of Pi [0,1]\n");
	printf("  fc2 = upper cutoff frequency as a fraction of Pi [0,1]\n");
        printf("  sf = 1 to scale c coefficients for normalized response\n");
        printf("  sf = 0 to not scale c coefficients\n");
	printf("  outfile = output file name\n");
	return(-1);
    }

    n = atoi( argv[1] );
    f1f = atof( argv[2] );
    f2f = atof( argv[3] );
    sff = atoi( argv[4] );

    /* calculate the d coefficients */
    dcof = dcof_bwbp( n, f1f, f2f );
    if( dcof == NULL )
    {
        perror( "Unable to calculate d coefficients" );
        return(-1);
    }

    /* calculate the c coefficients */
    ccof = ccof_bwbp( n );
    if( ccof == NULL )
    {
        perror( "Unable to calculate c coefficients" );
        return(-1);
    }

    sf = sf_bwbp( n, f1f, f2f ); /* scaling factor for the c coefficients */

    /* create the filter coefficient file */
    fp = fopen(argv[5], "w");
    if( fp == 0 )
    {
	perror( "Unable to open output file" );
	return(-1);
    }

    /* Output the file header */
    fprintf( fp, "# Butterworth bandpass filter coefficients.\n" );
    fprintf( fp, "# Produced by bwbp.\n" );
    fprintf( fp, "# Filter order: %d\n", n );
    fprintf( fp, "# Lower cutoff freq.: %1.15lf\n", f1f );
    fprintf( fp, "# Upper cutoff freq.: %1.15lf\n", f2f );
    fprintf( fp, "# Scaling factor: %1.15lf\n", sf );

    /* Output the c coefficients */
    fprintf( fp, "%d\n", 2*n+1 );    // number of c coefficients
    if( sff == 0 )
        for( i = 0; i <= 2*n; ++i)
	    fprintf( fp, "%d\n", ccof[i] );
    else
        for( i = 0; i <= 2*n; ++i)
	    fprintf( fp, "%1.15lf\n", (double)ccof[i]*sf );

    /* Output the d coefficients */
    fprintf( fp, "%d\n", 2*n+1 );  /* number of d coefficients */
    for( i = 0; i <= 2*n; ++i )
	fprintf( fp, "%1.15lf\n", dcof[i] );

    fclose( fp );
    free( dcof );
    free( ccof );
}
