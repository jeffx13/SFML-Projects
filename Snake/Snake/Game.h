#pragma once
#include <SFML/Graphics.hpp>
#include "Location.h"
#include "Board.h"
#include "Snake.h"
#include <assert.h>

class Game
{
private:
	const int win_width;
	const int win_height;
	sf::RenderWindow window;
	Board board;
	static constexpr Location StartingLoc{ 4,4 };
	Location DeltaLoc{ 0,0 };
	Snake snek;
	bool GameOver{ false };
public:
	Game() :window(sf::VideoMode(win_width, win_height), "Snake"), board(window), snek(StartingLoc,board),win_width(board.GetWinWidth()), win_height(board.GetWinHeight())
	{};
	void init();
	void mouse();
	void keyboard();
	static constexpr int SnakeMovePeriod{ 5 };
	int SnakeMoveCounter{ 0 };

};

