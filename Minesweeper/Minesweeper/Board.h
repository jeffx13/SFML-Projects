#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <random>
#include <SFML/Graphics.hpp>

class Board
{
private:
	std::random_device rd;
	std::mt19937 mt{ rd() };
	std::uniform_real_distribution<float> dist{ 1,1000 };
	std::map<std::string, sf::Texture> textures;
	unsigned short int rows{ 10 };
	unsigned short int cols{ 10 };
	unsigned short int block_size{ 10 };
	unsigned short int bombs;
	std::vector<std::vector<int>> Grid;
	void BFS(int row, int col);
	std::vector<std::pair<int, int>> GetNeighbours(int row, int col);
	void LoadTexture();
	
private:
	enum {
		REVEALED = 0x01,
		FLAGGED = 0x02,
		BOMB = 0x04,
		CLICKED_BOMB = 0x08,
	};

public:
	Board(int rows, int cols, int block_size);
	
	void create();
	void draw(sf::RenderWindow& window);
	void reveal(int MousePosx, int MousePosy);
	void flag(int MousePosx, int MousePosy);
	void RevealAll();
};

