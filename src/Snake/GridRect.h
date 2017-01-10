#pragma once
#include <utility>
//#include "transform.h"
#include <SDL.h>
#include "TypeEnums.h"

struct GridRect {
	/*GridRect() = default;//necesario para la creacionde la grid (inicializacion de array 2D necesita un constructor por defecto);
	GridRect(int posX, int posY, int w, int h) {
		//quiza se tiene que iniciar con un new
		rect.x = posX*w;
		rect.y = posY*h;
		rect.w = w;
		rect.h=h;
	}*/
	typeOfSquare type;
	direction dir;
	SDL_Rect rect;
	SDL_RendererFlip flip;//sirve para saber como hemos de girar el sprite (necesario en las curvas)
};
