#pragma once
#include <cmath>
#include <iostream>
//template<typename T>
struct Vector2D
{
	Vector2D(float x, float y);
	Vector2D(float x, float y, float radius);
	Vector2D();

	friend std::ostream& operator<<(std::ostream& os, const Vector2D& vector);
	
	Vector2D operator+(const Vector2D& other) const; //ADD
	void operator+=(const Vector2D& other);

	Vector2D operator-() const;					 //NEGATIVE
	Vector2D operator-(const Vector2D& other) const; //SUBTRACT
	void operator-=(const Vector2D& other);

	Vector2D operator*(const float other) const;   //MULTIPLY BY CONSTANT
	void operator*=(const float other);

	Vector2D operator/(const float other) const;   //DIVIDE BY CONSTANT
	void operator/=(const float other);
						
	void rotate(float angle);

	float GetDistance(Vector2D other);
	float GetMagnitude();
	Vector2D GetNormalised();
	void Normalise();
	Vector2D FindVector(Vector2D other);
	Vector2D PerpendicularClockwise();
	Vector2D PerpendicularAntiClockwise();
	


	float x;
	float y;
	float radius;
};
