#pragma once
#include <iostream>

#include <cstdlib>
#include<map>
#include <SFML/Graphics.hpp>
#include "Board.h"

class Game
{
public:
	void init();
	void mouse();
	void keyboard();
	
    const unsigned short int rows = 50;
	const unsigned short int cols = 50;
	const unsigned short int block_size = 20;
private:
	int win_width{ block_size * cols };
	int win_height{ block_size * rows };
	sf::RenderWindow window;
	Board board{ rows, cols, block_size };
	bool Mass_Reveal{ false };
	int MassRevealRectSize{ 200 };
	void draw();
	void MassReveal(int MousePosX, int MousePosY);
	bool CheckMouseBounds(int MousePosX, int MousePosY);
};

