#include "..//include/titleMenu.h"

TitleMenu::TitleMenu() {

	//Loading 
	if (!titleMusic.openFromFile(".\\assets\\sounds\\TitleScreen.wav"))
		throw -1; // error
	titleMusic.play();
	titleMusic.setLoop(true);


	//Title
	titleText.setFont(font);
	titleText.setString("SPACE INVADERS");
	titleText.setCharacterSize(100);
	titleText.setFillColor(sf::Color(255, 255, 255));
	titleText.setStyle(sf::Text::Bold);
	sf::FloatRect textRect = titleText.getLocalBounds();
	titleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	titleText.setPosition(sf::Vector2f(screenWidth / 2.0f, 100.f));

	//Subtitle
	subtitleText.setFont(font);
	subtitleText.setString("OSKAR KOJDER P2549004");
	subtitleText.setCharacterSize(30);
	subtitleText.setFillColor(sf::Color(255, 255, 255));
	subtitleText.setStyle(sf::Text::Italic);
	textRect = subtitleText.getLocalBounds();
	subtitleText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	subtitleText.setPosition(sf::Vector2f(screenWidth / 2.0f, 160.f));

	//Play Button
	playBtnText.setFont(font);
	playBtnText.setString("PLAY");
	playBtnText.setCharacterSize(60);
	playBtnText.setFillColor(sf::Color(0, 255, 0));
	textRect = playBtnText.getLocalBounds();
	playBtnText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	playBtnText.setPosition(sf::Vector2f(screenWidth / 2.0f, 220.f));

	//Exit Button
	
	exitBtnText.setFont(font);
	exitBtnText.setString("EXIT");
	exitBtnText.setCharacterSize(60);
	exitBtnText.setFillColor(sf::Color(255, 255, 255));
	textRect = exitBtnText.getLocalBounds();
	exitBtnText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	exitBtnText.setPosition(sf::Vector2f(screenWidth / 2.0f, 300.f));
}

void TitleMenu::ColorExit() {
	exitBtnText.setFillColor(sf::Color(0, 255, 0));
	playBtnText.setFillColor(sf::Color(255, 255, 255));
}
void TitleMenu::ColorPlay() {
	exitBtnText.setFillColor(sf::Color(255, 255, 255));
	playBtnText.setFillColor(sf::Color(0, 255, 0));
}
TitleMenu::~TitleMenu() {


}