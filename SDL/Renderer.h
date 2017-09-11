#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <SDL\SDL.h>
#include <SDL\SDL_ttf.h>
#include <iostream>
#include <chrono>

using std::vector;
using std::cout;
using std::string;

enum TextureType
{
	TextType,
	SolidType,
	BoxType,
};


enum Boxtype
{
	Filled,
	Empty,
	Insert,
	Button,
};

class Texture
{
public:
	int frames = 0;

	Texture(){}
	Texture(SDL_Renderer* _RenderObject, SDL_Window* _WindowObject, TextureType Type) { RenderObject = _RenderObject; WindowObject = _WindowObject; _Type = Type; }

	SDL_Surface* Surface() { return _Surface; }
	void Surface(SDL_Surface* Surface) { _Surface = Surface; }

	SDL_Texture* TextureData() { return _Texture; }
	void TextureData(SDL_Texture* Texture) { _Texture = Texture; }

	virtual void Update(){}

	TextureType GetType() { return _Type; }
	void GetType(TextureType Type) { _Type = Type; }
	
	


	SDL_Renderer* RenderObject;
	SDL_Window* WindowObject;
	
private:
	SDL_Surface* _Surface;
	SDL_Texture* _Texture;
	TextureType _Type;
};

class Renderer
{
public:
	Renderer();
	~Renderer();
	std::chrono::system_clock::time_point StartTime;

	SDL_Renderer* RendererObject;
	SDL_Window* WindowObject;
	
	vector<Texture*> TextureList;

	
	void AddToRenderer();
	void Render();

	int Frames = 0;
	void GetFps()
	{
		Frames += 1;
		std::chrono::duration<double> Seconds = std::chrono::system_clock::now() - StartTime;
		int c = (int)Seconds.count();
		if (c >= 1)
			StartTime = std::chrono::system_clock::now();
			cout << Frames;
			Frames = 0;
	}
	//string GetLine(int index);
	//void SetRectangle(int index, SDL_Rect Rectangle);
	//void ChangeLine(int index, char Key);
	//void BackspaceLine(int index);
	//void NewTexture(TextureType Type, string Name, SDL_Rect Rect);
	//void AddToRenderer(Texture NewTexture);
};


class Text : public Texture
{
public:
	Text() 
	{
		TTF_Init(); Line = ""; 
		_Font = TTF_OpenFont("arial.ttf", 18); 
		_TextColor = { 0, 0, 0, 255 };
	}
	Text(SDL_Renderer* RenderObject, SDL_Rect Rect)
	{
		_Rect = Rect;
		Texture::GetType(TextureType::TextType);
		Texture::RenderObject = RenderObject;
		TTF_Init(); Line = ""; 
		_Font = TTF_OpenFont("arial.ttf", 18); 
		_TextColor = { 0, 0, 0, 255 };
	}
	void Update() override
	{
		Texture::Surface(TTF_RenderText_Solid(_Font, Line.c_str(), _TextColor)); 
		Texture::TextureData(SDL_CreateTextureFromSurface(Texture::RenderObject,Texture::Surface()));
		SDL_QueryTexture(Texture::TextureData(), NULL, NULL, &_Rect.w, &_Rect.h);
		SDL_FreeSurface(Texture::Surface());
	}
	
	SDL_Rect* GetRect() { return &_Rect; }

	string PushBack(char Key)
	{
		Line.push_back(Key);
		return Line;
	}
	string Backspace()
	{
		Line = Line.substr(0, Line.size() - 1);
		return Line;
	}

private:
	SDL_Rect _Rect;
	TTF_Font* _Font;
	SDL_Color _TextColor;
	string Line;
};

class Box : public Texture
{
public:
	
	//Constructing start


	bool Action;
	SDL_Rect Rect;
	Boxtype Type;

	Box(){}
	Box(SDL_Renderer* Renderer, SDL_Rect NewRect, Boxtype NewType)
	{
		Texture::GetType(TextureType::BoxType);
		Texture::RenderObject = Renderer;
		Type = NewType;
		Rect = NewRect;
		CreateBox();
	}
	// Constructing end

	//Main Functionality
	void CreateBox();
	SDL_Renderer* PassRenderer() { return Texture::RenderObject; }

private:
};

