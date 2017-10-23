#include "stdafx.h"
#include "MovementHandling.hpp"
#define PI 3.14159265
void canYouGetThere(std::vector <Square> &Map, sf::Vector2f &PZm, int &ID, int &W)
{
	int testID;

	testID = ID - W;	//2
	if (Map[testID].ST == MS_END || Map[testID].ST == MS_WALL)
	{
		if (PZm.y < Map[testID].SP.y + 55)
			PZm.y = Map[testID].SP.y + 55;
	}
	
	testID = ID - 1;		//4
	if (Map[testID].ST == MS_END || Map[testID].ST == MS_WALL)
	{
		if (PZm.x < Map[testID].SP.x + 55)
			PZm.x = Map[testID].SP.x + 55;
	}

	testID = ID + 1;		//5
	if (Map[testID].ST == MS_END || Map[testID].ST == MS_WALL)
	{
		if (PZm.x > Map[testID].SP.x - 55)
			PZm.x = Map[testID].SP.x - 55;
	}

	testID = ID + W;	//7
	if (Map[testID].ST == MS_END || Map[testID].ST == MS_WALL)
	{
		if (PZm.y > Map[testID].SP.y - 55)
			PZm.y = Map[testID].SP.y - 55;
	}

/*
	/*testID = ID - W - 1;	//1
	if (Map[testID].ST == MS_END || Map[testID].ST == MS_WALL || Map[testID].ST == MS_WATER)
	{
		Map[testID].SS.setTexture(mapt.end_t);
		if (PZm.x < Map[testID].SP.x + 50 && PZm.y < Map[testID].SP.y + 50)
		{
			PZm.x = Map[testID].SP.x + 50;
			PZm.y = Map[testID].SP.y + 50;
		}
	}

	testID = ID - W + 1;		//3
	if (Map[testID].ST == MS_END || Map[testID].ST == MS_WALL || Map[testID].ST == MS_WATER)
	{
		Map[testID].SS.setTexture(mapt.end_t);
		if (PZm.x > Map[testID].SP.x - 50 && PZm.y < Map[testID].SP.y + 50)
		{
			PZm.x = Map[testID].SP.x - 50;
			PZm.y = Map[testID].SP.y + 50;
		}
	}

	testID = ID + W - 1;	//6
	if (Map[testID].ST == MS_END || Map[testID].ST == MS_WALL || Map[testID].ST == MS_WATER)
	{
		Map[testID].SS.setTexture(mapt.end_t);
		if (PZm.x < Map[testID].SP.x + 50 && PZm.y > Map[testID].SP.y - 50)
		{
			PZm.x = Map[testID].SP.x + 50;
			PZm.y = Map[testID].SP.y - 50;
		}
	}
			
	testID = ID + W + 1;		//8
	if (Map[testID].ST == MS_END || Map[testID].ST == MS_WALL || Map[testID].ST == MS_WATER)
	{
		Map[testID].SS.setTexture(mapt.end_t);
		if (PZm.x > Map[testID].SP.x - 50 && PZm.y > Map[testID].SP.y - 50)
		{
			PZm.x = Map[testID].SP.x - 50;
			PZm.y = Map[testID].SP.y - 50;
		}
	}
*/

	//std::cout << ID << "," << testID << "," << W << std::endl;
}
void whereAmI(std::vector <Square> &Map, int &ID, float &maxspeed)
{
	if (Map[ID].ST == MS_WATER)
		maxspeed = 3.0;
	if (Map[ID].ST == MS_ROAD)
		maxspeed = 6.0;
	if (Map[ID].ST == MS_GRASS)
		maxspeed = 5.1;
}
void loadHeroMovement(HarTextures &herotex)
{
	herotex.steady_t.loadFromFile("data/textures/movement/steady.png");
	herotex.move1_t.loadFromFile("data/textures/movement/move1.png");
	herotex.move2_t.loadFromFile("data/textures/movement/move2.png");
	//herotex.attack_t.loadFromFile("data/textures/movement/attack.png");
	//herotex.hit_t.loadFromFile("data/textures/movement/hit.png");
	//herotex.dead_t.loadFromFile("data/textures/movement/dead.png");
}
void heroMovement(sf::Vector2f &vel, sf::Sprite &hero, HarTextures &herotex, sf::Clock &clock1, sf::Time &time1)
{
	if (abs(vel.x) < 1.1f && abs(vel.y) < 1.1f)
	{
		hero.setTexture(herotex.steady_t);
	} 
	else if (abs(vel.x) > 1.1f || abs(vel.y) > 1.1f)
	{
		time1 = clock1.getElapsedTime();
		if (time1.asMilliseconds() < 200)
			hero.setTexture(herotex.move1_t);
		else if (time1.asMilliseconds() < 400)
			hero.setTexture(herotex.move2_t);
		else
			clock1.restart();

		if (vel.x / abs(vel.y) > 100)
			hero.setRotation(90);
		else if (vel.x / abs(vel.y) < -100)
			hero.setRotation(270);
		else if (vel.y < 0)
			hero.setRotation(atan(-vel.x / vel.y) * (180 / PI));
		else if (vel.y > 0)
			hero.setRotation((atan(-vel.x / vel.y) * (180 / PI)) + 180);
	}
}