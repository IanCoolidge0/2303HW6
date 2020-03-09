/*
 * BattleshipBoard.h
 *
 *  Created on: Mar 5, 2020
 *      Author: Ian
 */

#ifndef BATTLESHIPBOARD_H_
#define BATTLESHIPBOARD_H_

#include "WaterCraft.h"
#include "Production.h"

typedef struct {
	Symbol symbol;
	Coordinate position;
} Cell;

class WaterCraft;
class BattleshipBoard {
public:
	BattleshipBoard();
	virtual ~BattleshipBoard();

	void initializeGameBoard();
	void printGameBoard(bool showPegs);
	void putShipOnGameBoard(WaterCraft ship, Coordinate coord, int direction);
	void manuallyPlaceShipsOnGameBoard(WaterCraft ship[]);
	void randomlyPlaceShipsOnGameBoard(WaterCraft ship[]);
	void updateGameBoard(Coordinate coord);
	void checkBoundsOfCardinal(bool cardinals[], int bound, int direction);

	short checkShot(Coordinate target);

	bool isValidLocation(Coordinate coord, int direction, int length);
private:
	Cell gameBoard[ROWS][COLS];
};

#endif /* BATTLESHIPBOARD_H_ */
