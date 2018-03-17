#pragma once

#include "Vector2.h"

#include <iostream>
#include <SFML\Graphics.hpp>


class Player {

public:
	sf::Sprite pSprite;
	float moveSpeed = 118.0f;
	char moveDirection = 'l';
	char newMoveDirection = 'l';
	std::string update = "";
	Vector2 movingTowards = Vector2(23, 11, 6);
	Player() {
		//default
	}
	Player(std::string imgDirectory) {
		if (!pTexture.loadFromFile(imgDirectory)) {
			std::cerr << "Error\n";
		}
		pSprite.setTexture(pTexture);
		pSprite.setOrigin(78,78);
		setPosition(startPoint);
		
		//std::cout << movingTowards.getIntX();
		pSprite.setScale(.14, .14);
		
	}
	void freeze() {
		moveSpeed = 0;
	}
	void init() {
		moveSpeed = 118.0f;
		setPosition(startPoint);
		moveDirection = 'l';
		newMoveDirection = 'l';
		rotatePlayer('l');
		update = "";
		movingTowards = Vector2(23, 11, 6);
	}
	void drawPlayer(sf::RenderWindow &window) {
		window.draw(pSprite);
	}
	void setPosition(Vector2 pos) {
		pSprite.setPosition(((pos.y * 15 + 7.5) * 1.75), ((pos.x * 15+7.5) * 1.75));
		rotatePlayer(moveDirection);
	}

	void getTarget() {
		/*
		int temp;
		int min = 0;
		int save = 0;
		int max = 30;
		
		switch (moveDirection) {
			
		case 'u':
			temp = LastPos.getIntY();
			max = 0;
			save = 0;
			for (int i = 0; i < 75; i++) {
				if (corners[i].getIntY() != temp)
					continue;

				if (corners[i].getIntX() < LastPos.getIntX()) {
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
			temp = LastPos.getIntY();
			max = 30;
			save = 0;
			for (int i = 0; i < 75; i++) {
				if (corners[i].getIntY() != temp)
					continue;

				if (corners[i].getIntX() > LastPos.getIntX()) {
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
			
			temp = LastPos.getIntX();
			max = 0;
			save = 0;
			for (int i = 0; i < 75; i++) {
				if (corners[i].getIntX() != temp)
					continue;

				if (corners[i].getIntY() < LastPos.getIntY()) {
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
			temp = LastPos.getIntX();
			max = 30;
			save = 0;
			for (int i = 0; i < 75; i++) {
				if (corners[i].getIntX() != temp)
					continue;

				if (corners[i].getIntY() > LastPos.getIntY()) {
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

		switch (moveDirection) {

		case 'u':
			movingTowards.x--;
			rotatePlayer('u');
			break;

		case 'd':
			movingTowards.x++;
			rotatePlayer('d');
			break;

		case 'l':
			movingTowards.y--;
			rotatePlayer('l');
			break;

		case 'r':
			movingTowards.y++;
			rotatePlayer('r');
			break;
		}
	}

	bool reachedTarget() {
		//std::cout << moveDirection << std::endl;
		if (moveDirection == 'u') {
			if (pSprite.getPosition().y < (movingTowards.x * 15 + 14.5)*1.75) {
				updateBlock();
			}
			if (pSprite.getPosition().y < (movingTowards.x * 15 + 7.5)*1.75) {
				
				return true;
				
			}
		}
		else if (moveDirection == 'd') {
			if (pSprite.getPosition().y > (movingTowards.x * 15 + .5)*1.75) {
				updateBlock();
			}
			if (pSprite.getPosition().y > (movingTowards.x * 15 + 7.5)*1.75) {
				
				return true;
				
			}
		}
		else if (moveDirection == 'l') {
			if (pSprite.getPosition().x < (movingTowards.y * 15 +14.5)*1.75) {
				updateBlock();
			}
			if (pSprite.getPosition().x < (movingTowards.y * 15 + 7.5)*1.75) {
				
				return true;
			}
		}
		else if (moveDirection == 'r') {
			if (pSprite.getPosition().x > (movingTowards.y * 15 + .5)*1.75) {
				updateBlock();
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
				//std::cout << "We hit an intersection!" << std::endl;
				return true;
				
			}
		}

		return false;
	}

	void nextTarget() {

		if (isIntersection()) {
			switch (newMoveDirection) {

			case 'u':
				if (TurnOptions[movingTowards.getCornerType()].find("u") != std::string::npos) {
					moveDirection = 'u';
					
				}
				if (TurnOptions[movingTowards.getCornerType()].find(moveDirection) != std::string::npos) {
					getTarget();
				}

				break;

			case 'd':
				if (TurnOptions[movingTowards.getCornerType()].find("d") != std::string::npos) {
					moveDirection = 'd';
					
				}
				if (TurnOptions[movingTowards.getCornerType()].find(moveDirection) != std::string::npos) {
					getTarget();
				}
				break;

			case 'l':
				if (TurnOptions[movingTowards.getCornerType()].find("l") != std::string::npos) {
					moveDirection = 'l';
					//std::cout << "I can continue Left" << std::endl;
					
				}
				if (TurnOptions[movingTowards.getCornerType()].find(moveDirection) != std::string::npos) {
					getTarget();
				}
				break;

			case 'r':
				if (TurnOptions[movingTowards.getCornerType()].find("r") != std::string::npos) {
					moveDirection = 'r';
					
				}
				if (TurnOptions[movingTowards.getCornerType()].find(moveDirection) != std::string::npos) {
					getTarget();
				}
				break;
			}
		}
		else {
			//std::cout << "Not an intersection" << std::endl;
			getTarget();
		}
		/*switch (moveDirection) {

		case 'u':

			break;

		case 'd':
			break;

		case 'l':
			break;

		case 'r':
			break;


		}
		*/
		}

	void teleportPlayer(int d) {
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

	void movePlayer(float deltaTime) {
		//std::cout << "moving too: " <<movingTowards.x<<" , " <<movingTowards.y <<std::endl;
		
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
			}else {
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
	void rotatePlayer(char direction) {
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
				 //std::cout << "EARLY SWITCH" << std::endl;
			 }
		 }

		 if (moveDirection == 'd') {
			 if (newMoveDirection == 'u') {
				 moveDirection = 'u';
				 getTarget();
				 //std::cout << "EARLY SWITCH" << std::endl;
			 }
		 }
		 if (moveDirection == 'l') {
			 if (newMoveDirection == 'r') {
				 moveDirection = 'r';
				 getTarget();
				// std::cout << "EARLY SWITCH" << std::endl;
			 }
		 }
		 if (moveDirection == 'r') {
			 if (newMoveDirection == 'l') {
				 moveDirection = 'l';
				 getTarget();
				 //std::cout << "EARLY SWITCH" << std::endl;
			 }
		 }

	}

	void updateBlock() {
		char tempX = (char)(movingTowards.getIntX()+90);
		char tempY = (char)(movingTowards.getIntY()+90);
		update = (std::string()+tempX) + tempY;
		//std::cout << "Getting the apple :" << update << std::endl;

	}
	std::string getUpdate() { //"" means no update //"aa" represents what coordinate was reached

		return update;
	}
	void clrUpdate() {
		update = "";
	}
private:
	sf::Texture pTexture;
	

	Vector2 startPoint = Vector2(23,12,0);

	

	//acidently mixed the x and y value but im not going back into change them again
	Vector2 corners[75] ={
	Vector2(1,1,0),Vector2(1,6,5),Vector2(1,12,1),Vector2(1,15,0),Vector2(1,21,5),Vector2(1,26,1),
	Vector2(5,1,8),Vector2(5,6,4),Vector2(5,9,5),Vector2(5,12,6),Vector2(5,15,6),Vector2(5,18,5),Vector2(5,21,4),Vector2(5,26,7),
	Vector2(8,1,2),Vector2(8,6,7),Vector2(8,9,2),Vector2(8,12,1),Vector2(8,15,0),Vector2(8,18,3),Vector2(8,21,8),Vector2(8,26,3),
	Vector2(11,9,0),Vector2(11,12,6),Vector2(11,15,6),Vector2(11,18,1),
	Vector2(14,6,4),Vector2(14,9,7),Vector2(14,18,8),Vector2(14,21,4),
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
