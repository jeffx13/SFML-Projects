#pragma once
#include <SFML/Graphics.hpp>
#include "Firework.h"

class Game
{
public:
	void init();
	void mouse();
	void keyboard();
	void update();
private:
	int win_width{1280};
	int win_height{720};
	sf::RenderWindow window;
	sf::VideoMode current_videomode{ win_width, win_height };
	std::vector<Firework> fireworks;
};

