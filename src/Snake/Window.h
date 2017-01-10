#pragma once
#include <SDL.h>
#include <string>
#include <iostream>

#define W Window::Instance()
class Window {
	Window(std::string name, int screenWidth, int screenHeight) :m_name(name), m_screenWidth(screenWidth), m_screenHeight(screenHeight) {
		try {
			SDL_Init(SDL_INIT_EVERYTHING);//iniciar SDL (con todo)
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");//"seteamos" el filtrado en linear (sirve, por ejemplo, para cuando reescalamos texturas)
			//crear la ventana
			//le pasamos el string nombre como cString, la altura y el ancho, no le indicamos donde la ha de poner, SDL_window_shown no es necesario (si no se especifica HIDDEN siempre sera shown), pero por si acaso lo pongo
			m_SDLWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
			if (m_SDLWindow == nullptr)throw SDL_GetError();//comprovación de que se ha creado bien la ventana;
		}
		catch(const char *msg){
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", msg);
			}
		}
	Window(const Window &rhs) = delete;
	Window &operator=(const Window &rhs) = delete;
public:
	inline static Window &Instance(std::string name="", int screenWidth=0, int screenHeight=0) {//valores por defecto para poder llamar Instance() sin parametros
		static Window window(name, screenWidth, screenHeight);
		return window;
	}
	 
	~Window() {}
	inline SDL_Window* operator()(void)const { return m_SDLWindow; }//sobreescrivimos el operador () para que nos devuelva directamente la SDL_Window
 	int GetWidth(void)const { return m_screenWidth; }
	int GetHeigth(void)const { return m_screenHeight; }

private:
	SDL_Window *m_SDLWindow{ nullptr };
	const std::string m_name;
	const int m_screenWidth, m_screenHeight;
};