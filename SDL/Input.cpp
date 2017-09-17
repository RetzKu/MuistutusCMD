#include "Input.h"


Input::~Input()
{
}

void Input::RunInput(SDL_Event* Event)
{
	//MouseLoc();
	switch (Event->type)
	{
		case SDL_MOUSEBUTTONDOWN:
			std::cout << "Mouse Button Pressed";
			ProcessClick();
			break;
	}
}

void Input::ProcessClick()
{
	
}

SDL_Rect* Input::MouseLoc()
{
	SDL_Rect Mloc;
	SDL_GetMouseState(&Mloc.x, &Mloc.y);
	SetMouseLoc(&Mloc);
	std::cout << "\nx: " << Mloc.x << " Y: " << Mloc.y;
	return &Mloc;
}

