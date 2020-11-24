#pragma once
#ifndef UFO
#define UFO

#include <SFML/Graphics.hpp>
#include <iostream>
#include "..//include//textureloader.h"
class Ufo
{
public:
	bool alive;
	sf::Sprite ufoSprite;
	sf::Texture texture;
	sf::Vector2f size;

	Ufo();
	void Move();
	void TakeDamage();
};
#endif

