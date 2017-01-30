#pragma once

#include "Window.h"
#include "Renderer.h"
#include "InputManager.h"
#include "GameScene.h"
#include "MenuScene.h"
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
		R.loadTexture<ObjectID::FLECHA>("flecha.png");
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
		SM.AddScene<MenuScene>();
	}
	
	void Run(std::string name, int screenWidth, int screenHeight) {

		//INIT
		Window::Instance(name, screenWidth, screenHeight);//init window
		//cargar sprites
		loadRes();
		addScenes();
		LvLM.loadStaditics();
		
		LvLM.theDif = dificulty::MEDIUM;

		SM.SetCurScene<MenuScene>();
		//Scene *&myCurScene(SM.GetCurScene());

		bool isRunning = true;
		LvLM.timeLastUpdate = 0;
		//GAME LOOP
		while (isRunning&&InMan.stillThere()) {
			//UPDATE
			LvLM.timeLastUpdate += TiMan.GetDeltaTime();//coge el tiempo que lleva en esta iteracion cuando porfin ejecuta el update
			InMan.Updating();//actualiza los inputs
			TiMan.Updating();
			
			SM.GetCurScene()->Update();
			//DRAW
			R.Clear();
			//currScene.Draw();
			SM.GetCurScene()->Draw();
			//theHud.draw();
			//pintar objetos
			R.Render();
		}
	}
};