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

	SDL_DestroyTexture(Texture1);
	SDL_DestroyTexture(Texture2);
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
				CoutCorrectKey(SDL_GetScancodeName(evnt.key.keysym.scancode));
				
				const char *Line = Key.c_str();
				Surface = TTF_RenderText_Solid(Font, Line, TextColor);
				Texture1 = SDL_CreateTextureFromSurface(_renderer, Surface);
				rect1.x = 0;
				rect1.y = 0;
				rect1.w = 20 * Key.size();
				rect1.h = 20;

				SDL_QueryTexture(Texture1, NULL, NULL, 0, 0);
				SDL_FreeSurface(Surface);
				SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0xFF);
				SDL_RenderCopy(_renderer, Texture1, NULL, &rect1);

				break;

		}

	}
}

void MainGame::CoutCorrectKey(std::string t)
{
	if (t == "Space") { Key.append(" "); }
	else if (t == "Backspace") { Key = Key.substr(0, Key.size() - 1); }
	else if (t == "Return"){}
	else if (t == "Left Shift") {}
	else if (t == "Tab") {}
	else if (t == "Escape") { _gameState = GameState::EXIT; std::cout << "\nProgram Ended\n";}
	else { Key.append(t);}
}
void MainGame::Backspace()
{

}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		//if (FocusState == false) { HotkeyHandler(_window); }
		HotkeyHandler(_window);
		MainRenderer();
	}
}

void MainGame::MainRenderer()
{
	SDL_RenderClear(_renderer);
	SDL_RenderCopy(_renderer, Texture1, 0, &rect1);
	SDL_RenderPresent(_renderer);
}

void MainGame::initSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(_screenWidth, _screenHeight, 0, &_window, &_renderer);
	TTF_Init();
	Font = TTF_OpenFont("arial.ttf", 256);

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
