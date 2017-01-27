#pragma once

#include "Window.h"
#include "Renderer.h"
#include "InputManager.h"
#include "GameScene.h"
#include "TimeManager.h"
#include "Hud.h"
#include "SceneManager.h"
#include "Grid.h"
#include "LvlManager.h"

namespace GameEngine {//como solo son funciones lo podemos iniciar como namespace
	void loadRes(void) {
		//Cargar los archivos en el renderer;
		R.loadTexture<ObjectID::SNAKE_FOOD>("snake_spritesheet.jpg");
		R.loadTexture<ObjectID::BLOCK>("block.png");
		R.loadTexture<ObjectID::HEART>("heart.png");
		R.FillSpriteCuts<typeOfSquare::HEAD>(0, 25, 25, 25);
		R.FillSpriteCuts<typeOfSquare::BODY>(25, 25, 25, 25);
		R.FillSpriteCuts<typeOfSquare::TAIL>(50, 26, 24, 25);
		R.FillSpriteCuts<typeOfSquare::CURVE>(25, 0, 25, 24);
		R.FillSpriteCuts<typeOfSquare::FOOD>(50, 0, 25, 24);
		R.loadFont<FontID::ARCADE>("ARCADECLASSIC.ttf", 40);
	}
	void addScenes(void) {
		//cargar las diferentes escenas
		SM.AddScene<GameScene>();
	}
	
	void Run(std::string name, int screenWidth, int screenHeight) {
		
		/*Window::Instance(name, screenWidth, screenHeight);//init window
		loadRes();
		addScenes();//cargar escena
		SM.loadStaditics();
		SM.SetCurScene<SceneManager>();
		Scene *&myCurScene(SM.GetCurScene());

		
		float timeLastUpdate = 0;
		Grid theGrid(10, 15);
		Hud theHud;
		bool isRunning = true;
		//GAME LOOP
		while (isRunning&&InMan.stillThere()) {
			//UPDATE
			timeLastUpdate += TiMan.GetDeltaTime();//coge el tiempo que lleva en esta iteracion cuando porfin ejecuta el update
			InMan.Updating();//actualiza los inputs
			TiMan.Updating();
			if (timeLastUpdate>myCurScene->timeDelay) {//si el tiempo desde el ultimo update>el tiempo que prentendemos que haya de delay actualiza la grid
				theGrid.update();
				timeLastUpdate -= myCurScene->timeDelay;
				//std::cout << timeLastUpdate << std::endl;
			}
			//DRAW
			R.Clear();
			//currScene.Draw();
			theGrid.draw();
			theHud.draw();
			//pintar objetos
			R.Render();
		}*/

		//INIT
		Window::Instance(name, screenWidth, screenHeight);//init window
		//cargar sprites
		loadRes();
		addScenes();
		LvLM.loadStaditics();
		dificulty dif = dificulty::MEDIUM;
		LvLM.theDif = dif;
		//inicializacion de la grid y seteamos las velocidad
		/*Grid theGrid;
		float timeDelay;
		
		//Hud init
		Hud theHud;*/

		SM.SetCurScene<GameScene>();
		Scene *&myCurScene(SM.GetCurScene());

		bool isRunning = true;
		LvLM.timeLastUpdate = 0;
		//GAME LOOP
		while (isRunning&&InMan.stillThere()) {
			//UPDATE
			LvLM.timeLastUpdate += TiMan.GetDeltaTime();//coge el tiempo que lleva en esta iteracion cuando porfin ejecuta el update
			InMan.Updating();//actualiza los inputs
			TiMan.Updating();

			if (LvLM.timeLastUpdate>LvLM.timeDelay) {//si el tiempo desde el ultimo update>el tiempo que prentendemos que haya de delay actualiza la grid
				myCurScene->Update();
				LvLM.timeLastUpdate -= LvLM.timeDelay;
				
			}
			//DRAW
			R.Clear();
			//currScene.Draw();
			myCurScene->Draw();
			//theHud.draw();
			//pintar objetos
			R.Render();
		}
	}

	
	

};