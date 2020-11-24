#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include <algorithm>
#include "../include/Player.h"
#include "..//include//Textureloader.h"
#include "..//include//Gui.h"
#include "..//include/Alien.h"
#include "..//include//AlienRow.h"
#include "..//include//Explosion.h"
#include "..//include/Shield.h"
#include "..//include//SoundManager.h"
#include "..//include/Ufo.h"
#include "..//include/TitleMenu.h"

using namespace std;

//setting global variables
sf::Font font;
const int screenWidth = 1280;
const int screenHeight = 720;

int main()
{
	//Loading Font
	if (!font.loadFromFile(".\\assets\\fonts\\unifont.ttf"))
	{
		cout << "Cannot load font";
		return 0;
	}

	//Setting window icon
	sf::Image icon;
	icon.loadFromFile("assets\\sprites\\icon.png");

	//Setting up window
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Space Invaders", sf::Style::Titlebar | sf::Style::Close);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // Set window icon. 
	window.setPosition(sf::Vector2i(100, 100)); // Set the position of the window to 100,100 relative to the desktop.
	window.setFramerateLimit(60); // Set the limit of the the number of frames per second
	
	//Time management
	sf::Clock timer; 
	float frameInterval = 1000000.0f / 6000000.f; // Frame interval in microseconds
	sf::Color bgColor = sf::Color(0, 0, 0, 255);// Background color

	//Title Menu
	TitleMenu titleMenu;
	
	//Declaring game states
	bool exitApp = false;
	bool runGame = false;
	bool showEndGameScreen = false;

Start:

	//Initializing GUI
	GUI gui(font);

	//Initializing Player
	Player player;
	player.playerSprite.setPosition(screenWidth / 2.f, 680);

	//Declaring alien textures 
	sf::Texture alienA1;
	sf::Texture alienA2;
	sf::Texture alienB1;
	sf::Texture alienB2;
	sf::Texture alienC1;
	sf::Texture alienC2;

	//Initializing Aliens
	Alien alien1("InvaderC1.png", alienC1, alienC2);
	AlienRow row1(alien1);
	row1.SetScore(40.f);

	Alien alien2("InvaderB1.png", alienB1, alienB2);
	AlienRow row2(alien2);
	row2.SetScore(20.f);
	AlienRow row3(alien2);
	row3.SetScore(20.f);

	Alien alien3("InvaderA1.png", alienA1, alienA2);
	AlienRow row4(alien3);
	row4.SetScore(10.f);
	AlienRow row5(alien3);
	row5.SetScore(10.f);

	int xPos = 0;

	//Setting Aliens Position
		for (size_t i = 0; i < 55; i++)
	{
		if (xPos > 10)
			xPos = 0;

		if (i < 11)
			row1.array[xPos].alienSprite.setPosition(xPos * 50 + 400, 100);

		if (i >= 11 && i < 22)
			row2.array[xPos].alienSprite.setPosition(xPos * 50 + 400, 150);

		if (i >= 22 && i < 33)
			row3.array[xPos].alienSprite.setPosition(xPos * 50 + 400, 200);

		if (i >= 33 && i < 44)
			row4.array[xPos].alienSprite.setPosition(xPos * 50 + 400, 250);

		if (i >= 44 && i < 55)
			row5.array[xPos].alienSprite.setPosition(xPos * 50 + 400, 300);
		xPos++;
	}

	//Array of alive alien adresses
	std::vector<Alien*> aliens;

	for (int i = 0; i < 11; i++)
	{
		aliens.emplace_back(&row1.array[i]);
		aliens.emplace_back(&row2.array[i]);
		aliens.emplace_back(&row3.array[i]);
		aliens.emplace_back(&row4.array[i]);
		aliens.emplace_back(&row5.array[i]);
	}

	//Creating pointers to rows
	AlienRow* currentRow = &row5;
	AlienRow* rowPointer = &row1;


	//Alien Shooting Variables
	sf::Clock ShootTimer;
	int shootTime = 3;
	float alienWaitTime = 100000.f;
	bool canAlienShoot = true;




	//Random Numbers generator for some events
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> enemyWait(0.4, 1.5);
	std::uniform_int_distribution<> ufoWait(10, 40);



	//Initializing Explosions
	Explosion explosion1;
	Explosion explosion2;
	sf::Clock ExplosionTimer;

	//Initializing Shields
	Shield shield1(100,560);
	Shield shield2(400, 560);
	Shield shield3(700, 560);
	Shield shield4(1000, 560);

	//Initializing Ufo
	Ufo ufo;
	int ufoTime = 20;
	sf::Clock ufoTimer;


	//Player bullet
	sf::Sprite playerBullet;
	sf::Texture bulletTexture;
	sf::Vector2f bulletSize = sf::Vector2f(6.f, 24.f);
	loadTexture(bulletTexture, playerBullet, "Bullet.png", bulletSize);
	playerBullet.setPosition(0, -50);


	//Enemy bullet
	sf::Sprite enemyBullet;
	loadTexture(bulletTexture, enemyBullet, "Bullet.png", bulletSize);
	enemyBullet.setPosition(0, 800);

	//Music
	 sf::Music defaultMusic;
	 if (!defaultMusic.openFromFile(".\\assets\\sounds\\Ether_Oar.ogg"))
		 return -1; // error
	 defaultMusic.setLoop(true);
	 defaultMusic.setVolume(20);
	 if (runGame)
		 defaultMusic.play();

	 //Initializing Sound Manager
	 SoundManager soundManager;

	 while (window.isOpen())
	 {
		 //Title Screen Loop
		 while (!runGame)
		 {
			 sf::Event event;
			 while (window.pollEvent(event))
			 {
				 // User has pressed the close button
				 if (event.type == sf::Event::Closed)
				 {
					 window.close();
					 return 0;
				 }
				 //Title screen Keys
				 if (event.type == sf::Event::KeyPressed)
				 {
					 if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
					 {
						 titleMenu.ColorPlay();
						 exitApp = false;
					 }
					 if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
					 {
						 titleMenu.ColorExit();
						 exitApp = true;
					 }
					 if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Enter)
					 {
						 if (exitApp)
							 exit(0);
						 else
						 {
							 titleMenu.titleMusic.stop();
							 runGame = true;
							 defaultMusic.play();
						 }

					 }
				 }

			 }
			 window.clear(bgColor);
			 window.draw(titleMenu.titleText);
			 window.draw(titleMenu.playBtnText);
			 window.draw(titleMenu.exitBtnText);
			 window.draw(titleMenu.subtitleText);
			 window.display();
		 }

		 //Game Loop
		 sf::Event event;
		 while (window.pollEvent(event))
		 {
			 if (event.type == sf::Event::Closed)
				 window.close();
			 if (event.type == sf::Event::KeyPressed)
			 { 
				 if (event.key.code == sf::Keyboard::Space)
				 {
					 //Restart game  
					 if (showEndGameScreen) 
					 {
						 showEndGameScreen = false;
						 goto Start;
					 }
				 }

			 }
		 }

		 //Player is still playing
		 if (!showEndGameScreen)
		 {
			 //Calculate Time events
			 sf::Time elapsedTime = timer.getElapsedTime();
			 sf::Time elapsedShootTime = ShootTimer.getElapsedTime();
			 sf::Time elapsedExplosionTime = ExplosionTimer.getElapsedTime();
			 sf::Time elapsedUfoTime = ufoTimer.getElapsedTime();

			 //Show ufo if its time for that
			 if (elapsedUfoTime.asSeconds() > ufoTime && !ufo.alive)
			 {
				 ufo.Move();
				 soundManager.Play("ufo");
				 ufoTime = ufoWait(gen); //Generate when ufo comes next
				 ufoTimer.restart();
			 }

			 //Alien Shooting
			 if (elapsedShootTime.asSeconds() > shootTime && canAlienShoot)
			 {
				 soundManager.Play("enemyShoot");
				 std::uniform_int_distribution<> randomAlien(0, aliens.size()-1); //Random alive aliens adresses
				 enemyBullet.setPosition(aliens[randomAlien(gen)]->alienSprite.getPosition());//Pick random alive alien and spawn bullet there
				 shootTime = enemyWait(gen); //Generate when next shoot is going to happen
				 ShootTimer.restart();
				 canAlienShoot = false;
			 }

			 //Clear any happening explosions
			 if (elapsedExplosionTime.asSeconds() > 0.3)
			 {
				 explosion1.explosionSprite.setPosition(0, -20);
				 explosion2.explosionSprite.setPosition(0, -20);
				 ExplosionTimer.restart();
			 }

			 //Code running every frame
			 if (elapsedTime.asMicroseconds() > frameInterval)
			 {
				 //Ufo movement
				 if (ufo.alive && ufo.ufoSprite.getPosition().x > -20)
					 ufo.ufoSprite.move(-3, 0);
				 else
				 {
					 ufo.TakeDamage();
					 soundManager.ufo.stop();
				 }

				 //Bullets movement
				 if (playerBullet.getPosition().y > -20)
				 {
					 playerBullet.move(0, -10.f);
				 }
				 else if (playerBullet.getPosition().y <= -20)
				 {
					 player.canShoot = true;
				 }

				 if (enemyBullet.getPosition().y < screenHeight + 20)
				 {
					 enemyBullet.move(0, 10.f);
				 }
				 else
				 {
					 canAlienShoot = true;
				 }

				 //Player with enemy bullet collision
				 if (player.playerSprite.getGlobalBounds().intersects(enemyBullet.getGlobalBounds()))
				 {
					 explosion2.explosionSprite.setPosition(enemyBullet.getPosition());
					 soundManager.Play("damagePlayer");
					 player.TakeDamage();
					 enemyBullet.setPosition(0, 1000);
					 gui.UpdateLives();
					 if (player.lives < 1)
					 {
						 showEndGameScreen = true;
						 gui.ShowGameOver(font, showEndGameScreen);
					 }
				 }

				 //Player bullet with enemy bullet collision
				 if (playerBullet.getGlobalBounds().intersects(enemyBullet.getGlobalBounds()))
				 {
					 explosion1.explosionSprite.setPosition(enemyBullet.getPosition());
					 soundManager.Play("explosion");
					 enemyBullet.setPosition(0, 1000);
					 playerBullet.setPosition(0, -20);
				 }

				 //Player bullet with ufo collision
				 if (playerBullet.getGlobalBounds().intersects(ufo.ufoSprite.getGlobalBounds()))
				 {
					 ufo.TakeDamage();
					 gui.UpdateScore(300);
					 soundManager.ufo.stop();
					 explosion1.explosionSprite.setPosition(ufo.ufoSprite.getPosition());
					 soundManager.Play("explosion");
					 playerBullet.setPosition(0, -20);
				 }

				 //Each bullet with each shield collision
				if (shield1.Intersects(playerBullet.getGlobalBounds()))
					shield1.PlayerBulletExplosion(shield1, explosion1, playerBullet, soundManager);

				if (shield1.Intersects(enemyBullet.getGlobalBounds()))
					shield1.EnemyBulletExplosion(shield1, explosion2, enemyBullet, soundManager);

				if (shield2.Intersects(playerBullet.getGlobalBounds()))
					shield2.PlayerBulletExplosion(shield2, explosion1, playerBullet, soundManager);

				if (shield2.Intersects(enemyBullet.getGlobalBounds()))
					shield2.EnemyBulletExplosion(shield2, explosion2, enemyBullet, soundManager);

				if (shield3.Intersects(playerBullet.getGlobalBounds()))
					shield3.PlayerBulletExplosion(shield3, explosion1, playerBullet, soundManager);

				if (shield3.Intersects(enemyBullet.getGlobalBounds()))
					shield3.EnemyBulletExplosion(shield3, explosion2, enemyBullet, soundManager);

				if (shield4.Intersects(playerBullet.getGlobalBounds()))
					shield4.PlayerBulletExplosion(shield4, explosion1, playerBullet, soundManager);

				if (shield4.Intersects(enemyBullet.getGlobalBounds()))
					shield4.EnemyBulletExplosion(shield4, explosion2, enemyBullet, soundManager);
				 

				//Aliens with player bullet collision
				 for (int i = 0; i < 5; i++)
				 {
					 int alienPos = 0;
					 switch (i)//switch that points to other row each iteration.
					 {
					 case 0:
						 rowPointer = &row1;
						 break;
					 case 1:
						 rowPointer = &row2;
						 break;
					 case 2:
						 rowPointer = &row3;
						 break;
					 case 3:
						 rowPointer = &row4;
						 break;
					 case 4:
						 rowPointer = &row5;
						 break;
					 }
					 for (int j = rowPointer->mostLeftAlien; j <= rowPointer->mostRightAlien; j++)
					 {
						 if (rowPointer->array[j].alienSprite.getGlobalBounds().intersects(playerBullet.getGlobalBounds())) //If alien was hit
						 {
							 rowPointer->array[j].TakeDamage();
							 soundManager.Play("explosion");
							 ExplosionTimer.restart();
							 explosion1.explosionSprite.setPosition(rowPointer->array[j].alienSprite.getPosition());
							 aliens.erase(std::remove(aliens.begin(), aliens.end(), &rowPointer->array[j]), aliens.end());//erase it from alive array
							 alienWaitTime -= 1680.f; //Decrase wait time for movenet = aliens descend faster
							 gui.UpdateScore(rowPointer->scoreValue);//Update score on GUI
							 playerBullet.setPosition(0, -20);//Move bullet off screen

							 //Most left alien checking 
							 if (j == rowPointer->mostLeftAlien)
							 {
								 int restInColumn = 0;
								 int rowX = j;
								 while (restInColumn < 1)//Checking if any aliens are alive in column
								 {
									 if (row1.array[rowX].alive)
										 restInColumn++;
									 if (row2.array[rowX].alive)
										 restInColumn++;
									 if (row3.array[rowX].alive)
										 restInColumn++;
									 if (row4.array[rowX].alive)
										 restInColumn++;
									 if (row5.array[rowX].alive)
										 restInColumn++;
									 if (restInColumn == 0)//If no aliens alive in column
									 {
										 if (rowX <= rowPointer->mostRightAlien)//If next column exist
											 rowX++;//Go there 
										 else
										 {
											 //Player won
											 gui.ShowGameOver(font, showEndGameScreen);
											 gui.gameOverText.setString("YOU WIN");
											 break;
										 }
									 }
								 
								 }
								 //Udpate all rows
								 row1.mostLeftAlien = rowX;
								 row2.mostLeftAlien = rowX;
								 row3.mostLeftAlien = rowX;
								 row4.mostLeftAlien = rowX;
								 row5.mostLeftAlien = rowX;
							 }
							 //Most right alien checking 
							 if (j == rowPointer->mostRightAlien)
							 {
								 int restInColumn = 0;
								 int rowX = j;
								 while (restInColumn < 1) //Checking if any aliens are alive in column
								 {
									 if (row1.array[rowX].alive)
										 restInColumn++;
									 if (row2.array[rowX].alive)
										 restInColumn++;
									 if (row3.array[rowX].alive)
										 restInColumn++;
									 if (row4.array[rowX].alive)
										 restInColumn++;
									 if (row5.array[rowX].alive)
										 restInColumn++;
									 if (restInColumn == 0)//If no aliens alive in column
									 {
										 if (rowX >= rowPointer->mostLeftAlien)//If next column exist
											 rowX--;//Go there
										 else
										 {
											 //Player won
											 gui.ShowGameOver(font, showEndGameScreen);
											 gui.gameOverText.setString("YOU WIN");
											 break;
										 }
									 }
								 }
								 //Udpate all rows
								 row1.mostRightAlien = rowX;
								 row2.mostRightAlien = rowX;
								 row3.mostRightAlien = rowX;
								 row4.mostRightAlien = rowX;
								 row5.mostRightAlien = rowX;
							 }
						 }
					 }
				 }
			 }
			 //Enemy Movement
			 if (elapsedTime.asMicroseconds() > alienWaitTime)
			 {
				 float movementDirection = currentRow->movementDirection; //Get direction where aliens move
				 bool goingDown = currentRow->goingDown;
				 if (!goingDown)
					 currentRow->Move();
				 else
					 currentRow->MoveDown();
				 //If they are close to rihgt edge
				 if (currentRow->array[currentRow->mostRightAlien].alienSprite.getPosition().x >= screenWidth - 100 && !goingDown)
				 {
					 currentRow->goingDown = true;
				 }
				 //If they are close to left edge
				 if (currentRow->array[currentRow->mostLeftAlien].alienSprite.getPosition().x <= 0 + 100 && !goingDown)
				 {
					 currentRow->goingDown = true;
					 if (currentRow->array[currentRow->mostLeftAlien].alienSprite.getPosition().y > 720)
						 gui.ShowGameOver(font, showEndGameScreen);

				 }
				 currentRow->NextTexture();//Change texture
				 //Go to next row
				 if (currentRow == &row5)
					 currentRow = &row4;

				 else if (currentRow == &row4)
					 currentRow = &row3;

				 else if (currentRow == &row3)
					 currentRow = &row2;

				 else if (currentRow == &row2)
					 currentRow = &row1;

				 else if (currentRow == &row1)
					 currentRow = &row5;
				 timer.restart();
			 }
			 //Handling Simultaneous Movement and Shooting
			 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			 {
				 if (player.playerSprite.getPosition().x > 50)
					 player.Move(-1);
			 }
			 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			 {
				 if (player.playerSprite.getPosition().x < 1230)
					 player.Move(1);
			 }
			 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.canShoot)
			 {
				 player.Shoot(playerBullet);
				 soundManager.Play("playerShoot");
			 }
		 }
		 if (showEndGameScreen)//Dont play any sounds if game ended
			 soundManager.StopAllSounds();

		 window.clear(bgColor);

		 //Drawing
		if (!showEndGameScreen) 
		{
			window.draw(player.playerSprite);
			window.draw(playerBullet);
			window.draw(enemyBullet);
			window.draw(gui.scoreText);
			window.draw(gui.scoreValue);
			window.draw(gui.livesText);
			window.draw(gui.livesValue);
			window.draw(explosion1.explosionSprite);
			window.draw(explosion2.explosionSprite);
			window.draw(shield1.quad);
			window.draw(shield2.quad);
			window.draw(shield3.quad);
			window.draw(shield4.quad);
			window.draw(ufo.ufoSprite);
			for (int i = 0; i < 55; i++) {
				if (xPos > 10)
					xPos = 0;

				if (i < 11)
					window.draw(row1.array[xPos].alienSprite);

				if (i >= 11 && i < 22)
					window.draw(row2.array[xPos].alienSprite);

				if (i >= 22 && i < 33)
					window.draw(row3.array[xPos].alienSprite);

				if (i >= 33 && i < 44)
					window.draw(row4.array[xPos].alienSprite);

				if (i >= 44 && i < 55)
					window.draw(row5.array[xPos].alienSprite);
				xPos++;
			}
		}
		else 
		{
			window.draw(gui.gameOverText);
			window.draw(gui.scoreText);
			window.draw(gui.scoreValue);
			window.draw(gui.livesValue);
		}
		window.display();
	}
	return 0;
}

