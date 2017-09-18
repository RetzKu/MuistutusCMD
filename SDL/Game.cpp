#include "Game.h"
#include <vector>




MSG msg = { 0 };
bool hotkeypressed = false;

void CheckTasks();
std::string KeypadTranslate(std::string key);
void HotkeyThread();
void HotkeyHandler(SDL_Window* _window, HWND WindowsHandle);

struct TriggerTimer
{
public:
	TriggerTimer() {}
	TriggerTimer(std::string Name, bool Singleuse, int _RecallInterval) { TaskName = Name; _Singleuse = Singleuse; TimeNow = std::chrono::system_clock::now(); RecallInterval = _RecallInterval; TimeToTrigger = false; }
	std::string TaskName;
	bool _Singleuse;
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
	bool Single()
	{
		return _TaskData._Singleuse;
	}
	
private:
	TriggerTimer _TaskData;
};

std::vector<Task> Tasks;



MainGame::MainGame()
{
	_gameState = GameState::PLAY;
}


MainGame::~MainGame()
{
	delete InputClass;
}

void MainGame::run()
{
	InputClass = new Input(RendererClass.WindowObject , &RendererClass);

	std::thread(HotkeyThread).detach();
	std::thread(CheckTasks).detach();

	Texture* B = RendererClass.AddToRenderer(TextureType::BoxType, SDL_Rect{ 10,100,150,18 });
	InsertBox = dynamic_cast<Box*>(B);

	B = RendererClass.AddToRenderer(TextureType::TextType, SDL_Rect{ 10,10,0,0 });
	MainInsert = dynamic_cast<Text*>(B);

	gameLoop();

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
			case SDL_KEYDOWN:
				CoutCorrectKey(SDL_GetScancodeName(evnt.key.keysym.scancode));
				break;
			case SDL_MOUSEBUTTONDOWN:
				InputClass->RunInput(&evnt);
				break;
		}
	}
}

void MainGame::CreateTask(std::string TaskName)
{
	std::string o;
	//Key = RendererClass.GetLine(0);
	bool Singleuse = false;
	if (Key.back() == 'S')
	{
		Key = Key.substr(0, Key.size() - 1);
		Singleuse = true;
	}
	for (int i = Key.length()-3; i < Key.length(); i++)
	{
		
		if (isdigit(Key[i]));
		{
			o.push_back(Key[i]);
			Key[i] = ' ';
		}
	}
	TriggerTimer tmpa = TriggerTimer(Key,Singleuse, std::stoi(o));
	Key.clear();
	Task b(tmpa);
	Tasks.push_back(b);
}

void MainGame::CoutCorrectKey(std::string t)
{
	t = KeypadTranslate(t);
	if (t == "Space") { MainInsert->PushBack(' '); }
	else if (t == "Backspace") { MainInsert->Backspace(); }
	else if (t == "Return") { CreateTask(Key); }
	else if (t == "Left Shift") {}
	else if (t == "Tab") {}
	else if (t == "Escape") { _gameState = GameState::EXIT; std::cout << "\nProgram Ended\n"; }
	else { /*insert key*/ MainInsert->PushBack(t[0]); Key.append(t);
	}
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
		std::chrono::system_clock::time_point Target = std::chrono::system_clock::now() + std::chrono::milliseconds(694/100);
		std::chrono::system_clock::time_point Now = std::chrono::system_clock::now();
		while (Now <= Target)
		{
			Now = std::chrono::system_clock::now();
			processInput();
			HotkeyHandler(RendererClass.WindowObject, WindowsHandle);
		}
		RendererClass.Render();
	}
}

void CheckTasks()
{
	using namespace std::chrono_literals;
	while (true)
	{
		if (Tasks.size() != 0)
		{
			for (int i = 0; i < Tasks.size(); i++)
			{
				if (Tasks[i].GetTimeDifference() == true)
				{
					std::string o = Tasks[i].printname();
					const char *Taskname = o.c_str();
					Tasks[i].printname();
					std::cout << "\n";
					MessageBox(NULL, Taskname, "elixiirit kehiin", MB_OK | MB_ICONQUESTION | MB_SYSTEMMODAL | MB_SERVICE_NOTIFICATION);
					Tasks[i].SetToNormal();
					if (Tasks[i].Single() == true)
					{
						Tasks.erase(Tasks.begin()+i);
					}
				}
			}
		}
		std::this_thread::sleep_for(1s);
	}
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
		if (WaitMessage())
		{
			while (GetMessage(&msg, NULL, 0, 0) != 0)
			{
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
}
