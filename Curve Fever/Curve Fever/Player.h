#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
#include <random>
#include "Vector2D.h"
class Player
{
public:
	Player(Vector2D Position)
	{
		head.setPosition(sf::Vector2f(Position.x, Position.y));
		HeadCentre = Vector2D(head.getGlobalBounds().left + head.getRadius(), head.getGlobalBounds().top + head.getRadius());
		VA.setPrimitiveType(sf::TriangleStrip);
		Direction.x = (rand() % 100) - 50;
		Direction.y = (rand() % 100) - 50;
		Direction = Direction.GetNormalised() * Speed;
		Vector2D Clockwise = Direction.PerpendicularClockwise().GetNormalised() * head.getRadius();
		Vector2D AntiClockwise = Direction.PerpendicularAntiClockwise().GetNormalised() * head.getRadius();
		Vector2D ClockwisePoint = HeadCentre + Clockwise;
		Vector2D AntiClockwisePoint = HeadCentre + AntiClockwise;
		VA.append(sf::Vector2f(ClockwisePoint.x, ClockwisePoint.y));
		VA.append(sf::Vector2f(AntiClockwisePoint.x, AntiClockwisePoint.y));
	}
	~Player() = default;
public:
	void Update(sf::RenderWindow& Win, std::vector<Vector2D>& OccupiedCoordinates);

private:
	sf::CircleShape head{ 5 };
	Vector2D Direction{ 0,0 };
	float TurnSpeed{ 8 };
	float Speed{ 4 };

	float radius{ 5 };
	sf::Color colour;
	
	bool dead{ false };
	bool CPU{ false };

	void Input();
	void Draw(sf::RenderWindow& Win);
	void CalcFront();
	sf::VertexArray VA;
	void AddPointToLine();
	void Collisions(std::vector<Vector2D>& OccupiedCoordinates);
	std::vector<int> lines;
	Vector2D HeadCentre;
	std::vector<Vector2D> front;
	int VertexNumber{ 2 };
	
	/*std::default_random_engine rd;
	std::mt19937 mt{ rd() };
	std::uniform_real_distribution<float> dist{ 0.0, 5.0 };*/
};
