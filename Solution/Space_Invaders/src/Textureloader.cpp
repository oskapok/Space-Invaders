#include "..//include/textureloader.h"

bool loadTexture(sf::Texture& tex, sf::Sprite& sprite, std::string sFileName, sf::Vector2f& size)
{
	bool bSuccess;
	bSuccess = tex.loadFromFile(".\\assets\\sprites\\" + sFileName);
	if (!bSuccess)
	{
		return false;
	}
	sprite.setScale(size.x / tex.getSize().x, size.y / tex.getSize().y);
	sprite.setOrigin(size.x / 2.f / sprite.getScale().x, size.y / 2.f / sprite.getScale().y);
	sprite.setTexture(tex);
	return true;
}
bool loadOnlyTexture(sf::Texture& tex, std::string sFileName)
{
	bool bSuccess;
	bSuccess = tex.loadFromFile(".\\assets\\sprites\\" + sFileName);
	if (!bSuccess)
	{
		return false;
	}

	return true;
}