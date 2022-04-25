#pragma once
#include <iostream>
#include <cmath>
#include <Vector>
#include "Player.h"
#include "SFML/Graphics.hpp"

class Terrain
{
public:
	Terrain(sf::RenderWindow& Win);
	void Update();

private:
	std::vector<Vector2D> OccupiedCoordinates;
	std::vector<Player> players;
	sf::RenderWindow& Window;
};

