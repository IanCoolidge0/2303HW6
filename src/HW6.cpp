//============================================================================
// Name        : HW5.cpp
// Author      : Ian
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "Tests.h"
#include "Production.h"

using namespace std;

int main(int argc, char* argv[]) {
	cout << "!!!Hello World,  we are on HW6!!!" << endl; // prints !!!Hello World!!!
	Tests* tsP = new Tests();
	if(tsP->tests())
	{
		Production* pP = new Production();
		if(pP->prod(argc, argv))
		{
			cout <<"Production passed." << endl;
		}
		delete(pP);
	}
	else
	{
		cout <<"Not all tests passed." << endl;
	}
	delete(tsP);
	return 0;
}
