/*
 * WaterCraft.h
 *
 *  Created on: Mar 6, 2020
 *      Author: Ian
 */

#ifndef WATERCRAFT_H_
#define WATERCRAFT_H_

#include <iostream>
#include "main.h"
#include "Production.h"
#include <string.h>

class WaterCraft {
public:
	WaterCraft();
	WaterCraft(char symbol, int length, std::string name);
	virtual ~WaterCraft();

	void setLength(int length);
	int getLength();
	void setSymbol(char symbol);
	char getSymbol();
	void setName(std::string name);
	std::string getName();
private:
	int length;
	char symbol;
	std::string name;
};

#endif /* WATERCRAFT_H_ */
