#include "Input.h"

int ExtractTime(Box* B);

Input::~Input()
{
}

void Input::RunInput(SDL_Event* Event)
{
	//MouseLoc();
	switch (Event->type)
	{
		case SDL_MOUSEBUTTONDOWN:
			std::cout << "\nMouse Button Pressed ";
			MouseLoc();
			ProcessClick();
			break;
		case SDL_KEYDOWN:
			CoutCorrectKey(SDL_GetScancodeName(Event->key.keysym.scancode));
			break;
	}
}

void Input::ProcessClick()
{
	SelectedTexture = TextureInfo();
}

SDL_Rect* Input::MouseLoc()
{
	SDL_Rect Mloc;
	SDL_GetMouseState(&Mloc.x, &Mloc.y);
	SetMouseLoc(Mloc);
	std::cout << "x: " << Mloc.x << " Y: " << Mloc.y;
	return &Mloc;
}


void Input::CoutCorrectKey(std::string t)
{
	t = KeypadTranslate(t);
	if (t == "Space") { t = " "; }

	if (t == "Return")
	{
		if (CheckIfCompleted() == false){ std::cout << "\nError while making Task"; }
		else { std::cout << "\nTask Created"; }
	}
	else if (t == "Left Shift") {}
	else if (t == "Tab") {}
	else if (t == "Escape") { }
	else if (SelectedTexture != nullptr)
	{
		if (SelectedTexture->GetType() == TextureType::BoxType)
		{
			Box* B = dynamic_cast<Box*>(SelectedTexture);
			if (t == "Backspace") { B->Backspace(); }
			else if (B->TextRect.w < B->Rect.w)
			{
				B->PushBack(t[0]);
			}
		}
	}
}

bool Input::CheckIfCompleted()
{
	string TaskName;
	int TaskTime;
	for each(Texture* var in _RenderClass->TextureList)
	{
		if (var->Name == "Task Name")
		{
			Box* B = dynamic_cast<Box*>(var);
			if (B->Rect.w == 0){ return false; }
			else { TaskName = B->GetLine(); }
		}
		if (var->Name == "Task Time")
		{
			Box* B = dynamic_cast<Box*>(var);
			if (B->Rect.w == 0) { return false; }
			else { TaskTime = ExtractTime(B); if (TaskTime == -1) { return false; } }
		}
	}
	return true;
}

int ExtractTime(Box* B)
{
	string Time;
	for each (char Letter in B->GetLine())
	{
		if (isdigit(Letter))
		{
			Time.push_back(Letter);
		}
		else { return -1; }
	}
	if (Time == "")
	{
		return -1;
	}
	return std::stoi(Time);
}

std::string Input::KeypadTranslate(std::string key)
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
