#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Vector2.h"
#include "MapControl.h"
#include "Ghost.h"
#include "GhostMgr.h"
#include <math.h>


//Vector2 mapGrid(27, 31);

sf::RenderWindow window(sf::VideoMode(900, 1000), "Pacman-Iconic", sf::Style::Titlebar | sf::Style::Close);
sf::Clock deltaClock;
sf::Time deltaTime;
sf::Clock shittyClock;
sf::Font myFont;
sf::Text ScoreT;
sf::Text ScoreN;
sf::Text bigTex;
MapControl map;
sf::Text ScoreMsg;
std::string message ="";

Player player("imgs/Pacman.png");
GhostMgr ghostMgr = GhostMgr();
int lives =3;
int scorev = 0;
int total = 0;
std::string temp;
int killMode = 0;
int tempKills = 0;
int level = 1;
bool waintingContinue = false;
void init();

void nextLevelMessage();

void freeze() {
	player.freeze();
	ghostMgr.freeze();

}

void resetScene() {
	player.init();
	ghostMgr.init();
}
void Die() {
	ghostMgr.freeze();
	player.freeze();
}
void RestartGame() {
	init();
	map.reset();
	resetScene();
}
void levelUp() {
	map.reset();
	resetScene();
	level++;
	killMode = 0;
	tempKills = 0;
	waintingContinue = false;
}
void init() {
	//map.drawMap(window);
	waintingContinue = false;
	level = 1;
	lives = 3;
	scorev = 0;
	killMode = 0;
	tempKills = 0;
	message = "";
	ScoreT.setString("Score:");
	ScoreT.setFont(myFont);
	ScoreT.setCharacterSize(24);
	ScoreT.setColor(sf::Color::White);
	ScoreT.setPosition(0, 810);
	ScoreN.setString("000");
	ScoreN.setFont(myFont);
	ScoreN.setCharacterSize(24);
	ScoreN.setColor(sf::Color::White);
	ScoreN.setPosition(80, 810);
	ScoreMsg.setString("");
	ScoreMsg.setFont(myFont);
	ScoreMsg.setCharacterSize(36);
	ScoreMsg.setColor(sf::Color::Red);
	ScoreMsg.setPosition(200, 810);
	total = 0;
}
void DisplayMessage();
void addMessage(std::string);
int main() {

	if (!myFont.loadFromFile("arial.ttf"))
	{
		std::cerr << "Error\n";
	}
	init();




	


	while (window.isOpen()) {

		sf::Event Event;

		while (window.pollEvent(Event)) {

			switch (Event.type) {

			case sf::Event::Closed:
				window.close();

			case sf::Event::KeyReleased:
				if (Event.key.code == sf::Keyboard::Escape) {
					RestartGame();
				}
				if (Event.key.code == sf::Keyboard::Return){
					resetScene();
				}
				if (Event.key.code == sf::Keyboard::F) {
					if(waintingContinue)
						levelUp();
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				player.NewDirection('u');

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				player.NewDirection('d');


			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				player.NewDirection('l');


			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				player.NewDirection('r');


			}



		}
		window.clear();
		map.drawMap(window);

		ghostMgr.drawGhost(window);
		float delta = deltaTime.asSeconds();
		ghostMgr.moveGhost(delta, player.movingTowards.getIntX(), player.movingTowards.getIntY(), player.pSprite.getPosition().x, player.pSprite.getPosition().y);

		player.movePlayer(delta);

		player.drawPlayer(window);

		temp = ghostMgr.getUpdate();

		if (tempKills > 3) {
			tempKills = 0;
		}
		if (shittyClock.getElapsedTime().asSeconds() > 10) {
			tempKills = 0;
		}

		if (temp != "") {
			std::cout << temp << std::endl;
			if (temp == "kill") {
				//std::cout << "player died" << std::endl;
				Die();
			}
			if (temp == "die") {
				tempKills++;
				std::cout << tempKills << std::endl;
				scorev += 100 * pow(2,tempKills);
				addMessage(("+" +(std::to_string((int)(100 * pow(2, tempKills)))) ));
				
				
				ghostMgr.unFreeze();
			}
			
		}
		

		//checkUpdates
	
		temp = "";
		temp = player.getUpdate();
		if (temp != "") {
			int tempX = 0; int tempY = 0; int tempT = 0;

			tempX = static_cast<int>(temp[0]) - 90;
			tempY = static_cast<int>(temp[1]) - 90;
			tempT = map.eatBlock(tempX, tempY);
			//std::cout << tempT << std::endl;
			if (tempT == 1) {
				total++;
				scorev += 10;
				if (total > 245) {
					freeze();
					waintingContinue = true;
					total = 0;
				}
			}
			else if (tempT == 2) {
				//std::cout << "Plus 10 points AND SUPER POWER!" << std::endl;
				tempKills = 0;
				killMode = 1;
				total++;
				scorev += 50;
				if (total > 245) {
					freeze();
					waintingContinue = true;
					total = 0;
				}
				ghostMgr.goBlue();
				shittyClock.restart();
			}
			else if (tempT == 3) {
				player.teleportPlayer(3);
			}
			else if (tempT == 4) {
				player.teleportPlayer(4);
			}


		}
		player.clrUpdate();
		ghostMgr.clrUpdate();
		ScoreN.setString(std::to_string(scorev));
		window.draw(ScoreN);
		window.draw(ScoreT);
		DisplayMessage();
		if (waintingContinue) {
			nextLevelMessage();
		}
		window.display();
		deltaTime = deltaClock.restart();
	}

	

}
void addMessage(std::string msg) {
	message = ( msg + "\n" + message);
}

void nextLevelMessage() {
	bigTex.setString("Level Up! Press f to continue.");
	bigTex.setFont(myFont);
	bigTex.setCharacterSize(54);
	bigTex.setColor(sf::Color::Red);
	bigTex.setPosition(100, 200);
	window.draw(bigTex);
}

void DisplayMessage() {
	ScoreMsg.setString(message);
	window.draw(ScoreMsg);
}

