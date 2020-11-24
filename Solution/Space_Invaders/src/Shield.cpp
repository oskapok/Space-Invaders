#include "..//include/Shield.h"
#include <iostream>

Shield::Shield( int xPos, int yPos) {
	quad =  sf::VertexArray(sf::Quads, 32);

	quad[0].position = sf::Vector2f(0, 10);
	quad[1].position = sf::Vector2f(30, 0);
	quad[2].position = sf::Vector2f(30, 30);
	quad[3].position = sf::Vector2f(0, 30);

	quad[4].position = sf::Vector2f(30, 0);
	quad[5].position = sf::Vector2f(60, 0);
	quad[6].position = sf::Vector2f(60, 30);
	quad[7].position = sf::Vector2f(30, 30);

	quad[8].position = sf::Vector2f(60, 0);
	quad[9].position = sf::Vector2f(90, 0);
	quad[10].position = sf::Vector2f(90, 30);
	quad[11].position = sf::Vector2f(60, 30);

	quad[12].position = sf::Vector2f(90, 0);
	quad[13].position = sf::Vector2f(120, 10);
	quad[14].position = sf::Vector2f(120, 30);
	quad[15].position = sf::Vector2f(90, 30);

	quad[16].position = sf::Vector2f(0, 30);
	quad[17].position = sf::Vector2f(60, 30);
	quad[18].position = sf::Vector2f(30, 50);
	quad[19].position = sf::Vector2f(0, 50);

	quad[20].position = sf::Vector2f(60, 30);
	quad[21].position = sf::Vector2f(120, 30);
	quad[22].position = sf::Vector2f(120, 50);
	quad[23].position = sf::Vector2f(90, 50);

	quad[24].position = sf::Vector2f(0, 50);
	quad[25].position = sf::Vector2f(30, 50);
	quad[26].position = sf::Vector2f(30, 70);
	quad[27].position = sf::Vector2f(0, 70);

	quad[28].position = sf::Vector2f(90, 50);
	quad[29].position = sf::Vector2f(120, 50);
	quad[30].position = sf::Vector2f(120, 70);
	quad[31].position = sf::Vector2f(90, 70);

	for (int i = 0; i < 32; i++)
	{
		quad[i].color = sf::Color::Green;
		quad[i].position.x += xPos;
		quad[i].position.y += yPos;
	}

}
bool Shield::Intersects(sf::FloatRect rectangle) {

	for (int i = 0; i < 8; i++)
	{
		int pos = i * 4;
		if (rectangle.left < quad[pos].position.x + (quad[pos+1].position.x - quad[pos].position.x) &&
			rectangle.left + rectangle.width > quad[pos].position.x &&
			rectangle.top < quad[pos].position.y + (quad[pos + 2].position.y - quad[pos+1].position.y) &&
			rectangle.top + rectangle.height > quad[pos].position.y)
		{
			if (quad[pos].color == sf::Color::Transparent)
				return false;

			quad[pos].color = sf::Color::Transparent;
			quad[pos+1].color = sf::Color::Transparent;
			quad[pos+2].color = sf::Color::Transparent;
			quad[pos+3].color = sf::Color::Transparent;
			return true;
		}

	}
	return false;
}
void Shield::EnemyBulletExplosion(Shield& shield, Explosion &explosion, sf::Sprite& bullet, SoundManager& soundMan) {
	explosion.explosionSprite.setPosition(bullet.getPosition());
	soundMan.Play("explosion");
	bullet.setPosition(0, 1000);
}

void Shield::PlayerBulletExplosion(Shield& shield, Explosion& explosion, sf::Sprite& bullet, SoundManager& soundMan) {
	explosion.explosionSprite.setPosition(bullet.getPosition());
	soundMan.Play("explosion");
	bullet.setPosition(0, -20);
}