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
	void RunInput(SDL_Event* Event);
	void ProcessClick();
	SDL_Rect* MouseLoc();
	
	void SetMouseLoc(SDL_Rect* MouseLoc) { _MouseLoc = MouseLoc; }
	SDL_Rect* GetMouseLoc() { return _MouseLoc; }

private:
	SDL_Window* _WindowObject;
	SDL_Rect* _MouseLoc;
};

