#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Ship4.h"
#include "Ship3.h"
#include "Ship2.h"
#include "Ship1.h"
#include "ShipBase.h"
#include "Constants.h"

using namespace std;

vector<vector<Grid>> leftGrid()
{
	vector<vector<Grid>> cells(10);
	int k = 0;
	for (int i = 0; i < 400; i += 38)
	{
		for (int j = 0; j < 400; j += 38)
		{
			Grid cell(sf::Vector2f(38, 38), sf::Color::White, sf::Color::Black, sf::Vector2f(j + 51, i + 101), FREE);
			cells[k].push_back(cell);
			j += 2;
		}
		k++;
		i += 2;
	}

	return cells;
}

vector<vector<Grid>> rightGrid()
{
	vector<vector<Grid>> cells(10);
	int k = 0;
	for (int i = 0; i < 400; i += 38)
	{
		for (int j = 0; j < 400; j += 38)
		{
			Grid cell(sf::Vector2f(38, 38), sf::Color::White, sf::Color::Black, sf::Vector2f(j + 701, i + 101), FREE);
			cells[k].push_back(cell);

			j += 2;
		}
		k++;
		i += 2;
	}

	return cells;
}

void updateShot(sf::Vector2i pos, vector<vector<Grid>> map)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (pos.x >= map[i][j].getX() && pos.x <= map[i][j].getX() + GridSize && pos.y >= map[i][j].getY() && pos.y <= map[i][j].getY() + GridSize)
			{
				cout << "Change state" << endl;
				cout << "I: " << i << " J: " << j << endl;
				map[i][j].setState(BUSY);
				map[i][j].updateColor(BUSY);
				
			}
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SeaBattle");

	//---------Filling left part of the board---------
	vector<vector<Grid>> myMap = leftGrid();

	//---------Filling right part of the board--------
	vector<vector<Grid>> enemyMap = rightGrid();

	//---------Create ships------------------
	bool isPlacing = true;
	int shipNumber = 0;
	vector<Ship*> fleet = { new Ship4(2, 4), new Ship3(2, 4), new Ship3(2, 4), new Ship2(2, 4), new Ship2(2, 4), new Ship2(2, 4), new Ship1(2, 4), new Ship1(2, 4), new Ship1(2, 4), new Ship1(2, 4)};
	fleet[shipNumber]->setPosition(myMap);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
			if (event.type == sf::Event::KeyPressed && isPlacing)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Right:
					fleet[shipNumber]->update(myMap, RIGHT);
					break;
					
				case sf::Keyboard::Left:
					fleet[shipNumber]->update(myMap, LEFT);
					break;

				case sf::Keyboard::Up:
					fleet[shipNumber]->update(myMap, UP);
					break;

				case sf::Keyboard::Down:
					fleet[shipNumber]->update(myMap, DOWN);
					break;

				case sf::Keyboard::R:
					fleet[shipNumber]->rotate(myMap);
					break;

				case sf::Keyboard::Space:
					if (shipNumber <= 10)
					{
						cout << "Entered here " << endl;
						shipNumber++;

						if (shipNumber == 10)
						{
							cout << "Here" << endl;
							isPlacing = false;
							break;
						}
						else
						{
							fleet[shipNumber]->setPosition(enemyMap);
							fleet[shipNumber]->setPosition(myMap);
						}						
					}
					
					break;
				}
			}
			//------shoot control---------
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i position = sf::Mouse::getPosition(window);
				cout << "X:  " << position.x << " Y:  " << position.y << endl;
				updateShot(position, myMap);
			}
		}

		window.clear();
		
		//--------update ships positions-----------
		for (int i = 0; i < shipNumber; i++)
		{
			fleet[i]->setPosition(myMap);
			fleet[i]->setPosition(enemyMap);
		}

		//---------update map-----------
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				switch (myMap[i][j].getState())
				{	
				case FREE:
					
					myMap[i][j].updateColor(FREE);
					break;

				case SHIP:
					
					myMap[i][j].updateColor(SHIP);
					break;

				case BUSY:
					cout << "Change color" << endl;
					myMap[i][j].updateColor(BUSY);
					break;
				}

			}
		}
		

		//----------draw map------------
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				window.draw(myMap[i][j].getShape());
				window.draw(enemyMap[i][j].getShape());
			}
		}
		
		window.display();
	}

	return 0;
}