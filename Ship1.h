#ifndef SHIP1_H
#include "Constants.h"
#include "ShipBase.h"
#define SHIP1_H

class Ship1 : public Ship
{
public:
	Ship1(int row, int col) : Ship(1, row, col) {}

	void rotate(vector<vector<Grid>> &map)
	{

	}
};

#endif