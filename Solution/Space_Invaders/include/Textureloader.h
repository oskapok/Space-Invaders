#pragma once
#ifndef TEXTURE_LOADER
#define TEXTURE_LOADER

#include <SFML/Graphics.hpp>

bool loadTexture(sf::Texture& tex, sf::Sprite& sprite, std::string sFileName, sf::Vector2f& size);
bool loadOnlyTexture(sf::Texture& tex, std::string sFileName);

#endif