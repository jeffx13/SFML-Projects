#pragma once
#include "Location.h"
#include "SFML/Graphics.hpp"
#include <random>
class Board
{
public:
	Board(sf::RenderWindow& window) 
		:
		window(window),
		mt(std::random_device()())
	{
		
	};
	void DrawBlock(const Location& loc, const sf::Color colour);
	bool CheckBound(Location loc) const;
	int GetWinWidth() { return dimension * rows; }
	int GetWinHeight() { return dimension * cols; }
private:
	static constexpr int dimension{ 30 };
	static constexpr int rows{ 40 };
	static constexpr int cols{ 25 };
	sf::RenderWindow& window;
	std::mt19937 mt;
	
	
	
};

