#pragma once
#ifndef MapHandling_hpp
#define MapHandling_hpp

#include <SFML\Graphics.hpp>

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
struct MapTextures
{
	sf::Texture		wall_t,
					road_t,
					water_t,
					grass_t,
					end_t;
};
enum MapSquareType : int
{
	MS_WALL,
	MS_ROAD,
	MS_WATER,
	MS_GRASS,
	MS_END
};
struct Square
{
	MapSquareType	ST;		//ST - Square Type
	sf::Vector2f	SP;		//SP - Square Position
	sf::Sprite		SS;		//SS - Square Sprite
	int				SID;	//SID - Square ID
};
std::vector <Square> LoadMapFromFile(std::string MapName, int &W, int &H, MapTextures &mapt);
Square SetSquareProperties(int &i, int &type, MapTextures &mapt, int &W);
void LoadTextures(MapTextures &mapt);
void PrintMap(sf::RenderWindow &window, std::vector <Square> &Map, sf::Vector2f &PZm, int &W, sf::Vector2f &PZe, int &ID);

#endif // !MapHandling_hpp
