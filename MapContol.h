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
	MapControl() {
		//Default
	}

	void drawDefaultMap() {
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 28; j++) {
				sf::Texture tempTexture;
				sf::Sprite tempSprite;

				if (defaultMap[i][j] == 'w') {
					if (!tempTexture.loadFromFile(wall)) {
						std::cerr << "Error\n";
					}
					tempSprite.setTexture(tempTexture);
					tempSprite.setPosition((i * 15), (j * 15));
					window.draw(tempSprite);
				}
				else if (defaultMap[i][j] == 'a') {
					if (!tempTexture.loadFromFile(apple)) {
						std::cerr << "Error\n";
					}
					tempSprite.setTexture(tempTexture);
					tempSprite.setPosition((i * 15), (j * 15));
					window.draw(tempSprite);

				}
				else if (defaultMap[i][j] == 'p') {
					if (!tempTexture.loadFromFile(power)) {
						std::cerr << "Error\n";
					}
					tempSprite.setTexture(tempTexture);
					tempSprite.setPosition((i * 15), (j * 15));
					window.draw(tempSprite);

				}
			
			
			}
		}
	}

private:

	char defaultMap[31][28] = { {'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},//0
								{'w','a','a','a','a','a','a','a','a','a','a','a','a','w','w','a','a','a','a','a','a','a','a','a','a','a','a','w'},//1
								{'w','a','w','w','w','w','a','w','w','w','w','w','a','w','w','a','w','w','w','w','w','a','w','w','w','w','a','w'},//2
								{'w','p','w','w','w','w','a','w','w','w','w','w','a','w','w','a','w','w','w','w','w','a','w','w','w','w','a','w'},//3
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
								{'e','e','e','e','e','e','a','e','e','e','w','e','e','e','e','e','e','w','e','e','e','a','e','e','e','e','e','e'},//4
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

	char currentMap[31][28];

};