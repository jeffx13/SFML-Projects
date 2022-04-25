#include "Terrain.h"
#include "Player.h"
#include "SFML/Graphics.hpp"

Terrain::Terrain(sf::RenderWindow& Win)
	:
	Window(Win)
{
		players.emplace_back(Player(Vector2D(100, 100)));
		
}

void Terrain::Update()
{
	for (auto& player : players) {
		player.Update(Window,OccupiedCoordinates);
		//player.GetCurrentCell(CellWidth,CellHeight)
	}
}

