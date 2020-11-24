#include "..//include//Explosion.h"

Explosion::Explosion() {
	size = sf::Vector2f(40.f, 40.f);
	loadTexture(explosionTexture, explosionSprite, "explosion.png", size);
}
