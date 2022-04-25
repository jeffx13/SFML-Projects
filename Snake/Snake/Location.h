#pragma once
struct Location
{
	int x;
	int y;
	void Add(Location DeltaLoc){
		x += DeltaLoc.x;
		y += DeltaLoc.y;
	}
	void Subtract(Location DeltaLoc) {
		x -= DeltaLoc.x;
		y -= DeltaLoc.y;
	}
	

};
