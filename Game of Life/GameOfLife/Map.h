#pragma once
#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <bitset>
class Map
{

private:
	sf::RenderWindow& Win;
	unsigned int CountNeighbours(int row, int col);
	unsigned short int CellSize{ 20 };
	const unsigned int rows;
	const unsigned int cols;
	const unsigned int Framerate{ 3 };
	unsigned int CurrentFrame{ 0 };
	
	std::vector<std::vector<int>> CurrentGen;
	std::vector<std::vector<int>> NextGen;
	std::random_device rd;
	std::mt19937 mt{ rd() };
	std::uniform_real_distribution<float> dist{ 1,10000 };
public:
	Map(sf::RenderWindow& Win);
	void draw();
	void update();
	void print() const;
	void AddCell(unsigned int MousePosx, unsigned int MousePosy);
	void AddGlider(unsigned int MousePosx, unsigned int MousePosy);
};

