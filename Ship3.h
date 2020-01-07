#ifndef SHIP3_H
#include "ShipBase.h"
#include "Constants.h"
#include "Grid.h"
#define SHIP3_H

class Ship3 : public Ship
{
public:
	Ship3(int row, int col) : Ship(3, row, col){}

	void rotate(vector<vector<Grid>> &map)
	{
		//----------If we rotate first time, then check collision with ships or walls-----------------
		if (getRotationPos() == 0)
		{
			//-------------Rotate the ship and check whether it's collide with something---------------
			map[getShip(0).getRow()][getShip(0).getCol()].setState(FREE);
			getShip(0).changeCol(1);
			getShip(0).changeRow(1);

			map[getShip(2).getRow()][getShip(2).getCol()].setState(FREE);
			getShip(2).changeCol(-1);
			getShip(2).changeRow(-1);

			//-----------TODO: add checking collision on 2 part of the ship--------------------
			if (!(isCollide(getShip(0), map) || isCollide(getShip(2), map)))
			{
				setRotationPos(1);
			}
			else //-------------- if ship collide, return it's position back-----------------
			{
				getShip(0).changeCol(-1);
				getShip(0).changeRow(-1);
				map[getShip(0).getRow()][getShip(0).getCol()].setState(SHIP);

				getShip(2).changeCol(1);
				getShip(2).changeRow(1);
				map[getShip(2).getRow()][getShip(2).getCol()].setState(SHIP);

			}
		}
		else
		{
			map[getShip(0).getRow()][getShip(0).getCol()].setState(FREE);
			getShip(0).changeCol(-1);
			getShip(0).changeRow(-1);

			map[getShip(2).getRow()][getShip(2).getCol()].setState(FREE);
			getShip(2).changeCol(1);
			getShip(2).changeRow(1);

			if (!(isCollide(getShip(0), map) || isCollide(getShip(2), map) ))
			{
				setRotationPos(0);
			}
			else
			{

				getShip(0).changeCol(1);
				getShip(0).changeRow(1);
				map[getShip(0).getRow()][getShip(0).getCol()].setState(SHIP);

				getShip(2).changeCol(-1);
				getShip(2).changeRow(-1);
				map[getShip(2).getRow()][getShip(2).getCol()].setState(SHIP);

			}
		}
		setPosition(map);
	}

};

#endif