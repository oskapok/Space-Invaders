#pragma once
#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>
#include <iostream>
#include "..//include//textureloader.h"

class Player
{
public:
	bool canShoot;
	int lives;
	float playerSpeed;
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	sf::Vector2f size = sf::Vector2f(40.f, 40.f);
	std::string textFileName = "Ship.png";

	Player();
	void Move(float direction);
	void Shoot(sf::Sprite& bulletSprite);
	void TakeDamage();

};
#endif

