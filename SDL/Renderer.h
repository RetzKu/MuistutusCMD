#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <SDL\SDL.h>
#include <SDL\SDL_ttf.h>
#include <iostream>

using std::vector;
using std::cout;
using std::string;

enum TextureType
{
	Text,
	Solid,

};

class Renderer
{
public:
	Renderer();
	~Renderer();

	class Texture;
	SDL_Renderer* RendererObject;
	SDL_Window* WindowObject;

	vector<Texture> TextureList;
	
	const vector<Texture> & GetTextures() const { return TextureList; }
	void SetRectangle(int index, SDL_Rect Rectangle);
	void ChangeLine(int index, char Key);
	void BackspaceLine(int index);
	void NewTexture(TextureType Type, string Name);
	void AddToRenderer(Texture NewTexture);
	void Render();
};

