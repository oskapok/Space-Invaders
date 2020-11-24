#include "..//include/Alien.h"

Alien::Alien(std::string alienName, sf::Texture &texture1, sf::Texture &texture2) {
	_texture1 = &texture1;
	_texture2 = &texture2;
	alive = true;
	size = sf::Vector2f(40, 40);
	loadTexture(*_texture1, alienSprite, alienName, size);
	alienName.resize(alienName.size() -5);
	loadOnlyTexture(*_texture2, alienName+"2.png");
}

void Alien::NextTexture() {
	alienSprite.setTexture(*_texture2);
}
void Alien::PreviousTexture() {
	alienSprite.setTexture(*_texture1);
}
void Alien::TakeDamage() {
	_texture1 = nullptr;
	_texture2 = nullptr;
	alive = false;
	alienSprite.setScale(0, 0);
}
