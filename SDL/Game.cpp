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

	Texture* B = RendererClass.AddToRenderer(Boxtype::Insert, SDL_Rect{ 5,300,300,18 }, "Task Name");
	InsertBox = dynamic_cast<Box*>(B);

	B = RendererClass.AddToRenderer(Boxtype::Insert, SDL_Rect{ 312,300,80,18 }, "Task Time");

	B = RendererClass.AddToRenderer(TextureType::TextType, SDL_Rect{ 10,10,0,0 }, "Running Task");
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
		}
		InputClass->RunInput(&evnt);
	}
}

//void MainGame::CreateTask(std::string TaskName)
//{
//	TriggerTimer tmpa = TriggerTimer(Key,Singleuse, std::stoi(o));
//	Key.clear();
//	Task b(tmpa);
//	Tasks.push_back(b);
//}


void MainGame::gameLoop()
{
	using namespace std::chrono_literals;
	while (_gameState != GameState::EXIT)
	{
		HotkeyHandler(RendererClass.WindowObject, WindowsHandle);
		processInput();
		RendererClass.Render();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
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
		std::this_thread::sleep_for(0.5s);
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
