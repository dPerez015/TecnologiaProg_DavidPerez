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
private:
	bool isSelected;
	SDL_Rect rect;
	SDL_Rect fondRect;
	std::string text;

};

