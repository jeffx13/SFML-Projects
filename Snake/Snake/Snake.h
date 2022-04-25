#pragma once
#include "Location.h"
#include "SFML/Graphics.hpp"
#include "Board.h"
#include <vector>
#include <assert.h>
class Snake
{
private:
	class Segment
	{
	public: 
		Segment(Board& board) :board(board) {};
		void InitHead(const Location& loc); 
		void InitBody();
		void Follow(Segment& next);
		void MoveBy(Location& DeltaLoc, bool& Dead);
		void MoveBack();
		void Draw() const;
		Board& board;
	private:
		Location loc;
		sf::Color colour;
	};

public:
	Snake(const Location& loc, Board& board);
	void MoveBy(Location& DeltaLoc);
	void Grow();
	void Draw() const;
	bool Dead{ false };
private:
	
	static constexpr int MaxSegments{ 100 };
	std::vector<Segment> segments;
	std::vector<Segment>::iterator SegmentIter;
	Board& board;
	
};

