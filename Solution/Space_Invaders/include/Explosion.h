#pragma once
#ifndef EXPLOSION
#define EXPLOSION

#include <SFML/Graphics.hpp>
#include <iostream>
#include "..//include//textureloader.h"


class Explosion
{
public:
	sf::Texture explosionTexture;
	sf::Sprite explosionSprite;
	sf::Vector2f size;
	Explosion();
};
#endif

