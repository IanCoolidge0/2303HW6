/*
 * WaterCraft.cpp
 *
 *  Created on: Mar 6, 2020
 *      Author: Ian
 */

#include "WaterCraft.h"

WaterCraft::WaterCraft() :
	length(0),
	symbol(WATER),
	name("") {
	// TODO Auto-generated constructor stub

}

WaterCraft::WaterCraft(char symbol, int length, std::string name) :
	length(length),
	symbol(symbol),
	name(name) {

}

WaterCraft::~WaterCraft() {
	// TODO Auto-generated destructor stub
}

void WaterCraft::setLength(int length) {
	this->length = length;
}

int WaterCraft::getLength() {
	return length;
}

void WaterCraft::setSymbol(char symbol) {
	this->symbol = symbol;
}

char WaterCraft::getSymbol() {
	return symbol;
}

void WaterCraft::setName(std::string name) {
	this->name = name;
}

std::string WaterCraft::getName() {
	return name;
}
