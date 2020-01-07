#ifndef SHIPBASE_H
#include <SFML/Graphics.hpp>
#include "Constants.h"
#define SHIPBASE_H
using namespace std;

class Place
{
	int column;
	int row;
	sf::RectangleShape shape;

public:

	Place() {}

	Place(int r, int c)
	{
		shape.setSize(sf::Vector2f(ShipWidth, ShipHeight));

		row = r;
		column = c;
	}

	int getCol()
	{
		return column;
	}

	void changeCol(int n)
	{
		column += n;
	}

	void changeRow(int n)
	{
		row += n;
	}

	int getRow()
	{
		return row;
	}

	sf::RectangleShape& getShape()
	{
		return shape;
	}
};

class Ship
{
	int pivot;
	int rotationPos = 0;
	vector<Place> ship;
	

public:

	
	Ship() {}

	Ship(int size, int r, int c)
	{
		ship.resize(size);

		for (int i = 0; i < getLen(); i++, r++)
		{
			ship[i] = Place(r, c);
		}
	}

	Place& getShip(int index)
	{
		return ship[index];
	}

	void setPivot(int p)
	{
		pivot = p;
	}

	int getRotationPos()
	{
		return rotationPos;
	}
	
	void setRotationPos(int p)
	{
		rotationPos = p;
	}

	int getLen()
	{
		return ship.size();
	}

	void setPosition(vector<vector<Grid>> &map)
	{
		for (int i = 0; i < getLen(); i++)
		{
			map[getShip(i).getRow()][getShip(i).getCol()].setState(SHIP);
		}
	}

	bool isCollide(Place ship, vector<vector<Grid>> &map)
	{
		if (ship.getCol() > 9 || ship.getRow() > 9 || ship.getCol() < 0 || ship.getRow() < 0 || map[ship.getRow()][ship.getCol()].getState() != FREE)
			return true;
		return false;
	}

	void update(vector<vector<Grid>> &map, int direction)
	{
		//----------Move ship right-------------
		//--------TODO: add collision with other ships------------------
		int k = 0;
		bool collide = false;
		switch (direction)
		{
		case RIGHT:
			collide = false;

			if (getRotationPos() == 0)// Vertically
			{
				for (int i = 0; i < getLen(); i++, k++)
				{
					//------change position of the ship on the map and check collision with ships and bounds-----------
					//------if there is a collision return everything back-------------------------
					map[getShip(i).getRow()][getShip(i).getCol()].setState(FREE);
					getShip(i).changeCol(1);

					if (isCollide(getShip(i), map))
					{
						for (int j = k; j >= 0; j--)
						{
							getShip(j).changeCol(-1);
							map[getShip(j).getRow()][getShip(j).getCol()].setState(SHIP);
						}
						collide = true;
						break;
					}

				}

				if (!collide)
				{
					for (int i = 0; i < getLen(); i++)
					{
						map[getShip(i).getRow()][getShip(i).getCol()].setState(SHIP);
					}
				}
			}
			else //Horizontally
			{
				map[getShip(0).getRow()][getShip(0).getCol()].setState(FREE);
				getShip(0).changeCol(1);
				
				//----if the rightest part is colliding the the whole ship is colliding------------
				if (isCollide(getShip(0), map))
				{
					for (int j = k; j >= 0; j--)
					{
						getShip(j).changeCol(-1);
						map[getShip(j).getRow()][getShip(j).getCol()].setState(SHIP);
					}
				}
				else//------if not collide move the rest of the ship--------------
				{
					for (int i = 1; i < getLen(); i++)
					{
						map[getShip(i).getRow()][getShip(i).getCol()].setState(FREE);
						getShip(i).changeCol(1);
						map[getShip(i).getRow()][getShip(i).getCol()].setState(SHIP);
					}
				}
			}

			setPosition(map);
			break;

		case LEFT:// problem place 
			collide = false;

			if (getRotationPos() == 0)// Vertically
			{
				for (int i = 0; i < getLen(); i++, k++)
				{
					//------change position of the ship on the map and check collision with ships and bounds-----------
					//------if there is a collision return everything back-------------------------
					map[getShip(i).getRow()][getShip(i).getCol()].setState(FREE);
					getShip(i).changeCol(-1);

					if (isCollide(getShip(i), map))
					{
						for (int j = k; j >= 0; j--)
						{
							getShip(j).changeCol(1);
							map[getShip(j).getRow()][getShip(j).getCol()].setState(SHIP);
						}
						collide = true;
						break;
					}

				}

				if (!collide)
				{
					for (int i = 0; i < getLen(); i++)
					{
						map[getShip(i).getRow()][getShip(i).getCol()].setState(SHIP);
					}
				}
			}
			else //Horizontally
			{
				map[getShip(getLen() - 1).getRow()][getShip(getLen() - 1).getCol()].setState(FREE);
				getShip(getLen() - 1).changeCol(-1);
				
				//----if the rightest part is colliding the the whole ship is colliding------------
				if (isCollide(getShip(getLen() - 1), map))
				{
					getShip(getLen() - 1).changeCol(1);
					map[getShip(getLen() - 1).getRow()][getShip(getLen() - 1).getCol()].setState(SHIP);

					break;
				}
				else//------if not collide move the rest of the ship--------------
				{
					for (int i = getLen() - 2; i >= 0; i--)
					{
						map[getShip(i).getRow()][getShip(i).getCol()].setState(FREE);
						getShip(i).changeCol(-1);
						map[getShip(i).getRow()][getShip(i).getCol()].setState(SHIP);
					}
				}
			}

			setPosition(map);
			break;

		case UP:
			collide = false;

			if (getRotationPos() == 0)// Vertically
			{
				map[getShip(0).getRow()][getShip(0).getCol()].setState(FREE);
				getShip(0).changeRow(-1);

				//----if the upper part is colliding the the whole ship is colliding------------
				if (isCollide(getShip(0), map))
				{
					getShip(0).changeRow(1);
					map[getShip(0).getRow()][getShip(0).getCol()].setState(SHIP);
				}
				else//------if not collide move the rest of the ship--------------
				{
					for (int i = 1; i < getLen(); i++)
					{
						map[getShip(i).getRow()][getShip(i).getCol()].setState(FREE);
						getShip(i).changeRow(-1);
						map[getShip(i).getRow()][getShip(i).getCol()].setState(SHIP);
					}
				}

			}
			else //Horizontally
			{
				for (int i = 0; i < getLen(); i++, k++)
				{
					
					map[getShip(i).getRow()][getShip(i).getCol()].setState(FREE);
					getShip(i).changeRow(-1);

					if (isCollide(getShip(i), map))
					{
						for (int j = k; j >= 0; j--)
						{
							getShip(j).changeRow(1);
							map[getShip(j).getRow()][getShip(j).getCol()].setState(SHIP);
						}
						collide = true;
						break;
					}

				}

				if (!collide)
				{
					for (int i = 0; i < getLen(); i++)
					{
						map[getShip(i).getRow()][getShip(i).getCol()].setState(SHIP);
					}
				}

			}

			setPosition(map);
			break;

		case DOWN://need a different mechanism for collision
			collide = false;

			if (getRotationPos() == 0)// Vertically
			{
				map[getShip(getLen() - 1).getRow()][getShip(getLen() - 1).getCol()].setState(FREE);
				getShip(getLen() - 1).changeRow(1);

				//----if the upper part is colliding the the whole ship is colliding------------
				if (isCollide(getShip(getLen() - 1), map))
				{
					getShip(getLen() - 1).changeRow(-1);
					map[getShip(getLen() - 1).getRow()][getShip(getLen() - 1).getCol()].setState(SHIP);
				}
				else//------if not collide move the rest of the ship--------------
				{
					for (int i = getLen() - 2; i >= 0; i--)
					{
						map[getShip(i).getRow()][getShip(i).getCol()].setState(FREE);
						getShip(i).changeRow(1);
						map[getShip(i).getRow()][getShip(i).getCol()].setState(SHIP);
					}
				}

			}
			else //Horizontally
			{
				for (int i = 0; i < getLen(); i++, k++)
				{
					map[getShip(i).getRow()][getShip(i).getCol()].setState(FREE);
					getShip(i).changeRow(1);

					if (isCollide(getShip(i), map))
					{
						for (int j = k; j >= 0; j--)
						{
							getShip(j).changeRow(-1);
							map[getShip(j).getRow()][getShip(j).getCol()].setState(SHIP);
						}
						collide = true;
						break;
					}

				}

				if (!collide)
				{
					for (int i = 0; i < getLen(); i++)
					{
						map[getShip(i).getRow()][getShip(i).getCol()].setState(SHIP);
					}
				}

			}

			setPosition(map);
			break;
		}
	}

	virtual void rotate(vector<vector<Grid>> &map) = 0;

};

#endif