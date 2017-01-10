#pragma once

#include "Window.h"
#include "Renderer.h"
#include "InputManager.h"
#include "TypeEnums.h"
#include "GameScene.h"
#include "TimeManager.h"
#include <iostream>

namespace GameEngine {//como solo son funciones lo podemos iniciar como namespace
	void loadRes(void) {
		//Cargar los archivos en el renderer;
		R.loadTexture<ObjectID::SNAKE_FOOD>("snake_spritesheet.jpg");
		R.loadTexture<ObjectID::BLOCK>("block.png");
		R.FillSpriteCuts<typeOfSquare::HEAD>(0, 25, 25, 25);
		R.FillSpriteCuts<typeOfSquare::BODY>(25, 25, 25, 25);
		R.FillSpriteCuts<typeOfSquare::TAIL>(50, 25, 25, 25);
		R.FillSpriteCuts<typeOfSquare::CURVE>(25, 0, 25, 25);
		R.FillSpriteCuts<typeOfSquare::FOOD>(50, 0, 25, 25);
	}
	void addScenes(void) {
		//cargar las diferentes escenas
	}

	void Run(std::string name, int screenWidth, int screenHeight) {
		//INIT
		Window::Instance(name, screenWidth, screenHeight);//init window
		loadRes();//cargar sprites
		addScenes();//cargar escena
					//cargar escena actual
					//GameScene currScene(dificulty::EASY);
		float timeDelay = 1;
		float timeLastUpdate = 0;
		Grid theGrid(10, 15);
		bool isRunning = true;
		//GAME LOOP
		while (isRunning&&InMan.stillThere()) {
			//UPDATE
			timeLastUpdate += TiMan.GetDeltaTime();//coge el tiempo que lleva en esta iteracion cuando porfin ejecuta el update
			InMan.Updating();//actualiza los inputs
			TiMan.Updating();
			if (timeLastUpdate>timeDelay) {//si el tiempo desde el ultimo update>el tiempo que prentendemos que haya de delay actualiza la grid
				theGrid.update();
				timeLastUpdate -= timeDelay;
				//std::cout << timeLastUpdate << std::endl;
			}
			//DRAW
			R.Clear();
			//currScene.Draw();
			theGrid.draw();
			//pintar objetos
			R.Render();
		}
	}

	
	

};