#pragma once
#include <GL\glew.h>
#include <SDL\SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>
#include <thread>
#include <memory>
#include "Input_Manager.h"
#include "KeyLogger.h"
#include <algorithm>
#include <vector>
#include <SDL\SDL_ttf.h>

enum class GameState{PLAY, EXIT};


class MainGame
{
public:

	MainGame();
	~MainGame();

	KeyLogger Keys;

	void run();
	void MakeTimer(std::string);
	void CheckIfCompleted(std::string);

	std::string Key;
	const Uint8 *KeyState;
	HANDLE output_handle;
	CONSOLE_SCREEN_BUFFER_INFO screeninfo = {};
	std::vector<std::string> ActiveKeys = std::vector<std::string>(10);

	SDL_Color TextColor = {255,255,255, 255};
	TTF_Font *Font;

	SDL_Rect rect1, rect2;
	SDL_Texture *Texture1, *Texture2;
	SDL_Surface *Surface;

	void CoutCorrectKey(std::string);
	void Backspace();

	void MainRenderer();
	
	struct tm tmTime;
	struct tm EndLine;
	int diffseconds;
	bool FocusState;
	short columns;
	short rows;
	bool TimeCreated = false;
	
private:
	void processInput();
	void gameLoop();
	void initSystems();

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	int TextureWidth;
	int TextureHeight;

	int _screenWidth = 480;
	int _screenHeight = 360;
	GameState _gameState;

	char c;
	bool Typing;
	std::string stream;

};

