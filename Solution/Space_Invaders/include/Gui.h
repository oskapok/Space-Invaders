#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "..//include//Textureloader.h"

class GUI
{
public :
	sf::Text scoreText;
	sf::Text scoreValue;
	sf::Text livesText;
	sf::Text livesValue;
	sf::Text gameOverText;

	int lives;
	int score;
	void UpdateLives();
	void UpdateScore(float points);
	void ShowGameOver(sf::Font& font, bool& showEndGameScreen);
	GUI(sf::Font& font);
};


