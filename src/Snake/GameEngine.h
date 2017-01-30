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
#include "RankingScene.h"

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
		SM.AddScene<RankingScene>();
	}
	
	void Run(std::string name, int screenWidth, int screenHeight, std::string &pName) {

		//INIT
		Window::Instance(name, screenWidth, screenHeight);//init window
		//cargar sprites
		loadRes();
		addScenes();
		LvLM.loadStaditics();
		LvLM.PlayerName = pName;
		LvLM.theDif = dificulty::MEDIUM;

		SM.SetCurScene<MenuScene>();
		//Scene *&myCurScene(SM.GetCurScene());

		
		LvLM.timeLastUpdate = 0;
		//GAME LOOP
		while (InMan.stillThere()) {
			//UPDATE
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