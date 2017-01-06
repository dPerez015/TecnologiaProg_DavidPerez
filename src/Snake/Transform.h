#pragma once
#include <SDL.h>

struct Transform{
	SDL_Rect rect;
	Transform() {
		rect.x = 0;
		rect.y = 0;
		rect.w = 0;
		rect.h = 0;
	}
	Transform(int aX, int aY){
		rect.x = aX;
		rect.y = aY;
		rect.w = 0;
		rect.h = 0;
	}
	Transform(int aX, int aY, int aW, int aH) {
		rect.x = aX;
		rect.y = aY;
		rect.w = aW;
		rect.h = aH;
	}
	inline const SDL_Rect &operator()(void){ return rect; }
	friend bool operator==(Transform &lhs, Transform &rhs) {
		return (lhs.rect.x == rhs.rect.x &&
			lhs.rect.y == rhs.rect.y &&
			lhs.rect.w == rhs.rect.w &&
			lhs.rect.h == rhs.rect.h);
	}
}; 