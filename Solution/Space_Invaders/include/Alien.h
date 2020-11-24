#pragma once
#ifndef ALIEN
#define ALIEN

#include <SFML/Graphics.hpp>
#include <iostream>
#include "..//include//textureloader.h"
class Alien
{
private:
	sf::Texture* _texture1;
	sf::Texture* _texture2;
public:
	bool alive;
	sf::Sprite alienSprite;
	sf::Vector2f size;
	Alien(std::string alienName, sf::Texture& texture1, sf::Texture& texture2);
	void NextTexture();
	void PreviousTexture();
	void TakeDamage();
};
#endif

