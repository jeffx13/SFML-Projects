#include "Map.h"
#include <memory>
#include <stack>
#include <assert.h>

Map::Map(sf::RenderWindow& window)
	:
	Win(window),
	rows(Win.getSize().y / CellSize),
	cols(Win.getSize().x / CellSize)
{
	CurrentGen.resize(rows, std::vector<int>(cols,0));
	NextGen.resize(rows, std::vector<int>(cols, 0));

	std::cout << "rows: " << rows << "cols: " << cols << std::endl;
	int row, col;
	for (int i{ 0 };i < 200;) {
		row = int(dist(mt)) % (rows);
		col = int(dist(mt)) % (cols);
		if ((CurrentGen.at(row).at(col) & 0x01) == 0) {
			CurrentGen.at(row).at(col) |= 0x01;
			i++;
		}
	}
}

void Map::draw()
{
	for (std::size_t i = 0, e = CurrentGen.size(); i != e; ++i) {
		for (std::size_t j = 0, f = CurrentGen.at(i).size(); j != f; ++j) {
			std::unique_ptr<sf::RectangleShape> rect = std::make_unique<sf::RectangleShape>(sf::Vector2f(CellSize, CellSize));
			rect->setPosition(sf::Vector2f(j * CellSize, i * CellSize));
			rect->setOutlineThickness(-1);
			rect->setOutlineColor(sf::Color::Black);
			rect->setFillColor(sf::Color::White);
			if ((NextGen.at(i).at(j)&0x01) == 1) {
				rect->setFillColor(sf::Color::Black);
			}
			Win.draw(*rect);
		}
	}
	for (std::size_t i = 0, e = CurrentGen.size(); i != e; ++i) {
		for (std::size_t j = 0, f = CurrentGen.at(i).size(); j != f; ++j) {
			CurrentGen.at(i).at(j) = NextGen.at(i).at(j);
		}
	}
}

void Map::update()
{

	for (std::size_t i = 0, e = CurrentGen.size(); i != e; ++i) {
		for (std::size_t j = 0, f = CurrentGen.at(i).size(); j != f; ++j) {
			int neighbours = CountNeighbours(i, j);

			if (CurrentGen.at(i).at(j) == 1) {						//ALIVE
				if (neighbours < 2 || neighbours > 3)
				{
					NextGen.at(i).at(j) = 0;
				}
			}
			else if (CurrentGen.at(i).at(j) == 0) {	
				if (neighbours == 3) {
					NextGen.at(i).at(j) =  1;
				}
			}
		}
	}
}

void Map::print() const
{
	for (auto row : CurrentGen) {
		for (auto cell : row) {
			std::cout << " "<< std::bitset<4>(cell) << " ";
		}
		std::cout << std::endl;
	}
}

void Map::AddCell(unsigned int MousePosx, unsigned int MousePosy)
{
	NextGen.at(MousePosy / CellSize).at(MousePosx / CellSize)|=0x01;
	draw();
}
void Map::AddGlider(unsigned int MousePosx, unsigned int MousePosy)
{
	NextGen.resize(rows, std::vector<int>(cols, 0));
	unsigned int StartCellRow = MousePosy / CellSize;
	unsigned int StartCellCol = MousePosx / CellSize;

	NextGen.at(StartCellRow).at(StartCellCol) = 1;
	NextGen.at(StartCellRow + 1).at(StartCellCol) = 1;
	NextGen.at(StartCellRow + 1).at(StartCellCol + 1) = 1;
	NextGen.at(StartCellRow).at(StartCellCol + 1) = 1;

	NextGen.at(StartCellRow).at(StartCellCol + 10) = 1;
	NextGen.at(StartCellRow + 1).at(StartCellCol + 10) = 1;
	NextGen.at(StartCellRow + 2).at(StartCellCol + 10) = 1;
	NextGen.at(StartCellRow - 1).at(StartCellCol + 11) = 1;

	NextGen.at(StartCellRow - 1).at(StartCellCol + 11) = 1;
	NextGen.at(StartCellRow + 3).at(StartCellCol + 11) = 1;

	NextGen.at(StartCellRow - 2).at(StartCellCol + 12) = 1;
	NextGen.at(StartCellRow + 4).at(StartCellCol + 12) = 1;

	NextGen.at(StartCellRow - 2).at(StartCellCol + 13) = 1;
	NextGen.at(StartCellRow + 4).at(StartCellCol + 13) = 1;

	NextGen.at(StartCellRow + 1).at(StartCellCol + 14) = 1;

	NextGen.at(StartCellRow - 1).at(StartCellCol + 15) = 1;
	NextGen.at(StartCellRow + 3).at(StartCellCol + 15) = 1;

	NextGen.at(StartCellRow).at(StartCellCol + 16) = 1;
	NextGen.at(StartCellRow+1).at(StartCellCol + 16) = 1;
	NextGen.at(StartCellRow+2).at(StartCellCol + 16) = 1;
	NextGen.at(StartCellRow + 1).at(StartCellCol + 17) = 1;

	NextGen.at(StartCellRow).at(StartCellCol + 20) = 1;
	NextGen.at(StartCellRow-1).at(StartCellCol + 20) = 1;
	NextGen.at(StartCellRow-2).at(StartCellCol + 20) = 1;
	NextGen.at(StartCellRow).at(StartCellCol + 21) = 1;
	NextGen.at(StartCellRow - 1).at(StartCellCol + 21) = 1;
	NextGen.at(StartCellRow - 2).at(StartCellCol + 21) = 1;

	NextGen.at(StartCellRow - 3).at(StartCellCol + 22) = 1;
	NextGen.at(StartCellRow +1).at(StartCellCol + 22) = 1;

	NextGen.at(StartCellRow - 3).at(StartCellCol + 24) = 1;
	NextGen.at(StartCellRow + 1).at(StartCellCol + 24) = 1;
	NextGen.at(StartCellRow - 4).at(StartCellCol + 24) = 1;
	NextGen.at(StartCellRow + 2).at(StartCellCol + 24) = 1;	

	NextGen.at(StartCellRow -1).at(StartCellCol + 34) = 1;
	NextGen.at(StartCellRow - 2).at(StartCellCol + 34) = 1;

	NextGen.at(StartCellRow - 1).at(StartCellCol + 35) = 1;
	NextGen.at(StartCellRow - 2).at(StartCellCol + 35) = 1;

	
}

unsigned int Map::CountNeighbours(int row, int col)
{
	int neighbours{ 0 };

	if (row > 0 && col > 0) {
		if ((CurrentGen.at(row-1).at(col-1) & 0x01) == 1) { neighbours++; }
	}
	if (row > 0) {
		if ((CurrentGen.at(row-1).at(col) & 0x01) == 1) { neighbours++; }
	}
	if (row > 0 && col < cols-1) {
		if ((CurrentGen.at(row-1).at(col+1) & 0x01) == 1) { neighbours++; }
	}

	if (col > 0) {
		if ((CurrentGen.at(row).at(col-1) & 0x01) == 1) { neighbours++; }
	}
	if (col < cols-1) {
		if ((CurrentGen.at(row).at(col+1) & 0x01) == 1) { neighbours++; }
	}

	if (row < rows-1 && col > 0) {
		if ((CurrentGen.at(row + 1).at(col-1) & 0x01) == 1) { neighbours++; }
	}
	if (row < rows-1) {
		if ((CurrentGen.at(row + 1).at(col) & 0x01) == 1) { neighbours++; }
	}
	if (row < rows-1 && col < cols-1) {
		if ((CurrentGen.at(row + 1).at(col+1) & 0x01) == 1) { neighbours++; }
	}
	return neighbours;

	//std::cout << Grid.at(row).at(col) << "after" << std::endl;
}
