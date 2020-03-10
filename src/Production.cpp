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
	Stats players[2] = {
			{0, 0, 0, 0.0},
			{0, 0, 0, 0.0}
	};

	BattleshipBoard* playerOneGameBoard = new BattleshipBoard();
	BattleshipBoard* playerTwoGameBoard = new BattleshipBoard();

	Coordinate target;
	Coordinate targetTemp;
	Coordinate targetOrigin;
	Coordinate targetAI;

	WaterCraft* ship[NUM_OF_SHIPS];
	ship[0] = new WaterCraft('c', 5, "Carrier");
	ship[1] = new WaterCraft('b', 4, "Battleship");
	ship[2] = new WaterCraft('r', 3, "Cruiser");
	ship[3] = new WaterCraft('s', 3, "Submarine");
	ship[4] = new WaterCraft('d', 2, "Destroyer");

	bool huntMode = true;
	bool targetMode = false;
	bool flipper = true;
	bool cardinals[4] = {true, true, true, true};
	bool hasAShipSunked = false;

	short sunkShip[2][NUM_OF_SHIPS] = {
		{5, 4, 3, 3, 2},
		{5, 4, 3, 3, 2}
	};

	short player = 0;
	short shot = 0;
	int option = 0;
	int north = 0, south = 0, east = 0, west = 0;

	int i = 0;
	int counter = 1;

	char shipSymbol = '\0';

	std::ofstream outStream;
	outStream.open("outputFile.txt");

	/* Start of Program */

	welcomeScreen ();
	systemMessage("\t\t\t\tHit <ENTER> to continue!\n");
	system ("cls");

	playerOneGameBoard->initializeGameBoard();
	playerTwoGameBoard->initializeGameBoard();

	printf("> Please select from the following menu:\n");
	printf("> [1] Manually\n");
	printf("> [2] Randomly\n");
	printf("> Enter Option: ");
	scanf("%d", &option);

	switch(option) {
	case 1:
		playerOneGameBoard->manuallyPlaceShipsOnGameBoard(ship);
		break;
	case 2:
		playerOneGameBoard->randomlyPlaceShipsOnGameBoard(ship);
		break;
	}

	playerTwoGameBoard->randomlyPlaceShipsOnGameBoard(ship);
	printf("> Player 2 (Computer's) board has been generated.\n");

	player = getRandomNumber(0, 1);
	printf("> Player %d has been randomly selected to go first.\n", player + 1);
	systemMessage ("> Hit <ENTER> to continue!\n");
	system ("cls");

	while(true) {
		outStream << "Player " << (player + 1) << "'s turn." << std::endl;

		switch(player) {
		case 0:
			printf("> Player 2's Board:\n");
			playerTwoGameBoard->printGameBoard(false);
			printf("> PLAYER 1'S TURN\n");

			do {
				target = getTarget();
				shot = playerTwoGameBoard->checkShot(target);

				if(shot == -1)
					printf("> Try inputting another target!\n");
			} while(shot == -1);

			shipSymbol = playerTwoGameBoard->gameBoard[target.row][target.column].symbol;
			break;
		case 1:
			printf("Player 1's Board:\n");
			playerOneGameBoard->printGameBoard(true);
			printf("> COMPUTER'S TURN\n");

			if(hasAShipSunked) {
				hasAShipSunked = false;
				targetMode = false;
				huntMode = true;
			}

			if(targetMode) {
				target = targetAI;

				do {
					if(cardinals[0])
						target.row = north;
					else if(cardinals[1])
						target.row = south;
					else if(cardinals[2])
						target.column = west;
					else if(cardinals[3])
						target.column = east;
					else if(!cardinals[0] && !cardinals[1] && !cardinals[2] && !cardinals[3] && !hasAShipSunked) {
						target = targetOrigin;
						targetTemp = target;

						north = target.row - counter;
						targetTemp.row = north;

						if(playerOneGameBoard->checkShot(targetTemp) != -1 && north >= 0) {
							cardinals[0] = true;
						}

						targetTemp = target;
						south = target.row + counter;
						targetTemp.row = south;

						if(playerOneGameBoard->checkShot(targetTemp) != -1 && south <= 9) {
							cardinals[1] = true;
						}

						targetTemp = target;
						west = target.column - counter;
						targetTemp.column = west;

						if(playerOneGameBoard->checkShot(targetTemp) != -1 && west >= 0) {
							cardinals[2] = true;
						}

						targetTemp = target;
						east = target.column + counter;
						targetTemp.column = east;

						if(playerOneGameBoard->checkShot(targetTemp) != -1 && east <= 9) {
							cardinals[3] = true;
						}

						counter++;
					} else {
						targetMode = false;
						huntMode = true;
						break;
					}

					shot = playerOneGameBoard->checkShot(target);
				} while(shot == -1 && targetMode);

				if(shot == 1 && huntMode == false) {
					for(i = 0; i < 4; i++) {
						if(!flipper)
							cardinals[i] = false;

						if(cardinals[i] == flipper)
							flipper = false;
					}
				} else {
					for(i = 0; i < 4; i++) {
						if(flipper && cardinals[i] != false) {
							cardinals[i] = false;
							break;
						}
					}
				}

				flipper = true;
			}

			if(huntMode) {
				counter = 1;
				flipper = true;
				for(i = 0; i < 4; i++)
					cardinals[i] = true;

				do {
					target.row = getRandomNumber(0, 9);
					target.column = getRandomNumber(0, 9);

					shot = playerOneGameBoard->checkShot(target);
				} while(shot == -1);

				if(shot == 1) targetOrigin = target;
			}

			if(shot == 1) {
				if(!cardinals[0] && !cardinals[1] && !cardinals[2] && !cardinals[3] && !hasAShipSunked) {
					target = targetOrigin;
				}

				huntMode = false;
				targetMode = true;
				targetAI = target;

				if(cardinals[0]) {
					north = (targetAI.row - 1);
					playerOneGameBoard->checkBoundsOfCardinal(cardinals, north, 0);
					targetTemp = target;
					targetTemp.row = north;
					if(playerOneGameBoard->checkShot(targetTemp) == -1)
						cardinals[0] = false;
				}

				if(cardinals[1]) {
					south = (targetAI.row + 1);
					playerOneGameBoard->checkBoundsOfCardinal(cardinals, south, 1);
					targetTemp = target;
					targetTemp.row = south;
					if(playerOneGameBoard->checkShot(targetTemp) == -1)
						cardinals[1] = false;
				}

				if(cardinals[2]) {
					west = (targetAI.column - 1);
					playerOneGameBoard->checkBoundsOfCardinal(cardinals, west, 2);
					targetTemp = target;
					targetTemp.column = west;
					if(playerOneGameBoard->checkShot(targetTemp) == -1)
						cardinals[2] = false;
				}

				if(cardinals[3]) {
					east = (targetAI.column + 1);
					playerOneGameBoard->checkBoundsOfCardinal(cardinals, east, 3);
					targetTemp = target;
					targetTemp.column = east;
					if(playerOneGameBoard->checkShot(targetTemp) == -1)
						cardinals[3] = false;
				}
			}

			shipSymbol = playerOneGameBoard->gameBoard[target.row][target.column].symbol;
			break;
		}

		if(shot == 1) {
			printf("> %d, %d is a hit!\n", target.row, target.column);

			outStream << target.row << ", " << target.column << " is a hit!" << std::endl;

			players[player].numHits++;

			if(player == 1)
				hasAShipSunked = checkSunkShip(sunkShip, !player, shipSymbol, outStream);
			else
				checkSunkShip(sunkShip, !player, shipSymbol, outStream);
		} else {
			printf("> %d, %d is a miss!\n", target.row, target.column);

			outStream << target.row << ", " << target.column << " is a miss!" << std::endl;
			players[player].numMisses++;
		}

		if(player == 0)
			playerTwoGameBoard->updateGameBoard(target);
		else
			playerOneGameBoard->updateGameBoard(target);

		if(isWinner(players, player)) {
			printf("\n> Player %d wins!\n", player + 1);

			outStream << std::endl << ">>>>> Player " << (player + 1) << " wins! <<<<<" << std::endl;
			break;
		}

		systemMessage("> Hit <ENTER> to continue!\n");

		player = !player;

		system ("cls");
	}

	players[0].totalShots = players[0].numHits + players[0].numMisses;
	players[0].hitMissRatio = ((double) players[0].numHits / (double) players[0].numMisses) * 100;
	players[1].totalShots = players[1].numHits + players[1].numMisses;
	players[1].hitMissRatio = ((double) players[1].numHits / (double) players[1].numMisses) * 100;
	outStream << "+===================================================" << std::endl;
	outStream << "|                    PLAYER STATS                   " << std::endl;
	outStream << "+===================================================" << std::endl;
	outStream << "| PLAYER 1 : " << players[0].numHits << " hits                                " << std::endl;
	outStream << "|            " << players[0].numMisses << " misses                            " << std::endl;
	outStream << "|            " << players[0].totalShots << " total shots                      " << std::endl;
	outStream << "|            " << players[0].hitMissRatio << " hit/miss ratio                 " << std::endl;
	outStream << "| PLAYER 2 : " << players[1].numHits << " hits                                " << std::endl;
	outStream << "|            " << players[1].numMisses << " misses                            " << std::endl;
	outStream << "|            " << players[1].totalShots << " total shots                      " << std::endl;
	outStream << "|            " << players[1].hitMissRatio << " hit/miss ratio                 " << std::endl;
	outStream << "+===================================================" << std::endl;
	return true;
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

void Production::systemMessage(std::string message) {
	std::cout << message << std::endl;

	gets(NULL);
}

bool Production::isWinner(Stats players[], int player) {
	bool isWin = false;

	if (players[player].numHits == 17)
		isWin = true;

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

bool Production::checkSunkShip(short sunkShip[][NUM_OF_SHIPS], short player, char shipSymbol, std::ostream& stream) {
	bool sunked = false;

	switch (shipSymbol) {
		case CARRIER:
			if (--sunkShip[player][0] == 0) {
				printf ("> Player %d's Carrier sunked!\n", player + 1);

				/* Write to battleship.log */
				stream << "Player " << (player + 1) << "'s Carrier sunked!" << std::endl;

				sunked = true;
			}
			break;

		case BATTLESHIP:
			if (--sunkShip[player][1] == 0) {
				printf ("> Player %d's Battleship sunked!\n", player + 1);

				/* Write to battleship.log */
				stream << "Player " << (player + 1) << "'s Battleship sunked!" << std::endl;

				sunked = true;
			}
			break;

		case CRUISER:
			if (--sunkShip[player][2] == 0) {
				printf ("> Player %d's Cruiser sunked!\n", player + 1);

				/* Write to battleship.log */
				stream << "Player " << (player + 1) << "'s Cruiser sunked!" << std::endl;

				sunked = true;
			}
			break;

		case SUBMARINE:
			if (--sunkShip[player][3] == 0) {
				printf ("> Player %d's Submarine sunked!\n", player + 1);

				/* Write to battleship.log */
				stream << "Player " << (player + 1) << "'s Submarine sunked!" << std::endl;

				sunked = true;
			}
			break;

		case DESTROYER:
			if (--sunkShip[player][4] == 0) {
				printf ("> Player %d's Destroyer sunked!\n", player + 1);

				/* Write to battleship.log */
				stream << "Player " << (player + 1) << "'s Destroyer sunked!" << std::endl;

				sunked = true;
			}
			break;
	}

	return sunked;
}
