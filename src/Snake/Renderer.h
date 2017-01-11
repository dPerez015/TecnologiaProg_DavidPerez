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

enum FontStyle {
	FONT_STYLE_BOLD = TTF_STYLE_BOLD,
	FONT_STYLE_ITALIC = TTF_STYLE_ITALIC,
	FONT_STYLE_UNDERLINE = TTF_STYLE_UNDERLINE,
	FONT_STYLE_NORMAL = TTF_STYLE_NORMAL
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
			rotations.emplace(direction::LEFT, 270);
			rotations.emplace(direction::DOWN, 180);
			rotations.emplace(direction::RIGHT,90);

			SDL_Color color;
			color.r = 0;
			color.g = 0;
			color.b = 0;
			color.a = 255;
			theColors.emplace(Colors::BLACK, color);
			color.r = 20;
			color.g = 5;
			color.b = 168;
			color.a = 255;
			theColors.emplace(Colors::BLUE, color);
			
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
		SDL_Rect sCut;
		sCut.x = x;
		sCut.y = y;
		sCut.w = w;
		sCut.h = h;
		
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
	template<FontID id>void loadFont(std::string filename, int size) {
		try {
			if (!theFonts.emplace(id, TTF_OpenFont(RESOURCE_FILE(filename), size)).second) throw "no se ha podido cargar la Font"s;
		}
		catch (const std::string &msg) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", (msg + "\nSDL_Error:" + SDL_GetError()).c_str(), nullptr);
		}
	}
	void Push (SDL_Surface *surface, SDL_Rect rect) {
		try {
			if (surface == nullptr) { throw "La surface es nullptr"s; }
			auto texture = SDL_CreateTextureFromSurface(myRenderer, surface);
			if (SDL_RenderCopy(myRenderer, texture, NULL, &rect) != 0)throw "Problema al renderizar la surface"s;
			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
		
		}
		catch (const std::string &msg) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", (msg + "\nSDL_Error:" + SDL_GetError()).c_str(), nullptr);
		}
	}
	void Push(GridRect gRect) {
		try {
			switch (gRect.type)
			{
			case typeOfSquare::EMPTY:
				break;
			case typeOfSquare::BLOCK:
				if (SDL_RenderCopy(myRenderer, theImages[ObjectID::BLOCK], NULL, &gRect.rect) != 0) {
					throw "Problema al hacer push del bloque"s;
				}
				break;
			case typeOfSquare::HEART:
				if (SDL_RenderCopy(myRenderer, theImages[ObjectID::HEART], NULL, &gRect.rect) != 0) {
					throw "Problema al hacer push del corazon"s;
				}
				break;
			default:
				if (SDL_RenderCopyEx(myRenderer, theImages[ObjectID::SNAKE_FOOD], &spriteSheetCuts[gRect.type], &gRect.rect, rotations[gRect.dir], NULL, gRect.flip) != 0) {
					throw "Problema al hacer push"s;
				}
				break;
			}
			
		}
		catch (const std::string &msg) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", (msg + "\nSDL_Error:" + SDL_GetError()).c_str(), nullptr);
		}
	}
	inline SDL_Renderer* getRenderer(void) { return myRenderer; }
	template<FontID id>TTF_Font* getFont() {
		return theFonts[id];
	}
	template <FontID id, FontStyle style>void setFontStyle() {
		TTF_SetFontStyle(theFonts[id], style);
	}
	void Clear(void) {	
		SDL_SetRenderDrawColor(myRenderer, 20, 5, 168, 255);
		if (SDL_RenderClear(myRenderer)<0) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
		} 
		SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 255);
	}
	void Render(void) { SDL_RenderPresent(myRenderer);}
	std::unordered_map<Colors, SDL_Color> theColors;

private:
	std::unordered_map<FontID, TTF_Font*> theFonts;
	std::unordered_map<ObjectID, SDL_Texture*> theImages;
	std::unordered_map<typeOfSquare, SDL_Rect> spriteSheetCuts;
	std::unordered_map<direction, int> rotations;
	SDL_Renderer* myRenderer;
};
