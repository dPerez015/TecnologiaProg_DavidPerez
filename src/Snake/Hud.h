#pragma once
#include "Window.h"
#include <SDL.h>
#include "Renderer.h"
#include "GUI.h"

class Hud{
public:
	Hud() {
		//lineas de la grid
		esquinasGrid = new SDL_Point[5];
		esquinasGrid[0].x = W.GetWidth()*0.1/2;//limite horizontal izquierdo de la grid 
		esquinasGrid[0].y = W.GetHeigth()*0.3 / 2;//limite vertical arriba
		esquinasGrid[1].x = esquinasGrid[0].x;
		esquinasGrid[1].y = W.GetHeigth() - (esquinasGrid[0].y);
		esquinasGrid[2].x = W.GetWidth()-esquinasGrid[0].x;
		esquinasGrid[2].y = esquinasGrid[1].y;
		esquinasGrid[3].x = esquinasGrid[2].x;
		esquinasGrid[3].y = esquinasGrid[0].y;
		esquinasGrid[4].x = esquinasGrid[0].x;
		esquinasGrid[4].y = esquinasGrid[0].y;

		//posicion de la puntuacion
		posPuntuation.x = W.GetWidth()*0.1 / 2;
		posPuntuation.y = W.GetHeigth()*0.02;
		posPuntuation.w = W.GetWidth()*0.3;
		posPuntuation.h = W.GetHeigth()*0.13;
		puntuation = "0000";

		//posicion de las vidas
		for (int i = 0; i < 3; i++) {
			vidas[i].type = typeOfSquare::HEART;
		}
		vidas[0].rect.x = W.GetWidth()*0.7;
		vidas[1].rect.x = W.GetWidth()*0.8;
		vidas[2].rect.x = W.GetWidth()*0.9;
		vidas[2].rect.y = vidas[1].rect.y = vidas[0].rect.y = W.GetHeigth()*0.02;
		vidas[2].rect.w = vidas[1].rect.w = vidas[0].rect.w = W.GetWidth()*0.1;
		vidas[2].rect.h = vidas[1].rect.h = vidas[0].rect.h = W.GetHeigth()*0.1;
	}
	~Hud() {
		 delete esquinasGrid;
	}

	void draw() {
		//colocamos el color negro
		SDL_SetRenderDrawColor(R.getRenderer(), 0, 0, 0, 255);
		//dibujamos lineas de la grid
		SDL_RenderDrawLines(R.getRenderer(), esquinasGrid, 5);
		//puntuacion
		GUI::DrawTextSolid<FontID::ARCADE>(puntuation, posPuntuation);
		//vidas
		DrawLives();
	}

private:
	void DrawLives() {
		for (int i = 0; i < 3;i++) {
			R.Push(vidas[i]);
		}
	}

	SDL_Point* esquinasGrid;

	std::string puntuation;
	SDL_Rect posPuntuation;

	GridRect vidas[3];

};

