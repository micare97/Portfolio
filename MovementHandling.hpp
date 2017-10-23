#pragma once
#ifndef MovementHandling_hpp
#define MovementHandling_hpp
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "MapHandling.hpp"
struct HarTextures
{
	sf::Texture steady_t,
				move1_t,
				move2_t,
				attack_t,
				hit_t,
				dead_t;
};
void canYouGetThere(std::vector <Square> &Map, sf::Vector2f &PZm, int &ID, int &W);
void whereAmI(std::vector <Square> &Map, int &ID, float &maxspeed);
void loadHeroMovement(HarTextures &herotex);
void heroMovement(sf::Vector2f &vel, sf::Sprite &hero, HarTextures &herotex, sf::Clock &clock1, sf::Time &time1);
#endif // !MovementHandling_hpp
