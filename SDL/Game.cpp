#include "Game.h"
#include <vector>




MSG msg = { 0 };
bool hotkeypressed = false;

void HotkeyThread();
void HotkeyHandler(SDL_Window* _window, HWND WindowsHandle);

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
}


MainGame::~MainGame()
{
	 delete InputClass;
	 delete TaskClass;
}

void MainGame::run()
{
	TaskClass = new TaskFrame(&RendererClass);
	InputClass = new Input(RendererClass.WindowObject , &RendererClass);

	//TaskClass->CreateTask("p�k�le", false, 5);
	//TaskClass->CreateTask("singlep�k�le", true, 10);

	std::thread(HotkeyThread).detach();


	Texture* B = RendererClass.AddToRenderer(Boxtype::Insert, SDL_Rect{ 5,300,240,18 }, "Task Name");
	InsertBox = dynamic_cast<Box*>(B);

	B = RendererClass.AddToRenderer(TextureType::TextType, SDL_Rect{ 300, 10,0,0 }, "Fps Meter");
	FpsMeter = dynamic_cast<Text*>(B);

	B = RendererClass.AddToRenderer(Boxtype::Insert, SDL_Rect{ 258,300,80,18 }, "Task Time");

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



void MainGame::gameLoop()
{
	using namespace std::chrono_literals;
	while (_gameState != GameState::EXIT)
	{
		HotkeyHandler(RendererClass.WindowObject, WindowsHandle);
		processInput();
		RendererClass.Render();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		FpsMeter->Replace("Fps: " + std::to_string(RendererClass.TotalLastFrames));
		if (InputClass->TaskFilled == true)
		{
			std::string TaskName;
			int TaskTime;
			for each(Texture* Var in RendererClass.TextureList)
			{
				if (Var->Name == "Task Name")
				{
					Box* tmp = dynamic_cast<Box*>(Var);
					TaskName = tmp->GetLine();
				}
				if (Var->Name == "Task Time")
				{
					Box* tmp = dynamic_cast<Box*>(Var);
					TaskTime = ExtractTime(tmp);
				}
			}
			TaskClass->CreateTask(TaskName, true, TaskTime);
			InputClass->TaskFilled = false;
		}
		//if (var->Name == "Task Name")
		//{
		//	Box* B = dynamic_cast<Box*>(var);
		//	if (B->Rect.w == 0) { return false; }
		//	else { TaskName = B->GetLine(); }
		//}
		//if (var->Name == "Task Time")
		//{
		//	Box* B = dynamic_cast<Box*>(var);
		//	if (B->Rect.w == 0) { return false; }
		//	else { TaskTime = ExtractTime(B); if (TaskTime == -1) { return false; } }
		//}
	}
}

int MainGame::ExtractTime(Box* B)
{
	string Time;
	for each (char Letter in B->GetLine())
	{
		if (isdigit(Letter))
		{
			Time.push_back(Letter);
		}
		else if (Letter == 'M')
		{
			Time = std::to_string(std::stoi(Time) * 60);
		}
		else { return -1; }
	}
	if (Time == "")
	{
		return -1;
	}
	return std::stoi(Time);
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
