#pragma once
#include "Vector2.h"
#include <vector>
#include <iostream>
#include <SFML\Graphics.hpp>

class MapControl {

public:
	std::string wall = "imgs/wall.png";
	std::string apple = "imgs/apple.png";
	std::string power = "imgs/power.png";
	int boxSize = 15;

	int currentMap[31][28]; //0 is empty space //1 is wall // 2 is apple //3 is powerball //4 is left teleporter //5 is right teleporter

	MapControl() {
		if (!wallTexture.loadFromFile(wall)) {
			std::cerr << "Error\n";
		}
		if (!appleTexture.loadFromFile(apple)) {
			std::cerr << "Error\n";
		}
		if (!powerTexture.loadFromFile(power)) {
			std::cerr << "Error\n";
		}
		reset();
	}
	void reset() {
	
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 28; j++) {
				sprites[i][j].setOrigin((7.5), (7.5));
				sprites[i][j].setPosition(((j * 15 +7.5)*1.75), ((i * 15 + 7.5)*1.75));
				sprites[i][j].setScale(1.75, 1.75);

			}
		}
		setDefaultMap();
	}

	void setDefaultMap() {
		std::cout << "Hello world" << std::endl;
		
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 28; j++) {

				if (defaultMap[i][j] == 'w') {
					sprites[i][j].setTexture(wallTexture);
					currentMap[i][j] = 1;
				}
				else if (defaultMap[i][j] == 'a') {
					sprites[i][j].setColor(sf::Color(255, 255, 255, 255));
					sprites[i][j].setTexture(appleTexture);
					currentMap[i][j] = 2;
				}
				else if (defaultMap[i][j] == 'p') {
					sprites[i][j].setColor(sf::Color(255, 255, 255, 255));
					sprites[i][j].setTexture(powerTexture);
					currentMap[i][j] = 3;
				}
				else if (defaultMap[i][j] == 'l') {
					sprites[i][j].setColor(sf::Color(0,0,0,0));  ///these are the teleporters
					currentMap[i][j] = 4;
				}
				else if (defaultMap[i][j] == 'r') {
					sprites[i][j].setColor(sf::Color(0, 0, 0, 0));
					currentMap[i][j] = 5;
				}
				else
				{
					currentMap[i][j] = 0;
				}
			}
		}
		
	}
	void drawSimpleBackground() {
		
		

	}

	void drawMap(sf::RenderWindow &window) {
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 28; j++) {
				window.draw(sprites[i][j]);

			}
		}
	}

	int eatBlock(int x, int y) {
		if (currentMap[x][y] == 2) {
			currentMap[x][y] = 0;
			sprites[x][y].setColor(sf::Color(0, 0, 0, 0));
			return 1;
		}
		if (currentMap[x][y] == 3) {
			currentMap[x][y] = 0;
			sprites[x][y].setColor(sf::Color(0, 0, 0, 0));
			return 2;
		}
		if (currentMap[x][y] == 4) {
			return 3;
		}
		if (currentMap[x][y] == 5) {
			return 4;
		}
		return 0;
	}

private:

	sf::Texture wallTexture; //0
	
	sf::Texture appleTexture;
	
	sf::Texture powerTexture;

	sf::Sprite sprites[31][28];

	char defaultMap[31][28] = { {'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},//0
								{'w','a','a','a','a','a','a','a','a','a','a','a','a','w','w','a','a','a','a','a','a','a','a','a','a','a','a','w'},//1
								{'w','a','w','w','w','w','a','w','w','w','w','w','a','w','w','a','w','w','w','w','w','a','w','w','w','w','a','w'},//2
								{'w','p','w','w','w','w','a','w','w','w','w','w','a','w','w','a','w','w','w','w','w','a','w','w','w','w','p','w'},//3
								{'w','a','w','w','w','w','a','w','w','w','w','w','a','w','w','a','w','w','w','w','w','a','w','w','w','w','a','w'},//4
								{'w','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','w'},//5
								{'w','a','w','w','w','w','a','w','w','a','w','w','w','w','w','w','w','w','a','w','w','a','w','w','w','w','a','w'},//6
								{'w','a','w','w','w','w','a','w','w','a','w','w','w','w','w','w','w','w','a','w','w','a','w','w','w','w','a','w'},//7
								{'w','a','a','a','a','a','a','w','w','a','a','a','a','w','w','a','a','a','a','w','w','a','a','a','a','a','a','w'},//8
								{'w','w','w','w','w','w','a','w','w','w','w','w','e','w','w','e','w','w','w','w','w','a','w','w','w','w','w','w'},//9
								{'e','e','e','e','e','w','a','w','w','w','w','w','e','w','w','e','w','w','w','w','w','a','w','e','e','e','e','e'},//0
								{'e','e','e','e','e','w','a','w','w','e','e','e','e','e','e','e','e','e','e','w','w','a','w','e','e','e','e','e'},//1
								{'e','e','e','e','e','w','a','w','w','e','w','w','w','w','w','w','w','w','e','w','w','a','w','e','e','e','e','e'},//2
								{'w','w','w','w','w','w','a','w','w','e','w','e','e','e','e','e','e','w','e','w','w','a','w','w','w','w','w','w'},//3
								{'l','e','e','e','e','e','a','e','e','e','w','e','e','e','e','e','e','w','e','e','e','a','e','e','e','e','e','r'},//4
								{'w','w','w','w','w','w','a','w','w','e','w','e','e','e','e','e','e','w','e','w','w','a','w','w','w','w','w','w'},//5
								{'e','e','e','e','e','w','a','w','w','e','w','w','w','w','w','w','w','w','e','w','w','a','w','e','e','e','e','e'},//6
								{'e','e','e','e','e','w','a','w','w','e','e','e','e','e','e','e','e','e','e','w','w','a','w','e','e','e','e','e'},//7
								{'e','e','e','e','e','w','a','w','w','e','w','w','w','w','w','w','w','w','e','w','w','a','w','e','e','e','e','e'},//8
								{'w','w','w','w','w','w','a','w','w','e','w','w','w','w','w','w','w','w','e','w','w','a','w','w','w','w','w','w'},//9
								{'w','a','a','a','a','a','a','a','a','a','a','a','a','w','w','a','a','a','a','a','a','a','a','a','a','a','a','w'},//0
								{'w','a','w','w','w','w','a','w','w','w','w','w','a','w','w','a','w','w','w','w','w','a','w','w','w','w','a','w'},//1
								{'w','a','w','w','w','w','a','w','w','w','w','w','a','w','w','a','w','w','w','w','w','a','w','w','w','w','a','w'},//2
								{'w','p','a','a','w','w','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','w','w','a','a','p','w'},//3
								{'w','w','w','a','w','w','a','w','w','a','w','w','w','w','w','w','w','w','a','w','w','a','w','w','a','w','w','w'},//4
								{'w','w','w','a','w','w','a','w','w','a','w','w','w','w','w','w','w','w','a','w','w','a','w','w','a','w','w','w'},//5
								{'w','a','a','a','a','a','a','w','w','a','a','a','a','w','w','a','a','a','a','w','w','a','a','a','a','a','a','w'},//6
								{'w','a','w','w','w','w','w','w','w','w','w','w','a','w','w','a','w','w','w','w','w','w','w','w','w','w','a','w'},//7
								{'w','a','w','w','w','w','w','w','w','w','w','w','a','w','w','a','w','w','w','w','w','w','w','w','w','w','a','w'},//8
								{'w','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','a','w'},//9
								{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'} };//0

	

};