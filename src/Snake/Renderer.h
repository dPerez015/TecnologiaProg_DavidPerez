#pragma once
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "Window.h"

#include <string>
#include <unordered_map>
//#include <utility>

#include "GridRect.h"

#include "ResourceFiles.h"


#define R Renderer::Instance()
using namespace std::string_literals;
struct SpriteCut{
	SDL_Rect rect;
	SDL_Point center;
};

class Renderer {
private:
	Renderer() {
		try {
			myRenderer = SDL_CreateRenderer(W(), -1, SDL_RENDERER_ACCELERATED);
			if (myRenderer == nullptr)throw SDL_GetError();
			//Init rend color
			if (SDL_SetRenderDrawColor(myRenderer, 20, 5, 168, 255) < 0)throw SDL_GetError();
			//init png y jpg loading 
			const int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
			if (IMG_Init(imgFlags) != imgFlags)throw "Error al iniciar sdl_IMG"s;
			//init ttf
			if (TTF_Init() == -1) throw "Error al iniciar SDL_TTF"s;

			//guardar las rotaciones
			rotations.emplace(direction::UP,0);
			rotations.emplace(direction::LEFT, 90);
			rotations.emplace(direction::DOWN, 180);
			rotations.emplace(direction::RIGHT,270);
		}
		catch (const std::string msg) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",(msg+"\nSDL_Error:"+SDL_GetError()).c_str(),nullptr);
		}
	}
public:
	inline static Renderer &Instance() {
		static Renderer rend;
		return rend;
	}
	template <typeOfSquare type>void FillSpriteCuts(int x, int y, int w, int h) {
		SpriteCut sCut;
		sCut.rect.x = x;
		sCut.rect.y = y;
		sCut.rect.w = w;
		sCut.rect.h = h;
		sCut.center.x = sCut.rect.x + (sCut.rect.w / 2);
		sCut.center.y = sCut.rect.y + (sCut.rect.h / 2);
		
		spriteSheetCuts.emplace(type,sCut);
	}
	template <ObjectID Id>void loadTexture(std::string filename) {
		try {
			auto loadedImg = IMG_Load(RESOURCE_FILE(filename));//copia "../../res/"+ filename, lo pasa a string, i carga la imagen
			if (loadedImg != nullptr) {
				theImages.emplace(Id, SDL_CreateTextureFromSurface(myRenderer, loadedImg));
			}

			else throw "no se ha cargado bien la imagen"s;
		}
		catch (const std::string &msg) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", (msg + "\nSDL_Error:" + SDL_GetError()).c_str(), nullptr);
		}
	}
	void Push (SDL_Surface *surface, SDL_Rect rect) {
		//SDL_RenderCopy(myRenderer, );
	}
	void Push(GridRect gRect) {
		try {
			switch (gRect.type)
			{
			case typeOfSquare::BLOCK:
				if (SDL_RenderCopyEx(myRenderer, theImages[ObjectID::BLOCK], &spriteSheetCuts[gRect.type].rect, &gRect.rect, rotations[gRect.dir], NULL, gRect.flip) != 0) {
					throw "Problema al hacer push"s;
				}

				break;
			default:
				if (SDL_RenderCopyEx(myRenderer, theImages[ObjectID::SNAKE_FOOD], &spriteSheetCuts[gRect.type].rect, &gRect.rect, rotations[gRect.dir], NULL, gRect.flip) != 0) {
					throw "Problema al hacer push"s;
				}
				break;
			}
			
		}
		catch (const std::string &msg) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", (msg + "\nSDL_Error:" + SDL_GetError()).c_str(), nullptr);
		}
	}
	
	void Clear(void) {		
		if (SDL_RenderClear(myRenderer)<0) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
		} 
	}
	void Render(void) { SDL_RenderPresent(myRenderer);}
private:
	std::unordered_map<ObjectID, SDL_Texture*> theImages;
	std::unordered_map<typeOfSquare, SpriteCut> spriteSheetCuts;
	std::unordered_map<direction, int> rotations;
	SDL_Renderer* myRenderer;
};
