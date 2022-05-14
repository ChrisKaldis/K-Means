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

void readFile( char *filename, double data[SIZE][LENGTH], char class[SIZE][NAME] );
void printArray( double array[SIZE][LENGTH] );
void printClass( char array[SIZE][NAME] );
void printMeans( double array[CENTERS][LENGTH] );
int initialCenters( double means[CENTERS][LENGTH], char class[SIZE][NAME], double data[SIZE][LENGTH] );

int main(void) {

	double patterns[SIZE][LENGTH];
	char class[SIZE][NAME];
	double means[CENTERS][LENGTH];

	readFile( "iris.data", patterns, class );
	initialCenters( means, class, patterns);
	printMeans(means);
	KMeans(patterns, means, SIZE);
	printMeans(means);

	return EXIT_SUCCESS;
}

// Reads the patterns from a file and stores the data & class.
void readFile( char *filename, double data[SIZE][LENGTH], char class[SIZE][NAME] ) {

    FILE *fp;
    fp = fopen( filename, "r" );
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
