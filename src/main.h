/*
 * main.h
 *
 *  Created on: Mar 9, 2020
 *      Author: Ian
 */

#ifndef MAIN_H_
#define MAIN_H_

#define WATER '~'
#define HIT '*'
#define MISS 'm'

#define CARRIER 'c'
#define BATTLESHIP 'b'
#define CRUISER 'r'
#define SUBMARINE 's'
#define DESTROYER 'd'

typedef struct {
	int numHits;
	int numMisses;
	int totalShots;
	double hitMissRatio;
} Stats;

struct Coordinate {
	int row;
	int column;
};

typedef struct {
	char symbol;
	Coordinate position;
} Cell;

#endif /* MAIN_H_ */
