#pragma once
#ifndef SOUND_MANAGER
#define SOUND_MANAGER
#include <SFML/Audio.hpp>

class SoundManager
{
public:
	sf::SoundBuffer bPlayerShoot;
	sf::SoundBuffer bEnemyShoot;
	sf::SoundBuffer bExplosion;
	sf::SoundBuffer bDamagePlayer;
	sf::SoundBuffer bUfo;
	sf::Sound playerShoot;
	sf::Sound enemyShoot;
	sf::Sound explosion;
	sf::Sound damagePlayer;
	sf::Sound ufo;

	SoundManager();
	void Play(std::string sound);
	void StopAllSounds();
};
#endif
