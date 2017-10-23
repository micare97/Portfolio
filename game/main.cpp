// little_explorer.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//
#include "stdafx.h"

#include "SFML\Graphics.hpp"

#include "MapHandling.hpp"
#include "MovementHandling.hpp"

#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <cmath>
#include "wtypes.h"

#define PI 3.14159265

class har
{
public:
	int				IDpos;			//Map position in block's ID

	std::string		HarName;

	sf::Vector2f	MapPos;			//Map Position
	sf::Vector2f	ScreenPos;		//Monitor Position
	sf::Vector2f	vel;			//Velocity

	float			maxspeed;		//Maximum har speed
	float			accel;			//Acceleration
	float			decel;			//Deceleration
	float			actualspeed;	//Actual har speed

	sf::Sprite		sprite;			//Har's sprite
	HarTextures		hartex;			//Har's textures

	sf::Clock		clock;			//Har's clock
	sf::Time		time;			//Har's time

	void input()
	{
		/* A */	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			vel.x -= accel;
		/* D */	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			vel.x += accel;
		else
			vel.x *= decel;

		/* W */	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			vel.y -= accel;
		/* S */ else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			vel.y += accel;
		else
			vel.y *= decel;

		if (vel.x < -maxspeed)       vel.x = -maxspeed;
		if (vel.x > maxspeed)       vel.x = maxspeed;
		if (vel.y < -maxspeed)       vel.y = -maxspeed;
		if (vel.y > maxspeed)       vel.y = maxspeed;

		actualspeed = sqrt((vel.x*vel.x) + (vel.y*vel.y));
		if (actualspeed > maxspeed)
			vel *= maxspeed / actualspeed;


		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) MapPos += vel;
		Movement();
	}
	void loadStats(std::string &filePath)
	{
		std::fstream statsFile;
		statsFile.open(filePath, std::ios::in);
		if (!statsFile.good())
			std::cout << filePath << " failed to open" << std::endl;
		std::string input;

		statsFile >> input;
		HarName = input;
		std::cout << input << std::endl;

		statsFile >> input;
		MapPos.x = std::stoi(input);
		std::cout << "MapPos.x start: " << MapPos.x << std::endl;

		statsFile >> input;
		MapPos.y = std::stoi(input);
		std::cout << "MapPos.y start: " << MapPos.y << std::endl;

		statsFile >> input;
		maxspeed = std::stoi(input);
		std::cout << input << std::endl;

		statsFile >> input;
		accel = std::stof(input);
		std::cout << input << std::endl;

		statsFile >> input;
		decel = std::stof(input);
		std::cout << input << std::endl;

		statsFile.close();
	}
	void calcPos(int &W)
	{
		int tmp = MapPos.y / 60;
		IDpos = tmp * W + (MapPos.x / 60);
		std::cout << std::endl << "POS : |" << IDpos << "|";
	}
	void Movement()
	{
		if (abs(vel.x) < 1.1f && abs(vel.y) < 1.1f)
		{
			sprite.setTexture(hartex.steady_t);
		}
		else if (abs(vel.x) > 1.1f || abs(vel.y) > 1.1f)
		{
			time = clock.getElapsedTime();
			if (time.asMilliseconds() < 200)
				sprite.setTexture(hartex.move1_t);
			else if (time.asMilliseconds() < 400)
				sprite.setTexture(hartex.move2_t);
			else
				clock.restart();

			if (vel.x / abs(vel.y) > 100)
				sprite.setRotation(90);
			else if (vel.x / abs(vel.y) < -100)
				sprite.setRotation(270);
			else if (vel.y < 0)
				sprite.setRotation(atan(-vel.x / vel.y) * (180 / PI));
			else if (vel.y > 0)
				sprite.setRotation((atan(-vel.x / vel.y) * (180 / PI)) + 180);
		}
	}
};
class herohar : public har
{
public:
	herohar()
	{
		ScreenPos.x = 960;
		ScreenPos.y = 540;
		sprite.setPosition(960, 540);
		hartex.steady_t.loadFromFile("data/characters/hero/movement/steady.png");
		hartex.move1_t.loadFromFile("data/characters/hero/movement/move1.png");
		hartex.move2_t.loadFromFile("data/characters/hero/movement/move2.png");
		//hartex.attack_t.loadFromFile("data/characters/hero/textures/movement/attack.png");
		//hartex.hit_t.loadFromFile("data/characters/hero/textures/movement/hit.png");
		//hartex.dead_t.loadFromFile("data/characters/hero/textures/movement/dead.png");
		sprite.setOrigin(30, 30);
	}
};
int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080, 32), "TheGame", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

	std::string path = "data/characters/hero/hero.txt";
	herohar hero;
	hero.loadStats(path);

	sf::Event eevent;
	int		W, H;				//W - Map Width (in blocks), H - Map Hight (in blocks)
	std::vector <Square>	MAP;

//declaring texture structures
	
	MapTextures			mapt;		//mapt - Map Textures

//loading

	LoadTextures(mapt);
	MAP = LoadMapFromFile("1_map", W, H, mapt);

	while (window.isOpen())
	{
		
		while (window.pollEvent(eevent))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		hero.calcPos(W);
		hero.input();

		if (hero.MapPos.x < 961)			hero.MapPos.x = 961;
		if (hero.MapPos.x > W * 60 - 961)	hero.MapPos.x = W * 60 - 961;
		if (hero.MapPos.y < 601)			hero.MapPos.y = 601;
		if (hero.MapPos.y > H * 60 - 601)	hero.MapPos.y = H * 60 - 601;
		canYouGetThere(MAP, hero.MapPos, hero.IDpos, W);
		whereAmI(MAP, hero.IDpos, hero.maxspeed);
		window.clear();
 		PrintMap(window, MAP, hero.MapPos, W, hero.ScreenPos, hero.IDpos);
		window.draw(hero.sprite);
		window.display();
	}
	system("pause");
    return 0;
}
