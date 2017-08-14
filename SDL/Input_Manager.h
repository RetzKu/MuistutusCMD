#pragma once
#include "Game.h"

class mouse_Pos
{
public:
	mouse_Pos(int x, int y);
	~mouse_Pos();

	void Get_M_Location(int x, int y);

	void Box(int start_x, int start_y, int Width, int Height);

private:

	int _y;
	int _x;	
};

