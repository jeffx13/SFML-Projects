#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <chrono>
#define PI 3.1415926;

class Exploded_bit
{
public:
	Exploded_bit(
		char explosion_bit_radius,
		sf::Vector2f Exploded_bit_position,
		sf::Vector2f Exploded_bit_direction,
		sf::Color Exploded_bit_colour)
	{
		radius = explosion_bit_radius;
		direction = Exploded_bit_direction;
		colour = Exploded_bit_colour;
		circle.setFillColor(Exploded_bit_colour);
		circle.setRadius(radius);
		circle.setPosition(Exploded_bit_position.x - explosion_bit_radius, Exploded_bit_position.y - explosion_bit_radius);
	}
	sf::Vector2f direction;
	sf::Color colour;
	unsigned char angle_rotated{ 0 };
	char rotation_angle{ 2 };
	int alpha{ 255 };
	sf::CircleShape circle;
	char radius;
	void update();
	

};

class Smoke_particle
{
public:
	Smoke_particle(
		sf::Vector2f particle_position,
		sf::Vector2f particle_direction
	) {
		position = particle_position;
		direction = particle_direction;

	}
	unsigned char alpha{ 255 };
	sf::Vector2f position;
	sf::Vector2f direction;
	sf::Color colour{ 181, 181, 185, alpha };

	void update();

};

class Firework
{
public:
	Firework(float firework_radius, sf::Vector2i firework_position)
	{
		init_time = std::chrono::system_clock::now();
		firework.setPosition(sf::Vector2f(firework_position.x - firework_radius, firework_position.y - firework_radius));
		firework.setRadius(firework_radius);
		firework.setOutlineThickness(2);
		firework.setOutlineColor(sf::Color::Yellow);
		firework.setFillColor(sf::Color::Red);
		srand((unsigned)time(NULL));
	}

	std::chrono::system_clock::time_point init_time;
	std::chrono::system_clock::time_point current;
	std::chrono::milliseconds explosion_countdown{ 800 };

	sf::CircleShape firework;
	
	unsigned char explosion_radius{ 30 };
	unsigned char speed{ 10 };
	char explosion_bit_radius{ 5 };

	bool exploded{ false };
	bool finished{ false };
	std::vector<Exploded_bit> explosion;
	std::vector<Smoke_particle> smoke;
	void init();
	void explode();
	void update();
private:
	std::vector<sf::Color> colours{ 
		sf::Color(206, 32, 41),
		sf::Color(255, 252, 175),
		sf::Color(255, 225, 124),
		sf::Color(255, 102, 75),
		sf::Color(144, 56, 67),
		sf::Color(23, 56, 183),
		sf::Color(51, 64, 219),
		sf::Color(80, 77, 244),
		sf::Color(222, 91, 248),
		sf::Color(239, 232, 255),
		sf::Color(167, 107, 254),
		sf::Color(0, 255, 0) };
	
	
	
};
