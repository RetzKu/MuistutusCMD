#include "Game.h"
#include <vector>




mouse_Pos* Mouse = new mouse_Pos(0,0);
MSG msg = { 0 };
bool hotkeypressed = false;

void HotkeyHandler(SDL_Window *_window, HWND WindowsHandle);
void CheckTasks(SDL_Window* _window, std::string* Key);
void RemoveCorrectKey(std::string* Key);
std::string KeypadTranslate(std::string key);
void HotkeyThread();

struct TriggerTimer
{
public:
	TriggerTimer() {}
	TriggerTimer(std::string Name, int _RecallInterval) { TaskName = Name; TimeNow = std::chrono::system_clock::now(); RecallInterval = _RecallInterval; TimeToTrigger = false; }
	std::string TaskName;
	int RecallInterval;
	std::chrono::system_clock::time_point TimeNow;
	bool TimeToTrigger;

}TriggerTime;


class Task
{
public:
	Task(struct TriggerTimer a) { _TaskData = a; };

	std::string printname() { std::cout << _TaskData.TaskName; return _TaskData.TaskName; }
	void SetToNormal()
	{
		_TaskData.TimeNow = std::chrono::system_clock::now();
		_TaskData.TimeToTrigger = false;
	}
	bool GetTimeDifference()
	{
		std::chrono::duration<double> Seconds = std::chrono::system_clock::now() - _TaskData.TimeNow;
		auto i = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _TaskData.TimeNow);
		int c = (int)Seconds.count();
		if (c > _TaskData.RecallInterval)
		{
			_TaskData.TimeToTrigger = true;
			//run main task
		}
		return _TaskData.TimeToTrigger;
	}

private:
	TriggerTimer _TaskData;
};

std::vector<Task> Tasks;



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
	std::thread(HotkeyThread).detach();
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

			case SDL_KEYDOWN:
				CoutCorrectKey(SDL_GetScancodeName(evnt.key.keysym.scancode));
				//CheckIfCompleted(Key);
				const char *Line = Key.c_str();
				Surface = TTF_RenderText_Solid(Font, Line, TextColor);
				Texture1 = SDL_CreateTextureFromSurface(_renderer, Surface);
				SDL_QueryTexture(Texture1, NULL, NULL, &TextureWidth, &TextureHeight);
				rect1.x = 0;
				rect1.y = 0;
				rect1.w = TextureWidth;
				rect1.h = TextureHeight;

				SDL_FreeSurface(Surface);
				SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0xFF);
				SDL_RenderCopy(_renderer, Texture1, NULL, &rect1);

				break;

		}

	}
}

void MainGame::CreateTask(std::string TaskName)
{
	TriggerTimer tmpa = TriggerTimer(TaskName, 660);
	Key.clear();
	Task b(tmpa);
	Tasks.push_back(b);
}

void MainGame::CoutCorrectKey(std::string t)
{
	t = KeypadTranslate(t);
	if (t == "Space") { Key.append(" "); }
	else if (t == "Backspace") { Key = Key.substr(0, Key.size() - 1); }
	else if (t == "Return") { CreateTask(Key); }
	else if (t == "Left Shift") {}
	else if (t == "Tab") {}
	else if (t == "Escape") { _gameState = GameState::EXIT; std::cout << "\nProgram Ended\n"; }
	else { Key.append(t);}
}
std::string KeypadTranslate(std::string key)
{
	if (key == "Keypad 1") {key = "1";}
	else if(key == "Keypad 2") {key = "2";}
	else if(key == "Keypad 3") {key = "3";}
	else if(key == "Keypad 4") {key = "4";}
	else if(key == "Keypad 5") {key = "5";}
	else if(key == "Keypad 6") {key = "6";}
	else if(key == "Keypad 7") {key = "7";}
	else if(key == "Keypad 8") {key = "8";}
	else if(key == "Keypad 9") {key = "9";}
	else if(key == "Keypad 0") {key = "0";}
	else if(key == "Keypad +") {key = "+";}
	else if (key == "Keypad Enter") { key = "Return"; }
	return key;
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		HotkeyHandler(_window,WindowsHandle);
		MainRenderer();
		CheckTasks(_window,&Key);

		
	}
}

void CheckTasks(SDL_Window* _window, std::string* Key)
{
	if (sizeof(Tasks) != 0)
	{
		
		for (int i = 0; i < Tasks.size(); i++)
		{
			if (Tasks[i].GetTimeDifference() == true)
			{
				std::string o = Tasks[i].printname();
				const char *Taskname = o.c_str();
				Tasks[i].printname();
				std::cout << "\n";
				MessageBox(NULL, Taskname, "Bid ilmoitus",MB_OK|MB_ICONQUESTION|MB_SYSTEMMODAL|MB_SERVICE_NOTIFICATION);
				Tasks[i].SetToNormal();
				Tasks.erase(Tasks.begin() + i);
				RemoveCorrectKey(Key);
			}
		}
	}
	//std::cout << "checking tasks";
}
void RemoveCorrectKey(std::string* Key)
{

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
	Font = TTF_OpenFont("arial.ttf", 12);

	SDL_SysWMinfo SystemInfo;
	SDL_VERSION(&SystemInfo.version);
	SDL_GetWindowWMInfo(_window, &SystemInfo);

	SetHandle(SystemInfo.info.win.window);

	
	
}

void HotkeyHandler(SDL_Window *_window, HWND WindowsHandle)
{
	if (hotkeypressed == true)
	{
		std::cout << "Hotkey pressed";
		SDL_RaiseWindow(_window);
		SDL_RestoreWindow(_window);
		SDL_SetWindowInputFocus(_window);
		hotkeypressed = false;

		std::thread(HotkeyThread).detach();
	}
}

void HotkeyThread()
{
	if (RegisterHotKey(NULL, 1, MOD_CONTROL, 0x42))  //0x42 is 'b'
	{
		std::cout << "Hotkey Created\n";
	}

	while (hotkeypressed == false)
	{
		while (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			std::cout << "message";

			switch (msg.message)
			{
			case WM_HOTKEY:
				hotkeypressed = true;
				std::cout << "hotkey pressed";
				UnregisterHotKey(0, 1);
				break;
			default:
				break;
			}
		}
	}
}
