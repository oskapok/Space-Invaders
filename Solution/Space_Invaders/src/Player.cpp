#include "../include/Player.h"


 Player::Player() {
	 loadTexture(playerTexture, playerSprite, textFileName, size);
	 lives = 3;
	 playerSpeed = 7.f;
}

 void Player::Move(float direction) {
	 playerSprite.move(direction * playerSpeed ,0);
 }

 void Player::Shoot(sf::Sprite &bulletSprite) {
	 bulletSprite.setPosition(playerSprite.getPosition());
	 canShoot = false;
 }
 void Player::TakeDamage() {
	 lives--;
	 if (lives < 1) 
	 {
		 playerSprite.setScale(0, 0);
	 }
 }