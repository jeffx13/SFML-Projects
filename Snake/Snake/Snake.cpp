#include "Snake.h"
#include "Board.h"
#include <iostream>
Snake::Snake(const Location& loc,Board& board) 
	: board(board)
{
	auto head = Segment(board);
	head.InitHead(loc);
	segments.push_back(head);

}

void Snake::MoveBy(Location& DeltaLoc)
{
	
	if (segments.size() > 1) {
		for (unsigned int i{ segments.size()-1 };i > 0;--i) {
			auto next = i - 1;
			if (!Dead) 
			{
				segments[i].Follow(segments[next]);
			}
		}
	}
	
	segments.begin()->MoveBy(DeltaLoc,Dead);
	
}

void Snake::Grow()
{
	if (segments.size() < MaxSegments) {
		auto body = Segment(board);
		body.InitBody();
		segments.push_back(body);
	}
}

void Snake::Draw() const
{
	for (auto& segment : segments) {
		segment.Draw();
	}
}



void Snake::Segment::InitHead(const Location& loc)
{
	this->loc = loc;
	this->colour = sf::Color::Green;
}

void Snake::Segment::InitBody()
{
	this->colour = sf::Color::Yellow;
}

void Snake::Segment::Follow(Segment& next)
{
	this->loc = next.loc;
}

void Snake::Segment::MoveBy(Location& DeltaLoc,bool& Dead)
{
	if (abs(DeltaLoc.x) + abs(DeltaLoc.y) == 1) {
		Location NewLoc = loc;
		NewLoc.Add(DeltaLoc);
		if (board.CheckBound(NewLoc) && !Dead) {
			loc = NewLoc;
		}
		else{
			DeltaLoc.x = 0;
			DeltaLoc.y = 0;
			Dead = true;
		}
	}
}

void Snake::Segment::MoveBack()
{
	loc.x = 0;
	loc.y = 0;

}

void Snake::Segment::Draw() const
{
	board.DrawBlock(this->loc, this->colour);
	
}
