#include "..//include/Gui.h"

GUI::GUI(sf::Font &font) {

	scoreText.setFont(font);
	scoreText.setString("SCORE");
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color(255, 255, 255));
	scoreText.setPosition(sf::Vector2f(20, 10));

	scoreValue.setFont(font);
	scoreValue.setString("000");
	scoreValue.setCharacterSize(50);
	scoreValue.setFillColor(sf::Color(255, 255, 255));
	scoreValue.setPosition(sf::Vector2f(160, 10));

	livesText.setFont(font);
	livesText.setString("LIVES");
	livesText.setCharacterSize(50);
	livesText.setFillColor(sf::Color(255, 255, 255));
	livesText.setPosition(sf::Vector2f(1100, 10));

	livesValue.setFont(font);
	livesValue.setString("3");
	livesValue.setCharacterSize(50);
	livesValue.setFillColor(sf::Color(255, 255, 255));
	livesValue.setPosition(sf::Vector2f(1235, 10));

	lives = 3;
	score = 0;
}

void GUI::UpdateLives() {
	if (lives >= 1) {
		lives--;
	}
	livesValue.setString(std::to_string(lives));
}
void GUI::UpdateScore(float points) {
	score += points;
	std::string temp;
	if (score < 100)
		temp = "0" + std::to_string(score);
	else
		temp = std::to_string(score);
	scoreValue.setString(temp);
}

void GUI::ShowGameOver(sf::Font &font, bool &showEndGameScreen) {

	showEndGameScreen = true;
	gameOverText.setFont(font);
	gameOverText.setString("GAME OVER");
	gameOverText.setCharacterSize(100);
	gameOverText.setFillColor(sf::Color(255, 255, 255));
	sf::FloatRect textRect = gameOverText.getLocalBounds();
	gameOverText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	gameOverText.setPosition(sf::Vector2f(1280 / 2.0f, 100.f));
	scoreText.setPosition(440, 300);
	scoreValue.setPosition(640, 300);
	livesValue.setPosition(300, 400);
	livesValue.setString("PRESS SPACE TO PLAY AGAIN");
}
