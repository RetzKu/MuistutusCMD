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
	std::string Key;
	std::vector<std::string> KeyList;

	const Uint8 *KeyState;
	HANDLE output_handle;
	CONSOLE_SCREEN_BUFFER_INFO screeninfo = {};

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
	
private:
	void processInput();
	void gameLoop();

	HWND hApp;

	GameState _gameState;

	char c;
	bool Typing;
	std::string stream;

};

