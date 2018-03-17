#pragma once

#include "Ghost.h"
#include "Vector2.h"

#include <iostream>
#include <SFML\Graphics.hpp>

class GhostMgr {
public:
	Ghost yellow = Ghost("imgs/YellowGhost.png");
	Ghost pink = Ghost("imgs/PinkGhost.png");
	Ghost green = Ghost("imgs/GreenGhost.png");
	Ghost red = Ghost("imgs/RedGhost.png");
	sf::Clock clock;
	sf::Clock BlueTimer;
	sf::Clock AttackTimer;
	sf::Time time;
	int count = 0;
	std::string temp;
	int playerX;
	int playerY;
	bool frozen = false;

	GhostMgr() {
		//yellow = Ghost("imgs/Pacman.png");
		init();
	}

	void goBlue() {
		
		yellow.switchMode('v', 10);
		pink.switchMode('v', 10);
		green.switchMode('v', 10);
		red.switchMode('v', 10);
		//BlueTimer.restart();
		//AttackTimer.restart();
	}
	
	void init() {
		clock.restart();
		yellow.setStartPos(13,14);
		pink.setStartPos(13, 13);
		green.setStartPos(13, 15);
		red.setStartPos(13, 14);

		count = 0;
		freeze();
	//	std::cout << "freeze" << std::endl;
		yellow.defaultSpeed = 78.0f;
		pink.defaultSpeed = 92.0f;
		green.defaultSpeed = 74.0f;
		red.defaultSpeed = 85.5f;
		yellow.init();
		frozen = false;
		
		
	}
	void freeze() {
		clock.restart();
		frozen = true;
		yellow.switchMode('f', 0);
		pink.switchMode('f', 0);
		green.switchMode('f', 0);
		red.switchMode('f', 0);
	}

	void drawGhost(sf::RenderWindow &ewindow) {
		yellow.drawGhost(ewindow);
		pink.drawGhost(ewindow);
		green.drawGhost(ewindow);
		red.drawGhost(ewindow);
	}
	void moveGhost(float deltaTime, int playx, int playy,float playerX, float playerY) {
		update();
		yellow.moveGhost(deltaTime, playx, playy, playerX, playerY);
		pink.moveGhost(deltaTime, playx, playy, playerX, playerY);
		green.moveGhost(deltaTime, playx, playy, playerX, playerY);
		red.moveGhost(deltaTime, playx, playy, playerX, playerY);
	}

	void update() {
		
		yellow.Update();
		green.Update();
		red.Update();
		pink.Update();

		if (count == 0) {
			clock.restart();
			count = 1;
			return;
		}
		if (clock.getElapsedTime().asSeconds() > 2) {
			if (!frozen) {
				releaseGhost();
				clock.restart();
			}
		}
		/*
		if (BlueTimer.getElapsedTime().asSeconds() > 10 && count == 4) {
			setGhosts();
			
			return;
		}
		if (BlueTimer.getElapsedTime().asSeconds() > 15 && count ==4) {
			yellow.goNormal('a');
			pink.goNormal('a');
			green.goNormal('a');
			red.goNormal('a');
		}
		*/
	}
	void unFreeze() {
		
		
		if (yellow.frozen == true)
			yellow.init();
		if (pink.frozen == true)
			pink.init();
		if (green.frozen == true)
			green.init();
		if (red.frozen == true)
			red.init();
	}

	void setGhosts() {
		int temp = rand() % 8;
		if (temp == 0) {
			yellow.switchMode('a',0);
			pink.switchMode('y', 0);
			green.switchMode('r', 0);
			red.switchMode('b', 0);
		}
		if (temp == 1) {
			yellow.switchMode('b', 0);
			pink.switchMode('a', 0);
			green.switchMode('a', 0);
			red.switchMode('p', 0);
		}
		if (temp == 2) {
			yellow.switchMode('p', 0);
			pink.switchMode('a', 0);
			green.switchMode('b', 0);
			red.switchMode('a', 0);
		}
		if (temp == 3) {
			yellow.switchMode('a', 0);
			pink.switchMode('p', 0);
			green.switchMode('a', 0);
			red.switchMode('a', 0);
		}
		if (temp == 4) {
			yellow.switchMode('a', 0);
			pink.switchMode('y', 0);
			green.switchMode('r', 0);
			red.switchMode('b', 0);
		}
		if (temp == 5) {
			yellow.switchMode('y', 0);
			pink.switchMode('r', 0);
			green.switchMode('b', 0);
			red.switchMode('a', 0);
		}
		if (temp == 6) {
			yellow.switchMode('r', 0);
			pink.switchMode('b', 0);
			green.switchMode('a', 0);
			red.switchMode('y', 0);
		}
		if (temp == 7) {
			yellow.switchMode('a', 0);
			pink.switchMode('a', 0);
			green.switchMode('a', 0);
			red.switchMode('a', 0);
		}
		
		

	}

	void releaseGhost() {
		//std::cout << count << std::endl;
		if (count == 1) {
			pink.init();
			count++;
		}
		else if (count == 2) {
			green.init();
			count++;
		}
		else if (count == 3) {
			red.init();
			count++;
		}
	}

	std::string getUpdate(){
		temp =yellow.getUpdate();
		if (temp == "")
			temp = pink.getUpdate();
		if (temp == "")
			temp = green.getUpdate();
		if (temp == "")
			temp = red.getUpdate();
		if (temp != "")
			std::cout << temp << std::endl;

		return temp;
		
	}
	void clrUpdate() {
		yellow.clrUpdate();
		pink.clrUpdate();
		green.clrUpdate();
		red.clrUpdate();

	}
	
private:

};