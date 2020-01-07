#ifndef SHIP4_H
#include "ShipBase.h"
#include "Constants.h"
#define SHIP4_H

class Ship4 : public Ship
{
public:

	Ship4(int r, int c) : Ship(4, r, c) {}

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

			map[getShip(3).getRow()][getShip(3).getCol()].setState(FREE);
			getShip(3).changeCol(-2);
			getShip(3).changeRow(-2);

			cout << "Change rows and cols " << endl;

			//-----------TODO: add checking collision on 2 part of the ship--------------------
			if (!(isCollide(getShip(0), map) || isCollide(getShip(3), map) || isCollide(getShip(2), map)))
			{
				cout << "Change rot pos" << endl;
				setRotationPos(1);
			}
			else //-------------- if ship collide, return it's position back-----------------
			{
				cout << "In collide block now" << endl;

				getShip(0).changeCol(-1);
				getShip(0).changeRow(-1);
				map[getShip(0).getRow()][getShip(0).getCol()].setState(SHIP);
				
				getShip(2).changeCol(1);
				getShip(2).changeRow(1);
				map[getShip(2).getRow()][getShip(2).getCol()].setState(SHIP);

				getShip(3).changeCol(2);
				getShip(3).changeRow(2);
				map[getShip(3).getRow()][getShip(3).getCol()].setState(SHIP);

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

			map[getShip(3).getRow()][getShip(3).getCol()].setState(FREE);
			getShip(3).changeCol(2);
			getShip(3).changeRow(2);

			if (!(isCollide(getShip(0), map) || isCollide(getShip(3), map) || isCollide(getShip(2), map)))
			{
				cout << "Change rot pos again" << endl;
				setRotationPos(0);
			}
			else
			{
				cout << "In collide block again" << endl;
				getShip(0).changeCol(1);
				getShip(0).changeRow(1);
				map[getShip(0).getRow()][getShip(0).getCol()].setState(SHIP);

				getShip(2).changeCol(-1);
				getShip(2).changeRow(-1);
				map[getShip(2).getRow()][getShip(2).getCol()].setState(SHIP);

				getShip(3).changeCol(-2);
				getShip(3).changeRow(-2);
				map[getShip(3).getRow()][getShip(3).getCol()].setState(SHIP);
				
			}
		}
		setPosition(map);
	}

};

#endif