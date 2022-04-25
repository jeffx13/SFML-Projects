#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
class Game
{
public:

	Game();
	void init();
	void mouse();
	void keyboard();

private:
	static constexpr unsigned int win_width{1280};
	static constexpr unsigned int win_height{720};
	sf::RenderWindow window;
	Material material_type = Material::sand;
	Map Map;
};

