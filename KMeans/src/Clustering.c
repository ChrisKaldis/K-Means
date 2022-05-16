/*
 * Clustering.c
 *
 *  Created on: 14 May 2022
 *      Author: Chris Kaldis
 */

#include <math.h>
#include <stdlib.h>

#include "Clustering.h"

//Lloyd's algorithm K-means
/*
 * Input:
 * 		patterns:	2D array with the data
 * 		c:		  	initial patterns used as centers
 * 		numP:	  	number of patterns used
 *
 */
void KMeans( double patterns[][LENGTH], double c[CENTERS][LENGTH], int numP ) {

    double **d = (double **)malloc(numP*sizeof(double*));
    for (int i=0; i<numP; i++)
        d[i] = (double *)malloc(CENTERS*sizeof(double));
    int *a = (int *)malloc(numP*sizeof(int));

    double oldSSE;
    double tmpSSE;
    double SSE = INFINITY;

    do {

        tmpSSE = 0;
        oldSSE = SSE;
        // #pragma omp parallel for private(j) num_threads(threads)
        for ( int i = 0; i < numP; i++ ) {
            for ( int j = 0; j < CENTERS; j++ )
              d[i][j] = distEucl( patterns[i], c[j] );
            a[i] = argMin( d[i] ) ;
        }
        //
        double y[CENTERS][LENGTH];
        double z[CENTERS][LENGTH];
        initialTmpArray(y,z);
        //update step
        for ( int i = 0; i < numP; i++ ) {
            int index = a[i];
            for ( int k = 0; k < LENGTH; k++ ) {
                y[index][k] += patterns[i][k];
                z[index][k] += 1.0;
            }
            tmpSSE += distEucl( patterns[i], c[a[i]] );
        }
        for ( int j = 0; j < CENTERS; j++ ) {
            for ( int k = 0; k < LENGTH; k++ ) {
                z[j][k] = fmax(z[j][k],1.0);
                c[j][k] = y[j][k]/z[j][k];
            }
        }
        SSE = tmpSSE;

    } while ( SSE < oldSSE ) ;

    for ( int i = 0; i < numP; i++ )
        free(d[i]);
    free(d);
    free(a);

    return ;
}

// Argminimum
int argMin( double d[CENTERS] ) {

    int index = 0;
    double min = d[0];

    for ( int i = 1; i < CENTERS; i++ ) {
        if (min > d[i]) {
            min = d[i];
            index = i;
        }
    }

    return index;
}

// Calculates the Eucledean distance between a pattern and a centroid.
double distEucl( double x[LENGTH], double c[LENGTH] ) {

	double distance = 0;

    for ( int i = 0; i < LENGTH; i++ )
        distance += pow( (x[i] - c[i]), 2.0 );

    return ( pow(distance, 0.5) );
}

// Fill two arrays with 0.0, they used for recalculated the means.
void initialTmpArray( double y[CENTERS][LENGTH], double z[CENTERS][LENGTH] ) {

	for ( int j = 0; j < CENTERS; j++ ) {
		for ( int k = 0; k < LENGTH; k++ ) {
			y[j][k] = 0.0;
			z[j][k] = 0.0;
		}
	}

	return ;
}

int classifyPattern( double pattern[LENGTH], double c[CENTERS][LENGTH] ) {

	int class;
	double distances[CENTERS];

	for ( int i = 0; i < CENTERS; i++ ) {
		distances[i] = distEucl( pattern, c[i] );
	}

	class = argMin( distances ) + 1;

	return class;
}
