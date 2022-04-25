#include "Board.h"


void Board::DrawBlock(const Location& loc, const sf::Color colour)
{
	sf::RectangleShape block(sf::Vector2f(dimension, dimension));
	block.setPosition(sf::Vector2f(loc.x*dimension, loc.y * dimension));
	block.setFillColor(colour);
	window.draw(block);
	
}

bool Board::CheckBound(Location loc) const
{
	if (
		(0 < loc.x * dimension) && 
		(loc.x * dimension < window.getSize().x) &&
		(0 < loc.y * dimension) &&
		(loc.y * dimension < window.getSize().y))
	{
		return true;
	}
	else {
		return false;
	}
}


