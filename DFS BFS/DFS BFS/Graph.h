#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <random>
#include <map>
#include <set>
#include <utility>
class Graph
{
public:
	Graph(unsigned short int maze_rows, unsigned short int maze_cols)
	{
		rows = maze_rows;
		cols = maze_cols;
		maze.resize(maze_rows*maze_cols, 0);
		q.push_back(start);
	}
	std::vector<int> maze;
	unsigned short int rows;
	unsigned short int cols;
	unsigned short int start = 0;
	std::deque<unsigned short int> q;

	//PATHFINDING
	bool setted_start = false;
	unsigned short int pathfinding_start{};
	bool setted_end = false;
	unsigned short int pathfinding_end{};
	unsigned short int visited_count = 0;
	std::vector<int> path;

	enum {
		CELL_NORTH_PATH = 0x01,
		CELL_EAST_PATH = 0x02,
		CELL_SOUTH_PATH = 0x04,
		CELL_WEST_PATH = 0x08,
		CELL_VISITED = 0x10,
		CELL_VISITED_TWICE = 0x20,
		START_CELL = 0x40,
		END_CELL = 0x80,
		CELL_CLOSED = 0x10,
		PATH = 0x20,
	};
	void print_maze();
	void dfs();
	void bfs();
	void reset();
	void set_start(const unsigned short int row, const unsigned short int col) { setted_start = true;  pathfinding_start = row * cols + col; } //std::cout << "You have setted the start point at:" << std::endl << "row: " << row << std::endl << "col: " << col << std::endl;}
	void set_end(const unsigned short int row, const unsigned short int col) { setted_end = true; pathfinding_end = row * cols + col; }//std::cout << "You have setted the end point at:" << std::endl << "row: " << row << std::endl << "col: " << col << std::endl;}
	void A_Star();
private:
	std::default_random_engine rd;
	std::uniform_int_distribution<unsigned short int> intdist{ 0, 1000 };
	std::mt19937 mt{ rd() };
	std::vector < unsigned short int > get_neighbours(const unsigned short int cell_index);
	

};

