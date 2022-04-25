#pragma once
#ifndef GAME_H
#define GAME_H
#endif 
#include <SFML/Graphics.hpp>
#include "Particle.h"
class Game
{
public:
	void init();
	void mouse();
	void keyboard();
	void update();
private:
	int win_width{1980};
	int win_height{1720};
	sf::RenderWindow window;
	std::vector <Particle> particles;
	std::map<int, sf::Color> colours;
};

