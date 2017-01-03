#pragma once

#include "Window.h"
#include "Renderer.h"
#include "InputManager.h"

namespace GameEngine {//como solo son funciones lo podemos iniciar como namespace
	void loadRes() {
		//Cargar los archivos en el renderer;
	}
	void addScenes() {
		//cargar las diferentes escenas
	}

	void Run(std::string name, int screenWidth, int screenHeight) {
		//INIT
		Window::Instance(name, screenWidth, screenHeight);//init window
		loadRes();//cargar sprites
		addScenes();//cargar escena
		//cargar escena actual
		//init renderer
		bool isRunning = true;//Gameloop on
		//GAME LOOP
		while (isRunning&&InMan.stillThere()) {
			//UPDATE
			InMan.Updating();
			//DRAW
			R.Clear();
			//pintar objetos
			R.Render();

		}
	}

};