#pragma once

#include "Window.h"
#include "Renderer.h"
#include "InputManager.h"
#include "TypeEnums.h"
#include "GameScene.h"

namespace GameEngine {//como solo son funciones lo podemos iniciar como namespace
	void loadRes() {
		//Cargar los archivos en el renderer;
		R.loadTexture<ObjectID::SNAKE_FOOD>("snake_spritesheet.jpg");
		R.loadTexture<ObjectID::BLOCK>("block.png");
		R.FillSpriteCuts<typeOfSquare::HEAD>(0,25,25,25);
		R.FillSpriteCuts<typeOfSquare::BODY>(25, 25, 25, 25);
		R.FillSpriteCuts<typeOfSquare::TAIL>(50, 25, 25, 25);
		R.FillSpriteCuts<typeOfSquare::CURVE>(25, 0, 25, 25);
		R.FillSpriteCuts<typeOfSquare::FOOD>(50, 0, 25, 25);
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
		//GameScene currScene(dificulty::EASY);
		Grid theGrid = Grid(10, 15);
		//init renderer
		bool isRunning = true;//Gameloop on
		//GAME LOOP
		while (isRunning&&InMan.stillThere()) {
			//UPDATE
			InMan.Updating();
			theGrid.update();
			//DRAW
			R.Clear();
			//currScene.Draw();
			theGrid.draw();
			//pintar objetos
			R.Render();

		}
	}

};