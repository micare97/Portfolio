#include "stdafx.h"
#include "MapHandling.hpp"

std::vector <Square> LoadMapFromFile(std::string MapName, int &W, int &H, MapTextures &mapt)
{
	std::cout << "I'm starting to load the map.\n";
	std::vector <Square> Map;
	std::fstream tmpMapFile;
	tmpMapFile.open("data\\maps\\tst.txt", std::ios::in);
	if (tmpMapFile.good())
		std::cout << "File opened correctly \n";
	else
		std::cout << "File opening FAILED";
	std::string tmp;
	int type, i=0;
	while (!tmpMapFile.eof())
	{

		tmpMapFile >> tmp;
		if (tmp == "x")
		{
			W = i;
			std::cout << "Map width is " << W << std::endl;
			continue;
		}
		if (tmp == "h")
		{
			H = Map.size() / W;
			std::cout << "Map hight is " << H << std::endl;
			break;
		}
		//std::cout << tmp << std::endl;
		type = std::stoi(tmp);	//std::cout << "I'm starting to load the map222.\n";
		Map.push_back(SetSquareProperties(i, type, mapt, W));
		i++;
	}
	tmpMapFile.close();
	std::cout << "Map loaded and interpreted.\n";
	return Map;
}
Square SetSquareProperties(int &i, int &type, MapTextures &mapt, int &W)
{
	//std::cout << "I'm starting to interpret Square.\n";
	Square tmp;
	tmp.SID = i+1;

	switch (type)
	{
	case 1:
		tmp.ST = MS_WALL;
		tmp.SS.setTexture(mapt.wall_t);
		break;
	case 2:
		tmp.ST = MS_ROAD;
		tmp.SS.setTexture(mapt.road_t);
		break;
	case 3:
		tmp.ST = MS_WATER;
		tmp.SS.setTexture(mapt.water_t);
		break;
	case 4:
		tmp.ST = MS_GRASS;
		tmp.SS.setTexture(mapt.grass_t);
		break;
	case 5:
		tmp.ST = MS_END;
		tmp.SS.setTexture(mapt.end_t);
		break;
	default:
		std::cout << "Square type for square ID:" << tmp.SID << " not found.\n";
		break;
	}
	//std::cout << "type fixed, ";
	tmp.SS.setOrigin(30, 30);
	tmp.SP.x = (tmp.SID-1) % W * 60 + 30;
	tmp.SP.y = (tmp.SID-1) / W * 60 + 30;
	//std::cout << "ID: " << tmp.SID << ", (" << tmp.SP.x << ", " << tmp.SP.y << ")\n";
	//tmp.SS.setPosition((tmp.SID) % W * 60, (tmp.SID) / W * 60);
	//std::cout << (tmp.SID) % W * 60 << ", " << (tmp.SID) / W * 60 << "position fixed\nInterpretation finished.\n";
	return tmp;
}
void LoadTextures(MapTextures &mapt)
{
	std::cout << "I'm starting to load mapt.\n";
	mapt.wall_t.loadFromFile("data/textures/wall.png");
	mapt.road_t.loadFromFile("data/textures/road.png");
	mapt.water_t.loadFromFile("data/textures/water.png");
	mapt.grass_t.loadFromFile("data/textures/grass.png");
	mapt.end_t.loadFromFile("data/textures/end.png");
	std::cout << "mapt loading finished.\n";
}
void PrintMap(sf::RenderWindow &window, std::vector <Square> &Map, sf::Vector2f &PZm, int &W, sf::Vector2f &PZe, int &ID)
{
	const int	w = 34, // w - width of printed map
				h = 20,	// h - height of printed map
				B = 60; // B - length of block
	int			IDd;	// IDd - ID of printed Square

	for (int j = 0; j < h; ++j)
	{
		for (int i = 0; i < w; ++i)
		{
			int movex = -(w / 2) + i,
				movey = -(W*h / 2 - W*j);
			IDd = ID + movey + movex;
			Map[IDd].SS.setPosition(PZe.x + (Map[IDd].SP.x - PZm.x), PZe.y + (Map[IDd].SP.y - PZm.y));
			window.draw(Map[IDd].SS);
		}
	}
}
