#pragma once
#ifndef TITLE_MENU
#define TITLE_MENU

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

extern sf::Font font;
extern const int screenWidth;
extern const int screenHeight;
class TitleMenu
{
public:
	TitleMenu();
	~TitleMenu();
	sf::Text titleText;
	sf::Text subtitleText;
	sf::Text playBtnText;
	sf::Text exitBtnText;
	sf::Music titleMusic;

	void ColorExit();
	void ColorPlay();
};
#endif
