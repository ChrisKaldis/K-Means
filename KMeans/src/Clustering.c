/*
 * Clustering.c
 *
 *  Created on: 14 May 2022
 *      Author: Chris Kaldis
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

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

        //Fill two arrays with 0.0, they used for recalculated the means
        double y[CENTERS][LENGTH] = {{0.0}};
        double z[CENTERS][LENGTH] = {{0.0}};
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

// Calculates the Eucledean distance between a pattern and a centroid.
double distEucl( double x[LENGTH], double c[LENGTH] ) {

	double distance = 0;

    for ( int i = 0; i < LENGTH; i++ )
        distance += pow( (x[i] - c[i]), 2.0 );

    return ( pow(distance, 0.5) );
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

// Reads the patterns from a file and stores the data & class.
void readFile( char *filename, double data[SIZE][LENGTH], char class[SIZE][NAME] ) {

    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp) {
		puts("Error, file not found");
        exit(1);
	}
	for ( size_t i = 0; i < SIZE; i++ ) {
		fscanf(fp, "%lf,%lf,%lf,%lf,%s", &data[i][0], &data[i][1], &data[i][2], &data[i][3], &class[i][0]);
	}
    fclose(fp);

    return ;
}

// Prints an array[N][M]
void printArray( double array[SIZE][LENGTH] ) {

    for ( size_t i = 0; i < SIZE; i++ ) {
        for ( size_t j = 0; j < LENGTH; j++ )
            printf("%lf ", array[i][j]);
        putchar('\n');
    }
    putchar('\n');

    return ;
}

// Prints the name of classes (class[SIZE][NAME])
void printClass( char array[SIZE][NAME] ) {

    for ( size_t i = 0; i < SIZE; i++ ) {
    	printf("%s\n", array[i]);
    }
    putchar('\n');

    return ;
}

void printMeans( double array[CENTERS][LENGTH] ) {

	for ( size_t i = 0; i < CENTERS; i++ ) {
		for ( size_t j = 0; j < LENGTH; j++ )
			printf("%lf ", array[i][j]);
		putchar('\n');
	}
	putchar('\n');

	return ;
}

// Naive way function needs rewritting.
int initialCenters( double means[CENTERS][LENGTH], char class[SIZE][NAME], double data[SIZE][LENGTH] ) {

	int index[3] = {0, 55, 140};

	for ( size_t i = 0; i < CENTERS; i++ ) {
		for ( size_t j = 0; j < LENGTH; j++ ) {
			means[i][j] = data[index[i]][j];
		}
	}

	return 0;
}

// naive way
void error( double means[CENTERS][LENGTH], double data[SIZE][LENGTH] ) {

	double distances[SIZE][CENTERS];

	for ( int i = 0; i < SIZE; i++ ) {
		for ( int j = 0; j < CENTERS; j++ ) {
			distances[i][j] = distEucl( data[i], means[j] );
		}
	}

	int class;
	int errorC = 0;
	for ( int i = 0; i < SIZE; i++ ) {
		class = argMin(distances[i]) + 1;
		// class 1 is from 0 to 49
		if ( (i < 50) && (class != 1) )
			errorC += 1;
		// class 2 is from 50 to 99
		if ( (i > 49) && (i < 100) && (class != 2) )
			errorC += 1;
		if ( (i > 100) && (class != 3) )
			errorC += 1;
	}
	printf("Wrong classifications: %d\nTotal patterns: 149 (%f)", errorC, errorC/(float) SIZE);

	return ;
}
