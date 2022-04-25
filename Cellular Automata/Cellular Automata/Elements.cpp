#include "Elements.h"
#include <iostream>
Elements::Elements(Material type, std::vector<std::vector<std::shared_ptr<Elements>>>& Grid)
	:Grid(Grid), material(type),mt(std::random_device()())
{
	switch (type) 
	{
	case Material::sand:
		Attrib |= can_fall;
		Attrib |= can_move;
		density = 2.65f;
		material = Material::sand;

		break;
	case Material::water:
		material = Material::water;
		Attrib |= can_fall;
		Attrib |= can_move;
		Attrib |= can_flow;
		density = 1.0f;
		viscocity = 1;

		do {
			flow_dir = ((int)dist(mt) % 3)-1;
		} while (flow_dir == 0);
		break;
	case Material::oil:
		material = Material::oil;
		Attrib |= flammable;
		Attrib |= can_move;
		Attrib |= can_fall;
		Attrib |= can_flow;
		
		break;
	case Material::fire:
		material = Material::fire;
		break;
	case Material::steam:
		Attrib |= can_move;
		Attrib |= can_rise;
		break;
	case Material::smoke:
		material = Material::smoke;
		Attrib |= can_move;
		Attrib |= can_rise;
		break;
	case Material::concrete:
		material = Material::concrete;
		Attrib |= can_be_corroded;
		density = 100;
		health = 20;
		break;
	case Material::acid:
		Attrib |= can_move;
		Attrib |= can_fall;
		Attrib |= can_flow;
		break;
	case Material::wood:
		Attrib |= flammable;
		Attrib |= can_be_corroded;
		break;
	case Material::corrosive_gas:
		Attrib |= can_move;
		Attrib |= can_rise;
		break;
	case Material::lava:
		Attrib |= can_move;
		Attrib |= can_fall;
		Attrib |= can_flow;
		break;
	case Material::salt:
		Attrib |= can_move;
		Attrib |= can_fall;
		Attrib |= can_be_corroded;

		
	}
}

void Elements::update(unsigned int row, unsigned int col)
{
	if (Attrib & can_move) {
		if (Attrib & can_fall) {
			if (!(fall(row, col))&& (Attrib & can_flow)) {
				
				flow(row, col);
			}
		}
		if (Attrib & can_rise) {
			rise(row, col);
		}
	}
}

bool Elements::check_cell_material(unsigned int row, unsigned int col, Material material) const
{
	if (0 < row &&
		row < Grid.size() &&
		1 < col && col < Grid.at(row).size()) 
	{
		if (Grid[row][col]->material == material) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
	
}

bool Elements::check_cell_density(unsigned int row, unsigned int col, unsigned int density) const
{
	if (0 < row &&
		row < Grid.size() &&
		1 < col && col < Grid.at(row).size()) {

		if (Grid[row][col]->density < density) {
			return true;
		}
	}
	return false;
}

bool Elements::fall(unsigned int row, unsigned int col)
{
	std::vector<int> available_slide_directions;

	if (check_cell_material(row + 1, col, Material::empty) || 
		check_cell_density(row + 1, col, density ||
		(material == Material::water && check_cell_material(row + 1, col, Material::empty)))
		)
	{
		fall_count += velocity;
		if (fall_count >= weight)
		{
			Grid[row][col].swap(Grid[row + 1][col]);
			fall_count = 0;
			velocity += acceleration;
			
		}
		return true;
	}
	else {
		if (check_cell_material(row + 1, col + 1, Material::empty) ||
			(check_cell_density(row + 1, col + 1, density)))
		{
			available_slide_directions.push_back(col + 1);
		}
		if (check_cell_material(row + 1, col - 1, Material::empty) || (check_cell_density(row + 1, col - 1, density))) {

			available_slide_directions.push_back(col - 1);
		}
		
	}

	if (!available_slide_directions.empty()) {

		slide_count += velocity;
		if (slide_count >= viscocity)
		{
			auto randdir = (int)dist(mt) % available_slide_directions.size();
			Grid[row][col].swap(Grid[row+1][available_slide_directions[randdir]]);
			slide_count = 0;
		}
		return true;
	}
	else {
		return false;
	}
}

void Elements::flow(unsigned int row, unsigned int col)
{
	if (flow_dir > 0) {
		if (check_cell_material(row, col + 1, Material::empty))
		{
			flow_count += velocity;
			if (flow_count >= viscocity)
			{
				Grid[row][col].swap(Grid[row][col + 1]);
				flow_count = 0;
			}
		}
		else {
			
			do {
				flow_dir = ((int)dist(mt) % 3) - 1;
			} while (flow_dir == 0);
		}
	}
	else if(flow_dir<0) {
		 if (check_cell_material(row, col - 1, Material::empty))
		 {
			flow_count += velocity;
			if (flow_count >= viscocity)
			{
				Grid[row][col].swap(Grid[row][col - 1]);
				flow_count = 0;
			}
		 }
		 else
		 {
			 do {
				 flow_dir = ((int)dist(mt) % 3) - 1;
			 } while (flow_dir == 0);
		 }
	}
	
	

}

void Elements::set_aflame(unsigned int row, unsigned int col)
{

}

void Elements::rise(unsigned int row, unsigned int col)
{
}

void Elements::be_corroded(unsigned int row, unsigned int col)
{
}

void Elements::corrode(unsigned int row, unsigned int col)
{
	
}

