#ifndef GRID_H
#include <SFML/Graphics.hpp>
#include "Constants.h"
#define GRID_H
using namespace std;


class Grid
{

	int state;
	sf::RectangleShape shape;

public:
	

	void setState(int s)
	{
		state = s;
	}
		
	int getState()
	{
		return state;
	}

	int getX()
	{
		return shape.getPosition().x;
	}

	int getY()
	{
		return shape.getPosition().y;
	}

	Grid() {}

	Grid(sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor, sf::Vector2f position, int st)
	{
		shape.setSize(size);
		shape.setFillColor(fillColor);
		shape.setOutlineColor(outlineColor);
		shape.setOutlineThickness(1);
		shape.setPosition(position);
		state = st;
	}

	sf::RectangleShape& getShape()
	{
		return shape;
	}

	void updateColor(int color)
	{
		switch (color)
		{
		case FREE:
			shape.setFillColor(sf::Color::White);
			break;

		case SHIP:
			shape.setFillColor(sf::Color::Magenta);
			break;

		case BUSY:
			cout << "Redraw color" << endl;
			shape.setFillColor(sf::Color::Yellow);
			break;
		}
	}
};

#endif