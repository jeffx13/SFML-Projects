#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Elements.h"
#include <memory>
#include <iostream>

class Map
{
public:
	Map(sf::RenderWindow& Win);
	void AddElement(unsigned int x, unsigned int y, enum class Material type);
	void update();
	void draw();
private:
	static constexpr unsigned short int ParticleSize = 5;
	std::vector<std::vector<std::shared_ptr<Elements>>> Grid;
	sf::RenderWindow& Win;
	std::map<enum class Material,sf::Color> element_colours = {
		{Material::empty, sf::Color::White},
		{Material::sand, sf::Color(242, 209, 107)},
		{Material::water, sf::Color(35, 137, 218)},
		{Material::fire, sf::Color::White},
		{Material::steam, sf::Color::White},
		{Material::smoke, sf::Color::White},
		{Material::concrete, sf::Color(139, 79, 57)},
		{Material::oil, sf::Color::White},
		{Material::acid, sf::Color::White},
		{Material::wood, sf::Color::White},
		{Material::corrosive_gas, sf::Color::White},
		{Material::lava, sf::Color::White},
		{Material::salt, sf::Color::White},
	};
	const unsigned int cols;
	const unsigned int rows;
};

