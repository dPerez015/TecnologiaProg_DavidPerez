#include <SDL.h>
#include <string>

#define W Window::Instance()

class Window{
	SDL_Window *m_SDLWindow;
	const std::string m_name;
	const int m_screenWidth, m_screenHeight;

	Window(std::string name, int screenWidth, int screenHeight) :m_name(name), m_screenWidth(screenWidth), m_screenHeight(screenHeight){
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
		m_SDLWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

	}


	inline static Window &Instance(std::string name, int screenWidth, int screenHeight) {
		static Window window(name, screenWidth, screenHeight);
		return window;
	
	}

}