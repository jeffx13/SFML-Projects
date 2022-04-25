#pragma once
#include <SFML/Graphics.hpp>
#include "Terrain.h"
#include <vector>

class Game
{
public:
	Game() :window(sf::VideoMode(WinWidth, WinHeight), "Curve Fever") {};
	void init();
	void mouse();
	void keyboard();
	void init_players();
	void update();

private:
	static constexpr int WinWidth{ 1280 };
	static constexpr int WinHeight{ 720 };
	sf::RenderWindow window;
	Terrain terrain{ window};

	int player_count;
	int cpu_count;
	int players_alive;
	bool start{ false };

	

};