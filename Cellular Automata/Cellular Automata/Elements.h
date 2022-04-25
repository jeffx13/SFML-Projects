#pragma once
#include <SFML/Graphics.hpp>
#include <random>

enum class Material {
	empty, sand, water, fire, steam, smoke, concrete, oil, acid, wood, corrosive_gas, lava, salt
};

class Elements
{
private:
	std::vector<std::vector<std::shared_ptr<Elements>>>& Grid;
	enum Attributes {
		none = 0x00,
		can_fall = 0x01,
		can_flow = 0x02,
		can_rise = 0x04,
		can_move = 0x08,
		can_be_corroded = 0x10,
		can_evaporate = 0x20,
		flammable = 0x40,
	};
	unsigned int  flammability{ 0 };
	unsigned int  viscocity{ 10 };
	float density{ 0 };
	unsigned int corrosiveness{ 0 };
	unsigned int Attrib{ none };
	unsigned int health{ 10 };
	float weight{10};
	int fall_count{ 0 };
	int flow_dir{ 0 };
	float velocity{5};
	float acceleration{ 0.1 };
	int slide_count{ 0 };
	int flow_count{ 0 };

private:
	
	std::mt19937 mt;
	std::uniform_real_distribution<float> dist{1,100};
	bool check_cell_material(unsigned int row, unsigned int col, Material material) const;
	bool check_cell_density(unsigned int row, unsigned int col, unsigned int density) const;
	bool fall(unsigned int row, unsigned int col);
	void flow(unsigned int row, unsigned int col);
	void rise(unsigned int row, unsigned int col);
	void evaporate(unsigned int row, unsigned int col);
	void set_aflame(unsigned int row, unsigned int col);
	void be_corroded(unsigned int row, unsigned int col);
	void corrode(unsigned int row, unsigned int col);

public:
	Elements(Material type, std::vector<std::vector<std::shared_ptr<Elements>>>& Grid);
	Elements();
	void update(unsigned int row, unsigned int col);
	Material material;
	
	
	


	
};

