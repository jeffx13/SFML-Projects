#include "Map.h"
#include <assert.h>
#include "Elements.h"


Map::Map(sf::RenderWindow& Win)
	:
	Win(Win),
	cols(Win.getSize().x / ParticleSize),
	rows(Win.getSize().y / ParticleSize)
{
	
	Grid.resize(rows, std::vector<std::shared_ptr<Elements>>(cols, std::make_shared<Elements>(Elements(Material::empty, Grid))));
	std::cout << rows << std::endl;
	std::cout << cols << std::endl;
}

void Map::AddElement(unsigned int MousePosX, unsigned int MousePosY, enum Material type)
{
	int row = MousePosY / ParticleSize;
	int col = MousePosX / ParticleSize;
	std::shared_ptr<Elements> element;
	if (0 < row &&
		row < Grid.size() &&
		1 < col && 
		col < Grid.at(row).size())
	{
		if (Grid[row][col]->material == Material::empty) {
			switch (static_cast<Material>(type))
			{
			case Material::sand: {
				element = std::make_shared<Elements>(Elements{ Material::sand,Grid });
				break;
			}
			case Material::water:
			{
				element = std::make_shared<Elements>(Elements{ Material::water,Grid });
				break;
			}
			case Material::concrete:
			{
				element = std::make_shared<Elements>(Elements{ Material::concrete,Grid });
				break;
			}
			}
			Grid[row][col] = std::move(element);

		}
	}
	
}

void Map::update()
{
	for (int row{ 0 };row < Grid.size(); row++) {
		for (int col{ 0 };col < Grid[row].size(); col++) {
			if (Grid.at(row).at(col)->material != Material::empty) {
				Grid.at(row).at(col)->update(row, col);
			}
		}
	}
}

void Map::draw()
{
	for (int row{ 0 };row < Grid.size(); row++) {
		for (int col{ 0 };col < Grid[row].size(); col++) {
			if (Grid.at(row).at(col)->material != Material::empty) {
				std::unique_ptr<sf::RectangleShape> Rect = std::make_unique<sf::RectangleShape>(sf::RectangleShape(sf::Vector2f(ParticleSize, ParticleSize)));
				Rect->setFillColor(element_colours[Grid.at(row).at(col)->material]);
				Rect->setPosition(sf::Vector2f(col * ParticleSize, row * ParticleSize));
				Win.draw(*Rect);
			}
		}
	}
}

