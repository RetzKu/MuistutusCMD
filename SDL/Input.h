#pragma once
#include <iostream>
#include <string>
#include <SDL\SDL.h>
#include <SDL\SDL_ttf.h>

class Input
{
public:
	//Input(MainGame Game) { _Game = Game; }
	Input(SDL_Window* WindowObject) { _WindowObject = WindowObject; }
	Input(){}
	~Input();

	/*Checks all functions inside this class. Put this in main gameloop*/
	void RunInput();
	SDL_Rect* MouseLoc(SDL_Window* WindowObject);

private:
	SDL_Window* _WindowObject;
	SDL_Rect* _MouseLoc;
};

