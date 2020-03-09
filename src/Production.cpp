/*
 * Production.cpp
 *
 *  Created on: Mar 5, 2020
 *      Author: Ian
 */

#include "Production.h"

Production::Production() :
	hits1(0),
	hits2(0) {
	// TODO Auto-generated constructor stub
	srand(time(NULL));
}

Production::~Production() {
	// TODO Auto-generated destructor stub
}

bool Production::prod(int argc, char* argv[]) {
	return false;
}

void Production::welcomeScreen() {
	printf ("XXXXX   XXXX  XXXXXX XXXXXX XX     XXXXXX  XXXXX XX  XX XX XXXX\n");
	printf ("XX  XX XX  XX   XX     XX   XX     XX     XX     XX  XX XX XX  XX\n");
	printf ("XXXXX  XX  XX   XX     XX   XX     XXXX    XXXX  XXXXXX XX XXXX\n");
	printf ("XX  XX XXXXXX   XX     XX   XX     XX         XX XX  XX XX XX\n");
	printf ("XXXXX  XX  XX   XX     XX   XXXXXX XXXXXX XXXXX  XX  XX XX XX\n");
	printf ("\n\n");
	printf ("RULES OF THE GAME:\n");
	printf ("1. This is a two player game.\n");
	printf ("2. Player 1 is you and Player 2 is the computer.\n");
	printf ("3. Player 1 will be prompted if user wants to manually input coordinates\n");
	printf ("   for the game board or have the computer randomly generate a game board\n");
	printf ("4. There are five types of ships to be placed by longest length to the\n");
	printf ("   shortest; [c] Carrier has 5 cells, [b] Battleship has 4 cells, [r] Cruiser\n");
	printf ("   has 3 cells, [s] Submarine has 3 cells, [d] Destroyer has 2 cells\n");
	printf ("5. The computer randomly selects which player goes first\n");
	printf ("6. The game begins as each player tries to guess the location of the ships\n");
	printf ("   of the opposing player's game board; [*] hit and [m] miss\n");
	printf ("7. First player to guess the location of all ships wins\n\n");
}

void Production::systemMessage(char* message) {
	char ch = '\0';

	do {
		printf("%s", message);
	} while ((ch = getch()) != '\r');
}

bool Production::isWinner(int player) {
	bool isWin = false;

	if(player == 0 && hits1 == 17) {
		isWin = true;
	}

	if(player == 1 && hits2 == 17) {
		isWin = true;
	}

	return isWin;
}

Coordinate Production::generatePosition(int direction, int length) {
	Coordinate position;

	if (direction == 0) {
		position.row    = getRandomNumber (0, ROWS);
		position.column = getRandomNumber (0, COLS - length);
	} else { /* VERTICAL */
		position.row    = getRandomNumber (0, ROWS - length);
		position.column = getRandomNumber (0, COLS);
	}

	return position;
}

bool Production::convertStringToPosition(Coordinate* position, char* stringPosition, int length) {
	bool flag = true;
	int i = 0, j = 0, k = 1;

	/* checks if length of input is good */
	if (strlen (stringPosition)/2 == (unsigned int) length) {
		/* loops through the length of the ship */
		for (i = 0; i < length && flag; i++) {
			/* checks if each cell is a digit */
			if (isdigit (stringPosition[j]) && isdigit (stringPosition[k])) {
				position[i].row    = stringPosition[j] - '0';
				position[i].column = stringPosition[k] - '0';

				j += 2;
				k += 2;
			} else {
				flag = false;
			}
		}
	} else {
		flag = false;
	}

	return flag;
}

Coordinate Production::getTarget() {
	Coordinate target;

	fflush (stdin);

	printf ("> Enter Target (ex. > 3 4):\n");
	printf ("> ");
	scanf ("%d %d", &target.row, &target.column);

	return target;
}

int Production::getRandomNumber(int lowest, int highest) {
	if (lowest == 0)
		return rand () % ++highest;

	if (lowest > 0)
		return rand () % ++highest + lowest;

	return 0;
}
