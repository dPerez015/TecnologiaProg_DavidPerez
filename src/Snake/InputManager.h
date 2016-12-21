#pragma once

#include <SDL.h>
#include <queue>
#include <unordered_map>
#include <iostream>

#define InMan InputManager::Ins()

/*To do: Insert a listing method, convert the header to singeltone, ue the maps and the queues to make it more eficient and
*Change the Updating skeletone to make it better(now it is a shit)
*/

class InputManager {
private:
	bool onGoing = true;
	bool arrowUp = false;
	bool arrowDown = false;
	bool arrowRight = false;
	bool arrowLeft = false;
	bool escPressed = false;
	bool entPressed = false;
private:
	InputManager() = default;
public:

	//Singelton
	inline static InputManager &Ins() {
		static InputManager IM;
		return IM;
	}



	void Updating(void) {
		SDL_Event events;
			while (SDL_PollEvent(&events) != 0) {
				if (events.type == SDL_QUIT) {
					onGoing == false;
				}
				else if (events.type == SDL_KEYDOWN) {
					switch (events.key.keysym.sym) {
					case SDLK_UP:
						arrowUp = true;
						break;
					case SDLK_DOWN:
						arrowDown = true;
						break;
					case SDLK_LEFT:
						arrowLeft = true;
						break;
					case SDLK_RIGHT:
						arrowRight = true;
						break;
					case SDLK_ESCAPE:
						escPressed = true;
						break;
					case SDLK_KP_ENTER:
						entPressed = true;
						break;
					}
				}
			}
		}
};

