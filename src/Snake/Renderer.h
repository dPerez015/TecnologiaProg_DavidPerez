#pragma once
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Window.h"

#include <string>
#include <unordered_map>

#include "ID.h"
#include "Transform.h"

#include "ResourceFiles.h"


#define R Renderer::Instance()

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
			if (IMG_Init(imgFlags) != imgFlags)throw "Error al iniciar sdl_IMG";
			//init ttf
			if (TTF_Init() == -1) throw "Error al iniciar SDL_TTF";
		}
		catch (const std::string msg) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", msg);
		}
	}
public:
	inline static Renderer &Instance() {
		static Renderer rend;
		return rend;
	}

	template <ObjectID Id>void loadTexture(std::string filename) {
		try {
			auto loadedImg = IMG_Load(RESOURCE_FILE(filename));//copia "../../res/"+ filename, lo pasa a string, i carga la imagen
			if (loadedImg != nullptr) {
				theImages.emplace(Id, SDL_CreateTextureFromSurface(myRenderer, loadedImg));
			}

			else throw "no se ha cargado bien la imagen";
		}
		catch (const char* msg) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", msg);
		}
	}
	void Push (SDL_Surface *surface, Transform transform) {
		//SDL_RenderCopy(myRenderer, );
	}
	void Push(ObjectID Id, Transform transform) {
		//SDL_RenderCopy(myRenderer, theImages[Id], nullptr, transform)
	}
	void Clear(void) {		
		if (SDL_RenderClear(myRenderer)<0) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
		} 
	}
	void Render(void) { SDL_RenderPresent(myRenderer); }
private:
	std::unordered_map<ObjectID, SDL_Texture*> theImages;
	SDL_Renderer* myRenderer;
};
