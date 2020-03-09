/*
 * BattleshipBoard.cpp
 *
 *  Created on: Mar 5, 2020
 *      Author: Ian
 */

#include "BattleshipBoard.h"

BattleshipBoard::BattleshipBoard() {
	// TODO Auto-generated constructor stub

}

BattleshipBoard::~BattleshipBoard() {
	// TODO Auto-generated destructor stub
}

void BattleshipBoard::initializeGameBoard() {
	int i = 0, j = 0;

	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++) {
			gameBoard[i][j].symbol          = WATER;
			gameBoard[i][j].position.row    = i;
			gameBoard[i][j].position.column = j;
		}
}

void BattleshipBoard::printGameBoard(bool showPegs) {
	int i = 0, j = 0;

	printf ("  0 1 2 3 4 5 6 7 8 9\n");

	for (i = 0; i < ROWS; i++) {
		printf ("%d ", i);

		for (j = 0; j < COLS; j++) {
			if (showPegs)
				printf ("%c ", gameBoard [i][j].symbol);
			else {
				switch (gameBoard [i][j].symbol) {
					case HIT:   printf ("%c ", HIT);   break;
					case MISS:  printf ("%c ", MISS);  break;
					case WATER:
					default:    printf ("%c ", WATER); break;
				}
			}
		}

		putchar ('\n');
	}
}

void BattleshipBoard::putShipOnGameBoard(WaterCraft ship, Coordinate coord, int direction) {
	int i = ship.getLength() - 1;

	for (i = 0; i < ship.getLength(); i++) {
		if (direction == 0)
			gameBoard [coord.row][coord.column + i].symbol = ship.getSymbol();
		else /* VERTICAL */
			gameBoard [coord.row + i][coord.column].symbol = ship.getSymbol();
	}
}

void BattleshipBoard::manuallyPlaceShipsOnGameBoard(WaterCraft ship[]) {
	char       stringPosition[11] = "";
	int        i = 0, j = 0;

	Coordinate position[5];
	bool    isValid = false;

	fflush (stdin);

	for (i = 0; i < NUM_OF_SHIPS; i++) {

		while (true) {
			system ("cls");
			printGameBoard (true);
			printf ("> Please enter the %d cells to place the %s across (no spaces):\n", ship[i].getLength(), ship[i].getName().c_str());
			printf ("> ");
			scanf ("%s", stringPosition);

			Production* prod = new Production();
			/* convertStringtoPosition returns false if unsuccessful */
			if (prod->convertStringToPosition (position, stringPosition, ship[i].getLength())) {

				isValid = true;

				for (j = 0; j < ship[i].getLength(); j++) {

					if (gameBoard[position[j].row][position[j].column].symbol == WATER) {
						gameBoard[position[j].row][position[j].column].symbol = ship[i].getSymbol();
					} else {
						isValid = false;
						printf ("> Invalid input!\n");

						if (j != 0)
							while (j >= 0) {
								gameBoard[position[j].row][position[j].column].symbol = WATER;
								j--;
							}

						break;
					}
				}
			} else {
				isValid = false;
				printf ("> Invalid input!\n");
			}
			delete prod;

			if (isValid == true) break;
		}

	}
}

bool BattleshipBoard::isValidLocation(Coordinate coord, int direction, int length) {
	int i = length - 1;
	bool isValid = true;

	for (i = 0; isValid && i < length; i++) {
		if (direction == 0) {
			if (gameBoard [coord.row][coord.column + i].symbol != WATER &&
				(coord.column + i) < COLS)
				isValid = false;
		} else { /* VERTICAL */
			if (gameBoard [coord.row + i][coord.column].symbol != WATER &&
				(coord.row + i) < ROWS)
				isValid = false;
		}
	}

	return isValid;
}
