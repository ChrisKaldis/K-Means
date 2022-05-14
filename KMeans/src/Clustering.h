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

#endif /* CLUSTERING_H_ */
