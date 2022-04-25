#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class Game
{
public:
	Game();
	void init();
	

private:
	void mouse();
	void keyboard();
	int frame{ 0 };
	int framerate{ 10 };
	int win_width{1280};
	int win_height{720};
	sf::RenderWindow window{ sf::VideoMode(win_width, win_height), "Jeff's Game of Life" };
	Map Map;
	bool update{false};
};

