#include "Input.h"


Input::~Input()
{
}

void Input::RunInput()
{
}

SDL_Rect* Input::MouseLoc(SDL_Window* WindowObject)
{
	SDL_Rect Mloc;
	SDL_GetMouseState(&Mloc.x, &Mloc.y);
	std::cout << "\nx: " << Mloc.x << " Y: " << Mloc.y;
	return &Mloc;
}

