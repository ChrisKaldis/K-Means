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
	printf("\n");
	KMeans(patterns, means, SIZE);
	printMeans(means);
	error(means, patterns);
	double pattern[LENGTH];
	pattern[0] = 5.1;
	pattern[1] = 3.5;
	pattern[2] = 1.4;
	pattern[3] = 0.2;
	int pattern1 = classifyPattern(pattern, means);
	printf("\n class:%d \n",pattern1);

	return EXIT_SUCCESS;
}

