#include "..//include/Ufo.h"

Ufo::Ufo() {
	alive = false;
	size = sf::Vector2f(50, 50);
	loadTexture(texture, ufoSprite, "ufo.png", size);
	ufoSprite.setPosition(1350, 30);
}
void Ufo::TakeDamage() {
	alive = false;
	ufoSprite.setPosition(1350, 30);
}
void Ufo::Move() {
	alive = true;
}