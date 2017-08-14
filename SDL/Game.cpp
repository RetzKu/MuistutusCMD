#include "Game.h"
#include <vector>



mouse_Pos* Mouse = new mouse_Pos(0,0);
MSG msg = { 0 };

void CreateCaller();
void HotkeyHandler(SDL_Window *_window);



MainGame::MainGame()
{
	_window = nullptr;
	_gameState = GameState::PLAY;
}


MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();
	CreateCaller();
	gameLoop();

	SDL_DestroyWindow(_window);
	delete Mouse;
	
}

void MainGame::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{

		switch (evnt.type)
			{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;

			case SDL_MOUSEMOTION:
				Mouse->Get_M_Location(evnt.motion.x, evnt.motion.y);
				Mouse->Box(250, 270, 100, 100);
				break;

			case SDL_WINDOWEVENT:
				switch (evnt.window.event)
				{
				case SDL_WINDOWEVENT_FOCUS_GAINED:
				{
					FocusState = true;
					//std::cout << "focus gained ";
					break;
				}
				case SDL_WINDOWEVENT_FOCUS_LOST:
				{
					FocusState = false;
					//std::cout << "focus lost ";
					break;
				}
				}
				break;

			case SDL_KEYDOWN:
				CoutCorrectKey(SDL_GetScancodeName(evnt.key.keysym.scancode), columns, rows);
				break;

		}
	}
}

std::string MainGame::CoutCorrectKey(std::string t,short x, short y)
{
	if (t == "Space") { std::cout << " "; return " "; }
	if (t == "Backspace") { Backspace(); return " "; }
	if (t == "Return"){std::cout << "\n"; return "\n";}
	if (t == "Left Shift") { return ""; }
	if (t == "Tab") { return ""; }
	if (t == "Escape") { _gameState = GameState::EXIT; std::cout << "\nProgram Ended\n"; return "Exiting"; }
	else { std::cout << t; return t; }
}
void MainGame::Backspace()
{
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screeninfo);
	columns = screeninfo.dwCursorPosition.X;
	rows = screeninfo.dwCursorPosition.Y;

	columns -= 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { columns, rows });
	std::cout << " ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { columns, rows });
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		//if (FocusState == false) { HotkeyHandler(_window); }
		HotkeyHandler(_window);
	}
}


void MainGame::initSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("Beli", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
}
void CreateCaller()
{
	if (RegisterHotKey(NULL,1,MOD_CONTROL,0x42))  //0x42 is 'b'
	{
		std::cout << "Hotkey Created\n";
	}
}
void HotkeyHandler(SDL_Window *_window)
{
	if (PeekMessage(&msg, NULL, 0, 0,NULL) != 0)
	{
		if (msg.message == WM_HOTKEY)
		{
			//std::cout << "Hotkey pressed";
			SDL_RaiseWindow(_window);
			SDL_RestoreWindow(_window);
			SDL_SetWindowInputFocus(_window);
		}
	}
}
