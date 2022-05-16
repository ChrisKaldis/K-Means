/*
 * Clustering.h
 *
 *  Created on: 14 May 2022
 *      Author: Chris Kaldis
 */

#ifndef CLUSTERING_H_
#define CLUSTERING_H_

#define SIZE 150
#define LENGTH 4
#define CLASS 3
#define CENTERS 3
#define NAME 17

void KMeans( double patterns[][LENGTH], double centers[CENTERS][LENGTH], int numP );

double distEucl( double x[LENGTH], double c[LENGTH] );
int argMin( double[CENTERS] );
void initialTmpArray( double y[CENTERS][LENGTH], double z[CENTERS][LENGTH] );
int classifyPattern( double pattern[LENGTH], double c[CENTERS][LENGTH] );

void readFile( char *filename, double data[SIZE][LENGTH], char class[SIZE][NAME] );
void printArray( double array[SIZE][LENGTH] );
void printClass( char array[SIZE][NAME] );
void printMeans( double array[CENTERS][LENGTH] );
int initialCenters( double means[CENTERS][LENGTH], char class[SIZE][NAME], double data[SIZE][LENGTH] );
void error( double means[CENTERS][LENGTH], double data[SIZE][LENGTH] );

#endif /* CLUSTERING_H_ */
