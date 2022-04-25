#include "Board.h"
#include <memory>
#include <filesystem>

Board::Board(int rows, int cols, int block_size)
	:
	rows(rows),
	cols(cols),
	block_size(block_size)
{
	Grid.resize(rows, std::vector<int>(cols, 0));
	bombs = floor(0.25 * rows * cols);
	LoadTexture();
}

void Board::LoadTexture()
{
	std::string path = "images";
	for (auto& entry : std::filesystem::directory_iterator(path)) {
		//std::cout << entry.path().string()<< std::endl;
		auto firstindext = entry.path().string().find_first_of("\\");
		std::string img_name = entry.path().string().substr(firstindext + 1);
		auto lastindex = img_name.find_last_of(".");
		img_name = img_name.substr(0, lastindex);
		sf::Texture texture;
		texture.loadFromFile(entry.path().string());
		textures[img_name] = texture;
	}
	std::cout << "Textures Loaded." << std::endl;
}

void Board::RevealAll()
{
	for (auto& row : Grid) {
		for (auto& col : row) {
			col |= REVEALED;
		}
	}
}

void Board::create()
{
	for (auto& row : Grid) {
		for (auto& cell : row) {
			cell = 0;
		}
	}
	
	for (int i{}; i < bombs;) {
		int rand_row = int(dist(mt)) % rows;
		int rand_col = int(dist(mt)) % cols;
		if ((Grid[rand_row][rand_col] & BOMB) == 0) {
			Grid.at(rand_row).at(rand_col) |= BOMB;
			auto neighbours = GetNeighbours(rand_row, rand_col);

			for (auto& neighbour : neighbours) {
				if ((Grid.at(neighbour.first).at(neighbour.second) & BOMB) == 0)
				{
				auto& cell = Grid.at(neighbour.first).at(neighbour.second);
				auto revealed = cell & REVEALED;
				auto bomb = cell & BOMB;
				auto flag = cell & FLAGGED;
				auto click_bomb = cell & CLICKED_BOMB;
				cell >>= 4;
				cell += 1;
				cell <<= 4;
				cell |= revealed | bomb | flag | click_bomb;
				}
			}
			i++;
		}
	}
}

void Board::BFS(int row,int col)
{
	std::deque<std::pair<int,int>> q;
	std::set<std::pair<int, int>> closed;
	q.push_back(std::pair<int,int>(row, col));
	
	while (!(q.empty())) {
		auto current = q.front();
		auto neighbours = GetNeighbours(current.first, current.second);
		for (auto neighbour : neighbours) {
			Grid.at(neighbour.first).at(neighbour.second) |= REVEALED;
			if ((Grid.at(neighbour.first).at(neighbour.second) >> 4) == 0) {
				if ((Grid.at(neighbour.first).at(neighbour.second) & BOMB) == 0) {
					if (!closed.contains(neighbour)) {
						q.push_back(neighbour);
						closed.insert(neighbour);
					}
				}
			} 
		}
		q.pop_front();
	}
}

std::vector<std::pair<int, int>> Board::GetNeighbours(int row, int col)
{
	std::vector<std::pair<int,int>> neighbours;

	if (row > 0 && col > 0) {
		neighbours.push_back(std::pair<int, int>(row - 1, col - 1));
	}
	if (row > 0) {
		neighbours.push_back(std::pair<int, int>(row - 1, col));
	}
	if (row > 0 && col < cols - 1) {
		neighbours.push_back(std::pair<int, int>(row - 1, col + 1));
	}

	if (col > 0) {
		neighbours.push_back(std::pair<int, int>(row, col - 1));
	}
	if (col < cols - 1) {
		neighbours.push_back(std::pair<int, int>(row, col + 1));
	}

	if (row < rows - 1 && col > 0) {
		neighbours.push_back(std::pair<int, int>(row + 1, col - 1));
	}
	if (row < rows - 1) {
		neighbours.push_back(std::pair<int, int>(row + 1, col));
	}
	if (row < rows - 1 && col < cols - 1) {
		neighbours.push_back(std::pair<int, int>(row + 1, col + 1));
	}

	return neighbours;
};

void Board::draw(sf::RenderWindow& window)
{
	for (int i{};i < Grid.size();++i) {
		for (int j{};j < Grid.at(i).size();++j) {
			sf::Sprite block;
			block.setPosition(sf::Vector2f(j*block_size,i*block_size));

			if ((Grid[i][j] & REVEALED) == 0) {
				if ((Grid[i][j] & FLAGGED) == FLAGGED) { block.setTexture(textures["flag"]); }
				else { block.setTexture(textures["empty"]); };
			}
			else {
				if ((Grid[i][j] & BOMB) == BOMB) 
				{ 
					if ((Grid[i][j] & FLAGGED) == FLAGGED) {
						block.setTexture(textures["wrong_flag"]);
					}
					else if ((Grid[i][j] & CLICKED_BOMB) == CLICKED_BOMB) {
						block.setTexture(textures["clicked_bomb"]);
					}
					else {
						block.setTexture(textures["unclicked_bomb"]);
					}
				}
				else {
					auto BombCount =(Grid[i][j] >> 4);
					std::string str = std::to_string(BombCount);
					block.setTexture(textures[str]);
				}
			}

			block.setScale(
				block_size / block.getLocalBounds().width,
				block_size / block.getLocalBounds().height);
			window.draw(block);
		}
		
	}
}

void Board::reveal(int MousePosx, int MousePosy)
{
	Grid[MousePosy / block_size][MousePosx / block_size] |= REVEALED;
	if ((Grid[MousePosy / block_size][MousePosx / block_size] >> 4) == 0) {
		if ((Grid.at(MousePosy / block_size).at(MousePosx / block_size) & BOMB) == 0) {
			BFS(MousePosy / block_size, MousePosx / block_size);
		}
	}
	if ((Grid.at(MousePosy / block_size).at(MousePosx / block_size) & BOMB) == BOMB) {
		Grid[MousePosy / block_size][MousePosx / block_size] |= CLICKED_BOMB;
	}
	
}

void Board::flag(int MousePosx, int MousePosy)
{
	Grid[MousePosy / block_size][MousePosx / block_size] |= FLAGGED;
}

