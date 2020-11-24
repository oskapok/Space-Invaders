#include "..//include//AlienRow.h"

AlienRow::AlienRow(Alien &alien){
	array.reserve(11);//Optimization
	for (size_t i = 0; i < 11; i++)
	{
		array.emplace_back(alien);
	}
	mostLeftAlien = 0;
	mostRightAlien = 10;
}
void AlienRow::NextTexture() {
	if (nextTexture)
	{
		for (int i = 0; i < 11; i++) 
		{
			array[i].NextTexture();
		}
		nextTexture = false;
	}
	else 
	{
		for (int i = 0; i < 11; i++)
		{
			array[i].PreviousTexture();
		}
		nextTexture = true;
	}
}
void AlienRow::Move() {
	for (int i = 0; i < 11; i++)
	{
		array[i].alienSprite.move(25 * movementDirection,0);
	}
}
void AlienRow::MoveDown(){
	for (int i = 0; i < 11; i++)
	{
		array[i].alienSprite.move(0, 25);
	}
	movementDirection *= -1;
	goingDown = false;
}

void AlienRow::SetScore(float score) {
	scoreValue = score;
}


