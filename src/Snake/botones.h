#pragma once
#include "SDL.h"
#include <string>
#include "Renderer.h"
#include "GUI.h"
class Boton{
public:
	Boton() {}
	void initBoton(int tamX, int tamY, int posX, int posY, std::string t) {
		rect.h = tamY;
		rect.w = tamX;
		rect.x = posX;
		rect.y = posY;

		fondRect.h = tamY+3;
		fondRect.w = tamX+3;
		fondRect.x = posX-3;
		fondRect.y = posY-3;
		
		text = t;
		isSelected = false;
	}
	void draw() {
		if (isSelected) {
			SDL_SetRenderDrawColor(R.getRenderer(), 255, 255, 255, 255);
			SDL_RenderDrawRect(R.getRenderer(), &fondRect);
		}
		GUI::DrawTextSolid<FontID::ARCADE>(text, rect);
	}
	inline void select() { isSelected = true; }
	inline void desSelect() { isSelected = false; }
	void setText(std::string t) {
		text = t;
	}
protected:
	bool isSelected;
	SDL_Rect rect;
	SDL_Rect fondRect;
	std::string text;
};

//deslizador de dificultad.
//para las flechas carga la imagen en el renderer y haz un push en el sdlRect que toque (tienes que hacer 2 extras para estas.) durante el Draw. 
//añade un metodo para cambiar el texto que aparece. 
//investiga un poco sobre derivacion y los constructores, para saber si se puede hacer derivando de boton, si no hazlo cutre.

class deslizador:public Boton {
	public:
		void initDeslizador(int tamX, int tamY, int posX, int posY, std::string t) {
			initBoton(tamX, tamY, posX, posY, t);
			flechaD.h = tamY;
			flechaI.h = tamY;
			flechaD.w = tamY;
			flechaI.w = tamY;
			flechaD.y = posY;
			flechaI.y = posY;
			flechaD.x = posX + tamX;
			flechaI.x = posX - tamY;
		}
		void draw(){
			if (isSelected) {
				R.Push(flechaI, false);
				R.Push(flechaD, true);
				SDL_SetRenderDrawColor(R.getRenderer(), 255, 255, 255, 255);
				SDL_RenderDrawRect(R.getRenderer(), &fondRect);
				
			}
			GUI::DrawTextSolid<FontID::ARCADE>(text, rect);
		}
private:
	SDL_Rect flechaD, flechaI;
};
