/*
 * Production.h
 *
 *  Created on: Mar 5, 2020
 *      Author: Ian
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_

#define ROWS 10
#define COLS 10
#define NUM_OF_SHIPS 5

#include <stdio.h>
#include <conio.h>
#include <random>
#include <time.h>
#include <string.h>

typedef enum {
	WATER,
	MISS,
	HIT,
	CARRIER,
	BATTLESHIP,
	CRUISER,
	SUBMARINE,
	DESTROYER
} Symbol;

struct Coordinate {
	int row;
	int column;
};

class Production {
public:
	Production();
	virtual ~Production();

	bool prod(int argc, char* argv[]);

	void welcomeScreen();
	void systemMessage(char *message);

	bool isWinner(int player);
	Coordinate generatePosition(int direction, int length);

	bool convertStringToPosition(Coordinate position[], char* stringPosition, int length);
	Coordinate getTarget();

	int getRandomNumber(int lowest, int highest);
private:
	int hits1, hits2;
};

#endif /* PRODUCTION_H_ */
