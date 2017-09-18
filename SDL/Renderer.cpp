#include "Renderer.h"
#include <tchar.h>



//class Texture : public Renderer
//{
//public:
//	string TextureName;
//	Texture(TextureType Type,string Name, SDL_Rect Rect)
//	{
//		TextureName = Name;
//		_Rect = Rect;
//		_Type = Type;
//		if (Type == TextureType::Text)
//		{
//			_Line = "";
//			TTF_Init();
//			_Font = TTF_OpenFont("arial.ttf", 18);
//		}
//	}
//
//	void updatetexture(SDL_Renderer* RendererObject)
//	{
//		switch (_Type)
//		{
//		case Text:
//			_Surface = TTF_RenderText_Solid(_Font, _Line.c_str(), _TextColor);
//			_Texture = SDL_CreateTextureFromSurface(RendererObject, _Surface); //leakkaa
//			SDL_QueryTexture(_Texture, NULL, NULL, &TextureWidth, &TextureHeight);
//			_Rect.h = TextureHeight;
//			_Rect.w = TextureWidth;
//			SDL_FreeSurface(_Surface);
//			break;
//		case Solid:
//			break;
//		case Box:
//			SDL_SetRenderDrawColor(RendererObject, 0, 0, 0, 0xFF);
//			SDL_RenderDrawRect(RendererObject, &_Rect);
//			SDL_SetRenderDrawColor(RendererObject, 255, 255, 255, 0xFF);
//			break;
//		default:
//			break;
//		}
//		
//		
//	}
//
//	void SetLine(char Key) { _Line.push_back(Key); }
//	void BackspaceLine() { _Line = _Line.substr(0, _Line.size() - 1); }
//	void SetRect(SDL_Rect Rect) { _Rect = Rect; }
//	SDL_Texture* GetTexture() { return _Texture; }
//	SDL_Rect GetRectange() { return _Rect; }
//	string GetLine() { return _Line; }
//	TextureType GetType() { return _Type; }
//
//private:
//	SDL_Surface* _Surface;
//	SDL_Texture* _Texture;
//	SDL_Rect _Rect;
//	SDL_Color _TextColor = { 0,0,0, 255 };
//	TTF_Font* _Font;
//	string _Line;
//	TextureType _Type;
//	int TextureWidth;
//	int TextureHeight;
//};

Texture* Renderer::AddToRenderer(TextureType Type, SDL_Rect Rect)
{
	if (Type == TextureType::TextType)
	{
		Text* NewTexture = new Text(RendererObject, Rect);
		TextureList.push_back(NewTexture);
		return NewTexture;
	}
	else if (Type == TextureType::BoxType)
	{
		Box* NewBox = new Box(RendererObject, Rect, Boxtype::Insert);
		TextureList.push_back(NewBox);
		return NewBox;
	}
}

Renderer::Renderer()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(400, 400, 0, &WindowObject, &RendererObject);
	SDL_SetRenderDrawColor(RendererObject, 255, 255, 255, 0xFF);
	StartTime = std::chrono::system_clock::now();
}


Renderer::~Renderer()
{
	for each(Texture* var in TextureList)
		delete var;
	TextureList.clear();

	SDL_DestroyRenderer(RendererObject);
	SDL_DestroyWindow(WindowObject);
}



void Renderer::Render()
{
	SDL_RenderClear(RendererObject);
	GetFps();
	if (sizeof(TextureList) != 0)
	{
		for each (Texture* var in TextureList)
		{
			if (var->GetType() != BoxType)
			{
				Text* TmpText = dynamic_cast<Text*>(var);
				TmpText->Update();

				SDL_RenderCopy(var->Texture::RenderObject, var->Texture::TextureData(), 0, &var->Rect);
				SDL_DestroyTexture(var->Texture::TextureData());
			}
			else
			{
				SDL_SetRenderDrawColor(var->Texture::RenderObject, 0, 0, 0, 0xFF);
				Box* TmpBox = dynamic_cast<Box*>(var);
				SDL_RenderDrawRect(var->Texture::RenderObject, &TmpBox->Rect);
				SDL_SetRenderDrawColor(var->Texture::RenderObject, 255, 255, 255, 0xFF);
			}
		}
	}
	SDL_RenderPresent(RendererObject);
}

