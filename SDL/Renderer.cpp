#include "Renderer.h"



class Renderer::Texture
{
public:
	string TextureName;
	Texture(TextureType Type,string Name)
	{
		TextureName = Name;
		if (Type == TextureType::Text)
		{
			_Type = Type;
			_Line = "";
			TTF_Init();
			_Font = TTF_OpenFont("arial.ttf", 18);
		}
	}

	void updatetexture(SDL_Renderer* RendererObject)
	{
		switch (_Type)
		{
		case Text:
			_Surface = TTF_RenderText_Solid(_Font, _Line.c_str(), _TextColor);
			break;
		case Solid:
			break;
		default:
			break;
		}
		_Texture = SDL_CreateTextureFromSurface(RendererObject, _Surface);
		SDL_QueryTexture(_Texture, NULL, NULL, &TextureWidth, &TextureHeight);
		_Rect.h = TextureHeight;
		_Rect.w = TextureWidth;
		SDL_FreeSurface(_Surface);
	}

	void SetLine(char Key) { _Line.push_back(Key); }
	void BackspaceLine() { _Line = _Line.substr(0, _Line.size() - 1); }
	void SetRect(SDL_Rect Rect) { _Rect = Rect; }
	SDL_Texture* GetTexture() { return _Texture; }
	SDL_Rect GetRectange() { return _Rect; }

private:
	SDL_Surface* _Surface;
	SDL_Texture* _Texture;
	SDL_Rect _Rect;
	SDL_Color _TextColor = { 0,0,0, 255 };
	TTF_Font* _Font;
	string _Line;
	TextureType _Type;
	int TextureWidth;
	int TextureHeight;
};

Renderer::Renderer()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(400, 400, 0, &WindowObject, &RendererObject);
	SDL_SetRenderDrawColor(RendererObject, 255, 255, 255, 0xFF);
}


Renderer::~Renderer()
{
}

void Renderer::NewTexture(TextureType Type, string Name)
{
	Texture NewTexture = Texture(Type, Name);
	AddToRenderer(NewTexture);
}
 
void Renderer::AddToRenderer(Texture NewTexture)
{
	TextureList.push_back(NewTexture);
}

void Renderer::SetRectangle(int index, SDL_Rect Rectangle)
{
	TextureList[index].SetRect(Rectangle);
}

void Renderer::ChangeLine(int index,char Key)
{
	TextureList[index].SetLine(Key);
}

void Renderer::BackspaceLine(int index)
{
	TextureList[index].BackspaceLine();
}

void Renderer::Render()
{
	SDL_RenderClear(RendererObject);
	if (sizeof(TextureList) != 0)
	{
		for each (Texture var in TextureList)
		{
			var.updatetexture(RendererObject);
			SDL_RenderCopy(RendererObject, var.GetTexture(), 0, &var.GetRectange());
		}
	}
	SDL_RenderPresent(RendererObject);
}