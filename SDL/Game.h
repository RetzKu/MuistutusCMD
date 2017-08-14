#pragma once
#include <GL\glew.h>
#include <SDL\SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Input_Manager.h"
#include "KeyLogger.h"
#include <algorithm>
#include <vector>

enum class GameState{PLAY, EXIT};


class MainGame
{
public:

	MainGame();
	~MainGame();

	KeyLogger Keys;

	void run();

	const Uint8 *KeyState;
	HANDLE output_handle;
	CONSOLE_SCREEN_BUFFER_INFO screeninfo = {};
	std::vector<std::string> ActiveKeys = std::vector<std::string>(10);

	std::string CoutCorrectKey(std::string, short x, short y);
	void Backspace();


	bool FocusState;
	short columns;
	short rows;
	
private:
	void processInput();
	void gameLoop();
	void initSystems();

	SDL_Window* _window;
	int _screenWidth = 480;
	int _screenHeight = 360;
	GameState _gameState;

	char c;
	bool Typing;
	std::string stream;

};

