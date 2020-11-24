#pragma once
#ifndef ALIEN_ROW
#define ALIEN_ROW
#include "..//include/Alien.h"

class AlienRow
{
public:
	std::vector<Alien> array;
	int mostLeftAlien;
	int mostRightAlien;
	float scoreValue;
	bool nextTexture = true;
	bool goingDown = false;
	float movementDirection = 1.f;
	AlienRow(Alien& alien);
	void SetScore(float score);
	void NextTexture();
	void Move();
	void MoveDown();
};
#endif
