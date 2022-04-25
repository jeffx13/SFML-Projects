#pragma once
#include <SFML/Graphics.hpp>

class Game
{
public:
	void init();
	void mouse();
	void keyboard();

private:
	int win_width{1280};
	int win_height{720};
	sf::RenderWindow window;
};

