#pragma once
#include <string>
#include "Scene.h"
#include "Grid.h"
#include "Hud.h"
#include "SceneManager.h"
#include "LvlManager.h"

class GameScene : public Scene{
public:
	explicit GameScene() {}
	~GameScene() override {}
	virtual void OnEntry(void) override {
		currentState = SceneState::RUNNING;
		switch (LvLM.theDif) {
		case dificulty::EASY:
			LvLM.timeDelay = LvLM.defaultStats.speed;
			theGrid.GridInit(LvLM.theDif);
			break;
		case dificulty::MEDIUM:
			LvLM.timeDelay = LvLM.defaultStats.speed / 2;
			theGrid.GridInit(LvLM.theDif);
			break;
		case dificulty::HARD:
			LvLM.timeDelay = LvLM.defaultStats.speed / 3;
			theGrid.GridInit(LvLM.theDif);
			break;
		default:
			break;
		}
	}
	virtual void OnExit(void)  override {
	}
	virtual void Update(void)  override {
		if (LvLM.timeLastUpdate>LvLM.timeDelay) {//si el tiempo desde el ultimo update>el tiempo que prentendemos que haya de delay actualiza la grid
			theGrid.update();
			//TODO
			theHud.update(theGrid.getPunt(), theGrid.getVidas());

			LvLM.timeLastUpdate -= LvLM.timeDelay;
		}
	}
	virtual void Draw() override {
		theGrid.draw();
		//draw Hud;
		theHud.draw();
	}

private:
	int numOfRows, numOfColums, numFood;
	float timeLastUpdate, timeDelay;
	Grid theGrid;
	Hud theHud;
	//dificulty theDificulty;
};