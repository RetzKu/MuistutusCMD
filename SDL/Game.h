#pragma once
#include <SDL\SDL.h>
#include "Renderer.h"
#include <tchar.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>
#include <thread>
#include <memory>
#include "Input_Manager.h"
#include <Windows.h>
#include <SDL\SDL_syswm.h>
#include <algorithm>
#include <vector>
#include <SDL\SDL_ttf.h>
#include <functional>

enum class GameState{PLAY, EXIT};

class MainGame
{
public:

	MainGame();
	~MainGame();

	void run();
	//void MakeTimer(std::string);
	//void CheckIfCompleted(std::string);
	void CreateTask(std::string);
	void SetTaskName(std::string name) { SDL_SetWindowTitle(_window, name.c_str()); }
	std::string Key;
	std::vector<std::string> KeyList;

	const Uint8 *KeyState;
	HANDLE output_handle;
	CONSOLE_SCREEN_BUFFER_INFO screeninfo = {};

	SDL_Color TextColor = {0,0,0, 255};
	TTF_Font *Font;

	SDL_Rect rect1, rect2;
	SDL_Texture *Texture1, *Texture2;
	SDL_Surface *Surface;

	void CoutCorrectKey(std::string);

	
	/* New Experimental renderer class*/
	Renderer RendererClass;


	struct tm tmTime;
	struct tm EndLine;
	int diffseconds;
	bool FocusState;
	short columns;
	short rows;
	bool TimeCreated = false;

	void SetHandle(HWND Handle) { WindowsHandle = Handle; }
	
private:
	void processInput();
	void gameLoop();

	HWND hApp;
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	HWND WindowsHandle;

	int TextureWidth;
	int TextureHeight;

	int _screenWidth = 240;
	int _screenHeight = 160;
	GameState _gameState;

	char c;
	bool Typing;
	std::string stream;

};

