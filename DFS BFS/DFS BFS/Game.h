#pragma once
#include <SFML/Graphics.hpp>
#include "Graph.h"

class Game
{
	
private:
	int cell_size{ 20 };
	int cell_wall_thickness{ 1 };
	int maze_rows = 40;
	int maze_cols = 50;
	int win_width{ maze_cols * cell_size };
	int win_height{ maze_rows * cell_size };
	sf::RenderWindow window;
	
public:
	void init();
	void draw();
	
	void mouse();
	void keyboard();
	Graph maze{ maze_rows,maze_cols };
};

