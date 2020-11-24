#pragma once
#ifndef SHIELD
#define SHIELD
#include <SFML/Graphics.hpp>
#include <SFML/GRAPHICS/Rect.hpp>
#include "..//include//SoundManager.h"
#include "..//include//Explosion.h"

class Shield
{
public:

	Shield(int xPos, int yPos);
	sf::VertexArray quad;
	bool Intersects(sf::FloatRect rectangle);
	static void EnemyBulletExplosion(Shield& shield, Explosion& explosion, sf::Sprite& bullet, SoundManager& soundMan);
	static void PlayerBulletExplosion(Shield& shield, Explosion& explosion, sf::Sprite& bullet, SoundManager& soundMan);
};
#endif
