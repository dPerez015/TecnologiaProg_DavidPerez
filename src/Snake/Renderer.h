#pragma once
#include <unordered_map>
#include <SDL_image.h>
#include "ID.h"

class Renderer {
	inline static Renderer &Instance() {
		static Renderer rend;
		return rend;
	}
	template <ObjectsID Id>void loadTexture(std::string filename) {
		auto loadedTexture = IMG_Load(RESOURCE_FILE(filename));//es un define que copia "../../res/"+ filename y lo pasa a string
	}

private:
	std::unordered_map<ObjectID, SDL_Texture> theImages;

};
