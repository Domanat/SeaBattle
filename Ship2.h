#ifndef SHIP2_H
#include "ShipBase.h"
#include "Grid.h"
#include "Constants.h"
#define SHIP2_H

using namespace std;

class Ship2 : public Ship
{
public:
	Ship2(int row, int col) : Ship(2, row, col) {}

	void rotate(vector<vector<Grid>> &map)
	{
		//----------If we rotate first time, then check collision with ships or walls-----------------
		if (getRotationPos() == 0)
		{
			//-------------Rotate the ship and check whether it's collide with something---------------

			map[getShip(1).getRow()][getShip(1).getCol()].setState(FREE);
			getShip(1).changeCol(-1);
			getShip(1).changeRow(-1);

			if (!(isCollide(getShip(1), map)))
			{
				setRotationPos(1);
			}
			else //-------------- if ship collide, return it's position back-----------------
			{

				getShip(1).changeCol(1);
				getShip(1).changeRow(1);
				map[getShip(1).getRow()][getShip(1).getCol()].setState(SHIP);

			}
		}
		else
		{
			map[getShip(1).getRow()][getShip(1).getCol()].setState(FREE);
			getShip(1).changeCol(1);
			getShip(1).changeRow(1);

			if (!(isCollide(getShip(1), map)))
			{
				setRotationPos(0);
			}
			else
			{
				getShip(1).changeCol(-1);
				getShip(1).changeRow(-1);
				map[getShip(1).getRow()][getShip(1).getCol()].setState(SHIP);

			}
		}


		setPosition(map);
	}
};

#endif