#include "..//include//SoundManager.h"


SoundManager::SoundManager() {


	bUfo.loadFromFile(".\\assets\\sounds\\ufo4.wav");
	ufo.setBuffer(bUfo);
	ufo.setLoop(true);

	bPlayerShoot.loadFromFile(".//assets//sounds//playerShoot.wav");

	playerShoot.setBuffer(bPlayerShoot);

	bEnemyShoot.loadFromFile(".\\assets\\sounds\\alienShoot.wav");
	enemyShoot.setBuffer(bEnemyShoot);

	bExplosion.loadFromFile(".\\assets\\sounds\\Explosion.wav");
	explosion.setBuffer(bExplosion);

	bDamagePlayer.loadFromFile(".\\assets\\sounds\\DamagePlayer.wav");
	damagePlayer.setBuffer(bDamagePlayer);


}

void SoundManager::Play(std::string sound) {

	if (sound == "ufo")
		ufo.play();

	if (sound == "playerShoot")
	{
		playerShoot.play();
	}

	if (sound == "enemyShoot")
		enemyShoot.play();

	if (sound == "explosion")
		explosion.play();

	if (sound == "damagePlayer")
		damagePlayer.play();
}

void SoundManager::StopAllSounds() {
	ufo.stop();

}