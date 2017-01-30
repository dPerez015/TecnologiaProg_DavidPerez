#pragma once
#include <string>
#include "Scene.h"
#include "Grid.h"
#include "Hud.h"
#include "SceneManager.h"
#include "LvlManager.h"
#include "MenuScene.h"
#include "Ranking.h"
#include "TimeManager.h"

class GameScene : public Scene{
public:
	explicit GameScene();
	~GameScene() override {}
	virtual void OnEntry(void) override;
	virtual void OnExit(void)  override;
	virtual void Update(void)  override;
	virtual void Draw() override;

private:
	int numOfRows, numOfColums, numFood;
	float timeLastUpdate, timeDelay;
	Grid theGrid;
	Hud theHud;
	//dificulty theDificulty;
};