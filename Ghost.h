#pragma once
#pragma once

#include "Vector2.h"

#include <iostream>
#include <SFML\Graphics.hpp>
#include <cmath>
#include <stdlib.h>
#include <time.h>

class Ghost {

public:
	float defaultSpeed = 75.0f;
	float moveSpeed = 55.0f;
	char moveDirection = 'l';
	char newMoveDirection = 'l';
	char mode = 'a';
	int targetx = 0;
	int targety = 0;
	float playerx = 0;
	float playery = 0;
	bool vulnerable = false;
	bool frozen = false;
	Vector2 StartPos;

	sf::Clock nextClock;
	char nextMode = 'a';
	int nextModeSeconds = 0;

	std::string update = "";
	Ghost() {
		//default
	}
	Ghost(std::string imgDirectory) {
		
		if (!pTexture.loadFromFile(imgDirectory)) {
			std::cerr << "Error\n";
		}
		if (!blueText.loadFromFile("imgs/BlueGhost.png")) {
			std::cerr << "Error\n";
		}
		pSprite.setTexture(pTexture);
		pSprite.setOrigin(78, 78);
		pSprite.setRotation(0);
		

		//std::cout << movingTowards.getIntX();
		pSprite.setScale(.14, .14);
	}
	void setStartPos(int x, int y) {
		StartPos = Vector2(x, y, 1);
		setPosition(StartPos);
	}
	void goBlue(int Seconds) {
		
		nextMode = 'a';
		nextModeSeconds = Seconds;
		nextClock.restart();
		
		pSprite.setTexture(blueText);
		mode = 'v';
		moveSpeed = 45.0;
		vulnerable = true;
		if (moveDirection == 'u')
			moveDirection = 'd';
		else if (moveDirection == 'd')
			moveDirection = 'u';
		else if (moveDirection == 'l')
			moveDirection = 'r';
		else
			moveDirection = 'l';
		getTarget();
	}
	
	void switchMode(char m, int Seconds) {
		//std::cout << "my Char is"<< m << std::endl;
		if (m == 'v') {
			goBlue(Seconds);
		}
		
		else {
			nextMode = m;
			nextModeSeconds = Seconds;
			nextClock.restart();
			
		}
	}
	void drawGhost(sf::RenderWindow &window) {
		window.draw(pSprite);
	}
	void setPosition(Vector2 pos) {
		pSprite.setPosition(((pos.y * 15 + 7.5) * 1.75), ((pos.x * 15 + 7.5) * 1.75));
		
		//
		//std::cout << "Hello cunt" << std::endl;

	}
	void init() {
		frozen = false;
		setPosition(startPoint);
		moveSpeed = defaultSpeed;
		moveDirection = 'l';
		newMoveDirection = 'l';
		switchMode('a',0);
		mode = 'a';
		targetx = 0;
		targety = 0;
		update = "";
		movingTowards = Vector2(11, 12, 6);
		nextMode = mode;
		nextModeSeconds = 0;
		nextClock.restart();
	}
	void freeze() {
		
		init();
		nextMode = 'f';
		frozen = true;
		setPosition(StartPos);
		moveSpeed = 0;
		
	}
	void getTarget() {
		
		int temp;
		int min = 0;
		int save = 0;
		int max = 30;

		switch (moveDirection) {

		case 'u':
		temp = movingTowards.getIntY();
		max = 0;
		save = 0;
		for (int i = 0; i < 75; i++) {
		if (corners[i].getIntY() != temp)
		continue;

		if (corners[i].getIntX() < movingTowards.getIntX()) {
		if (corners[i].getIntX() > max) {
		max = corners[i].getIntX();


		save = i;
		}
		}
		}
		movingTowards.x = corners[save].x;
		movingTowards.y = corners[save].y;
		movingTowards.cornerType = corners[save].cornerType;

		break;
		case 'd':
		temp = movingTowards.getIntY();
		max = 30;
		save = 0;
		for (int i = 0; i < 75; i++) {
		if (corners[i].getIntY() != temp)
		continue;

		if (corners[i].getIntX() > movingTowards.getIntX()) {
		if (corners[i].getIntX() < max) {
		max = corners[i].getIntX();


		save = i;
		}
		}
		}
		movingTowards.x = corners[save].x;
		movingTowards.y = corners[save].y;
		movingTowards.cornerType = corners[save].cornerType;

		break;
		case 'l':

		temp = movingTowards.getIntX(); //14
		max = 0;
		save = 0;
		for (int i = 0; i < 75; i++) {
		if (corners[i].getIntX() != temp)
		continue;

		if (corners[i].getIntY() < movingTowards.getIntY()) {
		if (corners[i].getIntY() > max) {
		max = corners[i].getIntY();


		save = i;
		}
		}
		}
		movingTowards.x = corners[save].x;
		movingTowards.y = corners[save].y;
		movingTowards.cornerType = corners[save].cornerType;


		break;
		case 'r':
		temp = movingTowards.getIntX();
		max = 30;
		save = 0;
		for (int i = 0; i < 75; i++) {
			if (corners[i].getIntX() != temp)
				continue;

			if (corners[i].getIntY() > movingTowards.getIntY()) {
				if (corners[i].getIntY() < max) {
					max = corners[i].getIntY();
					save = i;
				}
			}
		}
		movingTowards.x = corners[save].x;
		movingTowards.y = corners[save].y;
		movingTowards.cornerType = corners[save].cornerType;
		break;

		}
		/**/

		/*switch (moveDirection) {

		case 'u':
			movingTowards.x--;
			
			break;

		case 'd':
			movingTowards.x++;
			
			break;

		case 'l':
			movingTowards.y--;
			
			break;

		case 'r':
			movingTowards.y++;
			
			break;
		}
		*/
	}

	bool reachedTarget() {
		//std::cout << movingTowards.y << std::endl;
		if (moveDirection == 'u') {
			if (pSprite.getPosition().y < (movingTowards.x * 15 + 14.5)*1.75) {
			//	updateBlock();
			}
			if (pSprite.getPosition().y < (movingTowards.x * 15 + 7.5)*1.75) {

				return true;

			}
		}
		else if (moveDirection == 'd') {
			if (pSprite.getPosition().y >(movingTowards.x * 15 + .5)*1.75) {
				//updateBlock();
			}
			if (pSprite.getPosition().y > (movingTowards.x * 15 + 7.5)*1.75) {

				return true;

			}
		}
		else if (moveDirection == 'l') {
			if (pSprite.getPosition().x < (movingTowards.y * 15 + 14.5)*1.75) {
				//updateBlock();
			}
			if (pSprite.getPosition().x < (movingTowards.y * 15 + 7.5)*1.75) {

				return true;
			}
		}
		else if (moveDirection == 'r') {
			if (pSprite.getPosition().x >(movingTowards.y * 15 + .5)*1.75) {
				//updateBlock();
			}
			if (pSprite.getPosition().x > (movingTowards.y * 15 + 7.5)*1.75) {

				return true;

			}
		}
		return false;

	}

	bool isIntersection() {
		int tempY = movingTowards.getIntY();
		int tempX = movingTowards.getIntX();

		for (int i = 0; i < 75; i++) {
			if (corners[i].getIntY() != tempY)
				continue;

			if (corners[i].getIntX() == tempX) {
				movingTowards.cornerType = corners[i].cornerType;
				std::cout << "We hit an intersection!" << std::endl;
				return true;

			}
		}

		return false;
	}

	void nextTarget() {
		if (mode != 'v') {
		//	std::cout << targetx << ", "<< movingTowards.getIntX() << " // " << targety <<", "<< movingTowards.getIntY() << std::endl;
			if (targetx - movingTowards.getIntX() > 0 && targety - movingTowards.getIntY() > 0) {
				if (targetx - movingTowards.getIntX() > targety - movingTowards.getIntY()) {
					newMoveDirection = 'd';
					if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos) {
						moveDirection = 'd';
						getTarget();
					}
					else if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos) {
						moveDirection = 'r';
						getTarget();
					}
					else if(TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos && moveDirection != 'r') {
						moveDirection = 'l';
						getTarget();
					}
					else {
						moveDirection = 'u';
						getTarget();
					}

				}
				else
				{
					if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos && moveDirection != 'l') {
						moveDirection = 'r';
						getTarget();
					}
					else if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos && moveDirection != 'u') {
						moveDirection = 'd';
						getTarget();
					}
					else if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos && moveDirection != 'r') {
						moveDirection = 'l';
						getTarget();
					}
					else {
						moveDirection = 'u';
						getTarget();
					}
				}
			}
			else if (targetx - movingTowards.getIntX() < 0 && targety - movingTowards.getIntY() < 0) {
				if (targetx - movingTowards.getIntX() < targety - movingTowards.getIntY()) {
					if (TurnOptions[movingTowards.getCornerType()].find("u") != std::string::npos && moveDirection != 'd') {
						moveDirection = 'u';
						getTarget();
					}
					else if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos && moveDirection != 'r') {
						moveDirection = 'l';
						getTarget();
					}
					else if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos && moveDirection != 'l') {
						moveDirection = 'r';
						getTarget();
					}
					else {
						moveDirection = 'd';
						getTarget();
					}
				}
				else
				{
					if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos && moveDirection != 'r') {
						moveDirection = 'l';
						getTarget();
					}
					else if (TurnOptions[movingTowards.getCornerType()].find("u") != std::string::npos && moveDirection != 'd') {
						moveDirection = 'u';
						getTarget();
					}
					else if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos && moveDirection != 'u') {
						moveDirection = 'd';
						getTarget();
					}
					else {
						moveDirection = 'r';
						getTarget();
					}
				}

			}
			else if (targetx - movingTowards.getIntX() > 0 && targety - movingTowards.getIntY() < 0) {
				if (std::abs(targetx - movingTowards.getIntX()) > std::abs(targety - movingTowards.getIntY())) {
					if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos && moveDirection != 'u') {
						moveDirection = 'd';
						getTarget();
					}
					else if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos && moveDirection != 'r') {
						moveDirection = 'l';
						getTarget();
					}
					else if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos && moveDirection != 'l') {
						moveDirection = 'r';
						getTarget();
					}
					else {
						moveDirection = 'u';
						getTarget();
					}
				}
				else
				{
					
					if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos && moveDirection != 'r') {
						moveDirection = 'l';
						
						getTarget();
					}
					else if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos && moveDirection != 'u') {
						moveDirection = 'd';
						getTarget();
					}
					else if (TurnOptions[movingTowards.getCornerType()].find("u") != std::string::npos && moveDirection != 'd') {
						moveDirection = 'u';
						getTarget();
					}
					else {
						moveDirection = 'r';
						getTarget();
					}

				}
			}
			else if (targetx - movingTowards.getIntX() < 0 && targety - movingTowards.getIntY() > 0) {
				if (std::abs(targetx - movingTowards.getIntX()) > std::abs(targety - movingTowards.getIntY())) {
					if (TurnOptions[movingTowards.getCornerType()].find("u") != std::string::npos && moveDirection != 'd') {
						moveDirection = 'u';
						getTarget();
					}
					else if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos && moveDirection != 'l') {
						moveDirection = 'r';
						getTarget();
					}
					else if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos && moveDirection != 'r') {
						moveDirection = 'l';
						getTarget();
					}
					else {
						moveDirection = 'd';
						getTarget();
					}
				}
				else
				{
					if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos && moveDirection != 'l') {
						moveDirection = 'r';
						getTarget();
					}
					else if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos && moveDirection != 'u') {
						moveDirection = 'd';
						getTarget();
					}
					else if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos && moveDirection != 'r') {
						moveDirection = 'l';
						getTarget();
					}
					else {
						moveDirection = 'u';
						getTarget();
					}
				}
			}

			else {
				if (targetx - movingTowards.getIntX() == 0) {
					if (targety > movingTowards.getIntY()) {
						if (moveDirection != 'l') {
							if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos) {
								moveDirection = 'r';
								getTarget();
								return;
							}
						}
						if (moveDirection != 'u') {
							if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos) {
								moveDirection = 'd';
								getTarget();
								return;
							}
						}
							if (moveDirection != 'r') {
								if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos) {
									moveDirection = 'l';
									getTarget();
									return;
								}
							}
						if (moveDirection != 'd') {
							if (TurnOptions[movingTowards.getCornerType()].find("u") != std::string::npos) {
								moveDirection = 'u';
								getTarget();
								return;
							}
						}
						
						else {
							if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos) {
								moveDirection = 'r';
								getTarget();
								return;
							}
						}
					}
					if (targety < movingTowards.getIntY()) {
						if (moveDirection != 'r') {
							if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos) {
								moveDirection = 'l';
								getTarget();
								return;
							}
						}
						if (moveDirection != 'u') {
							if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos) {
								moveDirection = 'd';
								getTarget();
								return;
							}
						}
						if (moveDirection != 'd') {
							if (TurnOptions[movingTowards.getCornerType()].find("u") != std::string::npos) {
								moveDirection = 'u';
								getTarget();
								return;
							}
						}
						if (moveDirection != 'l') {
							if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos) {
								moveDirection = 'r';
								getTarget();
								return;
							}
						}
					}
					else {
						if (TurnOptions[movingTowards.getCornerType()].find("u") != std::string::npos && moveDirection != 'd') {
							moveDirection = 'u';
							getTarget();
							return;
						}
						else if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos && moveDirection != 'u') {
							moveDirection = 'd';
							getTarget();
							return;
						}
						else if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos && moveDirection != 'r') {
							moveDirection = 'l';
							getTarget();
							return;
						}
						else if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos && moveDirection != 'l') {
							moveDirection = 'r';
							getTarget();
							return;
						}
					}
				}
				if (targety - movingTowards.getIntY() == 0) {
					if (targetx > movingTowards.getIntX()) {
						if (moveDirection != 'u') {
							if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos) {
								moveDirection = 'd';
								getTarget();
								return;
							}
						}
						if (moveDirection != 'r') {
							if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos) {
								moveDirection = 'l';
								getTarget();
								return;
							}
						}
						if (moveDirection != 'l') {
							if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos) {
								moveDirection = 'r';
								getTarget();
								return;
							}
						}
						if (moveDirection != 'd') {
							if (TurnOptions[movingTowards.getCornerType()].find("u") != std::string::npos) {
								moveDirection = 'u';
								getTarget();
								return;
							}
						}
					}
					if (targetx < movingTowards.getIntX()) {
						if (moveDirection != 'd') {
							if (TurnOptions[movingTowards.getCornerType()].find("u") != std::string::npos) {
								moveDirection = 'u';
								getTarget();
								return;
							}
						}
						if (moveDirection != 'r') {
							if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos) {
								moveDirection = 'l';
								getTarget();
								return;
							}
						}
						if (moveDirection != 'l') {
							if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos) {
								moveDirection = 'r';
								getTarget();
								return;
							}
						}
						if (moveDirection != 'u') {
							if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos) {
								moveDirection = 'd';
								getTarget();
								return;
							}
						}
					}
					else {
						if (TurnOptions[movingTowards.getCornerType()].find("u") != std::string::npos && moveDirection != 'd') {
							moveDirection = 'u';
							getTarget();
							return;
						}
						else if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos && moveDirection != 'u') {
							moveDirection = 'd';
							getTarget();
							return;
						}
						else if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos && moveDirection != 'r') {
							moveDirection = 'l';
							getTarget();
							return;
						}
						else if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos && moveDirection != 'l') {
							moveDirection = 'r';
							getTarget();
							return;
						}
					}
				}
			}
		}
		else
		{
			
			srand(time(NULL));
			int index = rand() % 4;
			//std::cout << index << std::endl;
			if (index == 0) {
				if (TurnOptions[movingTowards.getCornerType()].find("u") != std::string::npos && moveDirection != 'd') {
					moveDirection = 'u';
					getTarget();
				}
				else if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos && moveDirection != 'u') {
						moveDirection = 'd';
						getTarget();
					}
				else if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos && moveDirection != 'r') {
					moveDirection = 'l';
					getTarget();
				}
				else if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos && moveDirection != 'l') {
					moveDirection = 'r';
					getTarget();
				}
			}
			if (index == 1) {
				if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos && moveDirection != 'u') {
					moveDirection = 'd';
					getTarget();
				}
				else if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos && moveDirection != 'r') {
					moveDirection = 'l';
					getTarget();
				}
				else if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos && moveDirection != 'l') {
					moveDirection = 'r';
					getTarget();
				}
				else if (TurnOptions[movingTowards.getCornerType()].find("u") != std::string::npos && moveDirection != 'd') {
					moveDirection = 'u';
					getTarget();
				}
			}
			if (index == 2) {
				 if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos && moveDirection != 'r') {
					moveDirection = 'l';
					getTarget();
				}
				else if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos && moveDirection != 'l') {
					moveDirection = 'r';
					getTarget();
				}
				else if (TurnOptions[movingTowards.getCornerType()].find("u") != std::string::npos && moveDirection != 'd') {
					moveDirection = 'u';
					getTarget();
				}
				else if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos && moveDirection != 'u') {
					moveDirection = 'd';
					getTarget();
				}
				
			}
			if (index == 3) {
				
				if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos && moveDirection != 'l') {
					moveDirection = 'r';
					getTarget();
				}
				else if (TurnOptions[movingTowards.getCornerType()].find("u") != std::string::npos && moveDirection != 'd') {
					moveDirection = 'u';
					getTarget();
				}
				else if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos && moveDirection != 'u') {
					moveDirection = 'd';
					getTarget();
				}
				else if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos && moveDirection != 'r') {
					moveDirection = 'l';
					getTarget();
				}
			}
		}

	}

	
	void teleportGhost(int d) {
		if (d == 3) {
			setPosition(Vector2(14, 27, 0));
			movingTowards.x = 14;
			movingTowards.y = 26;
			update = "";
		}
		if (d == 4) {
			setPosition(Vector2(14, 0, 0));
			movingTowards.x = 14;
			movingTowards.y = 1;
			update = "";
		}
	}

	void setTarget(int x, int y) {
		if (mode == 'a') {
			targetx = x;
			targety = y;
		}
		else if (mode == 'y') {
			targetx = 0;
			targety = 0;
			if (abs(movingTowards.getIntX() - targetx) < 3 && abs(movingTowards.getIntY() - targety) < 3) {
				mode = 'r';
			}
		}
		else if (mode == 'r') {
			targetx = 30;
			targety = 0;
			if (abs(movingTowards.getIntX() - targetx) < 3 && abs(movingTowards.getIntY() - targety) < 3) {
				mode = 'b';
			}
		}
		else if (mode == 'b') {
			targetx = 30;
			targety = 27;
			if (abs(movingTowards.getIntX() - targetx) < 3 && abs(movingTowards.getIntY() - targety) < 3) {
				mode = 'p';
			}
		}
		else if (mode == 'p') {
			targetx = 0;
			targety = 27;
			if (abs(movingTowards.getIntX() - targetx) < 3 && abs(movingTowards.getIntY() - targety) < 3) {
				mode = 'y';
			}
		}
		else if (mode == 's') {
			
		}

	}

	void moveGhost(float deltaTime, int playx, int playy,float playerX, float playerY) {
		//std::cout << "moving too: " <<movingTowards.x<<" , " <<movingTowards.y <<std::endl;
		playerx = playerX;
		playery = playerY;
		setTarget(playx, playy);
		if (moveDirection == 'u') {
			if (!reachedTarget()) {
				pSprite.move(0, -moveSpeed*deltaTime);
			}
			else {

				nextTarget();
			}
			//


		}
		else if (moveDirection == 'd') {
			if (!reachedTarget()) {
				pSprite.move(0, moveSpeed*deltaTime);
			}
			else {
				
				nextTarget();
			}
		}
		else if (moveDirection == 'l') {
			if (!reachedTarget()) {
				pSprite.move(-moveSpeed*deltaTime, 0);
			}
			else {
				
				nextTarget();
			}

		}

		else if (moveDirection == 'r') {
			if (!reachedTarget()) {
				pSprite.move(moveSpeed*deltaTime, 0);
			}
			else {
				nextTarget();
			}
		}
	}
	void rotateGhost(char direction) {
		if (direction == 'u') {
			pSprite.setRotation(-90);

		}
		else if (direction == 'd') {
			pSprite.setRotation(90);
		}
		else if (direction == 'l') {
			pSprite.setRotation(180);
		}
		else if (direction == 'r') {
			pSprite.setRotation(0);
		}
	}
	void NewDirection(char direction) {
		newMoveDirection = direction;
		if (moveDirection == 'u') {
			if (newMoveDirection == 'd') {
				moveDirection = 'd';
				getTarget();
				std::cout << "EARLY SWITCH" << std::endl;
			}
		}

		if (moveDirection == 'd') {
			if (newMoveDirection == 'u') {
				moveDirection = 'u';
				getTarget();
				std::cout << "EARLY SWITCH" << std::endl;
			}
		}
		if (moveDirection == 'l') {
			if (newMoveDirection == 'r') {
				moveDirection = 'r';
				getTarget();
				std::cout << "EARLY SWITCH" << std::endl;
			}
		}
		if (moveDirection == 'r') {
			if (newMoveDirection == 'l') {
				moveDirection = 'l';
				getTarget();
				std::cout << "EARLY SWITCH" << std::endl;
			}
		}

	}

	void Update() {
		//std::cout << (nextClock.getElapsedTime().asSeconds() > nextModeSeconds) << std::endl;
		if (nextClock.getElapsedTime().asSeconds() > nextModeSeconds) {
			
			if (nextMode == 'f') {
				freeze();
				return;
			}
			
			pSprite.setTexture(pTexture);
			mode = nextMode;
			moveSpeed = defaultSpeed;
			vulnerable = false;
		}
		
	}

	void updateBlock() {
		char tempX = (char)(movingTowards.getIntX() + 90);
		char tempY = (char)(movingTowards.getIntY() + 90);
		update = (std::string() + tempX) + tempY;
		//std::cout << "Getting the apple :" << update << std::endl;

	}
	//.setPosition(((j * 15 +7.5)*1.75), ((i * 15 + 7.5)*1.75));
	std::string getUpdate() { //"" means no update //"aa" represents what coordinate was reached
		float dx = abs(pSprite.getPosition().x - playerx);
		float dy = abs(pSprite.getPosition().y - playery);
		float distance = sqrt((dx*dx) + (dy*dy));
		

		if (distance < 15) {
			
			if (vulnerable ==0) {
				update = "kill";
			}
			else
			{
				update = "die";
				die();
				std::cout << update << std::endl;
			}
		}
		
		return update;
	}
	void clrUpdate() {
		update = "";
		
	}
	void die() {
		
		frozen = true;
		setPosition(Vector2(13, 14, 0));
		
		moveSpeed = 0;
	}
private:
	sf::Texture blueText;
	sf::Texture pTexture;
	sf::Sprite pSprite;

	Vector2 startPoint = Vector2(11, 14, 0);

	Vector2 movingTowards = Vector2(1, 21, 5);

	//acidently mixed the x and y value but im not going back into change them again
	Vector2 corners[75] = {
		Vector2(1,1,0),Vector2(1,6,5),Vector2(1,12,1),Vector2(1,15,0),Vector2(1,21,5),Vector2(1,26,1),
		Vector2(5,1,8),Vector2(5,6,4),Vector2(5,9,5),Vector2(5,12,6),Vector2(5,15,6),Vector2(5,18,5),Vector2(5,21,4),Vector2(5,26,7),
		Vector2(8,1,2),Vector2(8,6,7),Vector2(8,9,2),Vector2(8,12,1),Vector2(8,15,0),Vector2(8,18,3),Vector2(8,21,8),Vector2(8,26,3),
		Vector2(11,9,0),Vector2(11,12,6),Vector2(11,15,6),Vector2(11,18,1),
		Vector2(14,6,8),Vector2(14,9,7),Vector2(14,18,8),Vector2(14,21,7),
		Vector2(17,9,8),Vector2(17,18,7),
		Vector2(20,1,0),Vector2(20,6,4),Vector2(20,9,6),Vector2(20,12,1),Vector2(20,15,0),Vector2(20,18,6),Vector2(20,21,4),Vector2(20,26,1),
		Vector2(23,1,2),Vector2(23,3,1),Vector2(23,6,8),Vector2(23,9,5),Vector2(23,12,6),Vector2(23,15,6),Vector2(23,18,5),Vector2(23,21,7),Vector2(23,24,0),Vector2(23,26,3),
		Vector2(26,1,0),Vector2(26,3,6),Vector2(26,6,3),Vector2(26,9,2),Vector2(26,12,1),Vector2(26,15,0),Vector2(26,18,3),Vector2(26,21,2),Vector2(26,24,6),Vector2(26,26,1),
		Vector2(29,1,2),Vector2(29,12,6),Vector2(29,15,6),Vector2(29,26,3),
	};
	std::string TurnOptions[9] = {
		"dr","dl","ur","ul", //0,1,2,3
		"udlr",		//4
		"dlr","ulr",//5,6
		"udl","udr"	//7,8
	};

};
