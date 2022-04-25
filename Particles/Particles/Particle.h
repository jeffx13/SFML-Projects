#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <random>


class Particle
{
public:
	Particle(float partical_radius, sf::Color particle_colour) {
		colour = particle_colour;
		radius = partical_radius;
	}
	sf::Color colour;
	sf::CircleShape particle;
	sf::Vector2f direction;
	float radius;
	
	void update() {
		if (radius > 0) {
			radius -= 0.1;
			particle.setRadius(radius);
			//printf("%2f", radius);
		}
		particle.move(direction);
		//randomise_direction();
		rotate();
		colour_change();
		
	}
	void rotate() {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> dist(1.0, 10.0);

		int x = (int(dist(mt)) % 8) - 4;
		//std::cout << x << std::endl;
		float angle = (x * 3.14) / 180;
		direction.x = cos(angle) * direction.x - sin(angle) * direction.y;
		direction.y = sin(angle) * direction.x + cos(angle) * direction.y;
	}
	void randomise_direction() {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> dist(1.0, 10.0);

		srand((unsigned)20);
		direction.x = int(dist(mt)) % 10 - 5;
		direction.y = int(dist(mt)) % 10 - 5;
	}
	auto normalise(sf::Vector2f vector,float magnitude) {
		float normalisation_factor = sqrtf(pow(vector.x, 2) + pow(vector.y, 2)) * magnitude;
		vector.x /= normalisation_factor;
		vector.y /= normalisation_factor;
		return vector;
	}
	void colour_change() {
		/*if (colour.r <= 255) {
			colour.r++;
		}
		else;if (colour.g <= 255) {
			colour.g++;
		}
		if (colour.b <= 255) {
			colour.b++;
		}
		if (colour == sf::Color(255,255,255)) {
			colour = sf::Color::Black;
		}*/
		colour.a -= 10;
		particle.setFillColor(colour);

	}
};

