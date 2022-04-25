#pragma once
#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>

class Game
{
public:
	void init();
	void bubblesort(std::vector<int>& list);
	void mergesort(std::vector<int>& list);
	void quicksort(std::vector<int>& list,int lower, int upper);
	void selectionsort(std::vector<int>& list);
	void insertionsort(std::vector<int>& list);

private:
	int win_width{ 1280 };
	int win_height{ 720 };
	int offset{ 0 };
	double sorting_array_size = 100;
	int max_height = win_height;
	double scale_factor;
	double element_width = (win_width-2*offset) /sorting_array_size;
	std::vector<int> sorting_array;
	
	void mouse();
	void keyboard();
	void draw();
	sf::RenderWindow window;
	std::default_random_engine rd;
	std::mt19937 mt{ rd() };
	std::uniform_int_distribution<int> intdist{1,10000};
};

