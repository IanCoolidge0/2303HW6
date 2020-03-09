/*
 * WaterCraft.h
 *
 *  Created on: Mar 6, 2020
 *      Author: Ian
 */

#ifndef WATERCRAFT_H_
#define WATERCRAFT_H_

#include <iostream>
#include "Production.h"
#include <string.h>

class WaterCraft {
public:
	WaterCraft();
	virtual ~WaterCraft();

	void setLength(int length);
	int getLength();
	void setSymbol(Symbol symbol);
	Symbol getSymbol();
	void setName(std::string name);
	std::string getName();

	bool checkSunkShip(short player, char shipSymbol, std::ostream outputFile);
private:
	int length;
	Symbol symbol;
	std::string name;
};

#endif /* WATERCRAFT_H_ */
