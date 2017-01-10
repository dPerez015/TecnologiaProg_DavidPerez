#pragma once
#include "Window.h"
#include <SDL.h>
#include "Renderer.h"
class Hud{
public:
	Hud() {
		esquinasGrid = new SDL_Point[4];
		esquinasGrid[0].x = W.GetWidth()*0.1/2;//limite horizontal izquierdo de la grid 
		esquinasGrid[0].y = W.GetHeigth()*0.3 / 2;//limite vertical arriba
		esquinasGrid[1].x = esquinasGrid[0].x;
		esquinasGrid[1].y = W.GetHeigth() - (esquinasGrid[0].y);
		esquinasGrid[2].x = W.GetWidth()-esquinasGrid[0].x;
		esquinasGrid[2].y = esquinasGrid[1].y;
		esquinasGrid[3].x = esquinasGrid[2].x;
		esquinasGrid[3].y = esquinasGrid[0].y;
	}
	~Hud() {
	
	}

	void draw() {
		SDL_SetRenderDrawColor(R, 0, 0, 0, 255);
	}

private:
	SDL_Point* esquinasGrid;
};

