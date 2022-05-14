/*
 ============================================================================
 Name        : KMeans.c
 Author      : Chris Kaldis
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "Clustering.h"

int main( void ) {

	double patterns[SIZE][LENGTH];
	char class[SIZE][NAME];
	double means[CENTERS][LENGTH];

	readFile( "iris.data", patterns, class );
	initialCenters( means, class, patterns);
	printMeans(means);
	KMeans(patterns, means, SIZE);
	printMeans(means);
	error(means, patterns);

	return EXIT_SUCCESS;
}

// Reads the patterns from a file and stores the data & class.
void readFile( char *filename, double data[SIZE][LENGTH], char class[SIZE][NAME] ) {

    FILE *fp;
    fp = fopen(filename, "r");
    if (fp) {
        for ( size_t i = 0; i < SIZE; i++ ) {
            for ( size_t j = 0; j < LENGTH; j++ )
                fscanf(fp,"%lf,", &data[i][j]);
            fscanf(fp,"%s", &class[i][0]);
        }
    }
    else {
        puts("Error, file not found");
        exit(1);
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

// Naive way function needs rewritting.
int initialCenters( double means[CENTERS][LENGTH], char class[SIZE][NAME], double data[SIZE][LENGTH] ) {

	int index[3];
	index[0] = 0;
	index[1] = 55;
	index[2] = 140;

	for ( size_t i = 0; i < CENTERS; i++ ) {
		for ( size_t j = 0; j < LENGTH; j++ ) {
			means[i][j] = data[index[i]][j];
		}
	}

	return 0;
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
		else if ( (i > 49) && (i < 100) && (class != 2) )
			errorC += 1;
		else if ( (i > 100) && (class != 3) )
			errorC += 1;
	}
	printf("Wrong classifications: %d\nTotal patterns: 149 (%f)", errorC, errorC/(float) SIZE);

	return ;
}
