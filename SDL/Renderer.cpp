#include "Renderer.h"



class Renderer::Texture
{
public:
	string TextureName;
	Texture(TextureType Type,string Name, SDL_Rect Rect)
	{
		TextureName = Name;
		SetRect(Rect);
		_Type = Type;
		if (Type == TextureType::Text)
		{
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
			_Texture = SDL_CreateTextureFromSurface(RendererObject, _Surface);
			SDL_QueryTexture(_Texture, NULL, NULL, &TextureWidth, &TextureHeight);
			_Rect.h = TextureHeight;
			_Rect.w = TextureWidth;
			SDL_FreeSurface(_Surface);
			break;
		case Solid:
			break;
		case Box:
			SDL_SetRenderDrawColor(RendererObject, 0, 0, 0, 0xFF);
			SDL_RenderFillRect(RendererObject, &_Rect);
			SDL_SetRenderDrawColor(RendererObject, 255, 255, 255, 0xFF);
			break;
		default:
			break;
		}
		
	}

	void SetLine(char Key) { _Line.push_back(Key); }
	void BackspaceLine() { _Line = _Line.substr(0, _Line.size() - 1); }
	void SetRect(SDL_Rect Rect) { _Rect = Rect; }
	SDL_Texture* GetTexture() { return _Texture; }
	SDL_Rect GetRectange() { return _Rect; }
	TextureType Type() { return _Type; }

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
	SDL_CreateWindowAndRenderer(360, 240, 0, &WindowObject, &RendererObject);
	SDL_SetRenderDrawColor(RendererObject, 255, 255, 255, 0xFF);
}


Renderer::~Renderer()
{
}

void Renderer::DestroyTextures()
{
	for each (Texture var in TextureList)
	{
		SDL_DestroyTexture(var.GetTexture());
		
	}
	SDL_DestroyWindow(WindowObject);
	SDL_DestroyRenderer(RendererObject);
}

void Renderer::NewTexture(TextureType Type, string Name, SDL_Rect Rect)
{
	Texture NewTexture = Texture(Type, Name, Rect);
	AddToRenderer(NewTexture);
}

void Renderer::NewTexture(TextureType Type, string Name, int x, int y, int h, int w)
{
	SDL_Rect Rect;
	Rect.x = x;
	Rect.y = y;
	Rect.w = w;
	Rect.h = h;
	Texture NewTexture = Texture(Type, Name, Rect);
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
			if (var.Type() != TextureType::Box)
			{
				SDL_RenderCopy(RendererObject, var.GetTexture(), 0, &var.GetRectange());
			}
		}
	}
	SDL_RenderPresent(RendererObject);
}