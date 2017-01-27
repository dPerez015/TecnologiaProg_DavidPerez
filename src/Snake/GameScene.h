#pragma once
#include <string>
#include "Scene.h"
#include "Grid.h"
#include "Hud.h"
#include "SceneManager.h"
#include "LvlManager.h"

class GameScene : public Scene{
public:
	explicit GameScene();
	~GameScene() override;
	virtual void OnEntry(void) override;
	virtual void OnExit(void)  override;
	virtual void Update(void)  override;
	virtual void Draw() override;

private:
	int numOfRows, numOfColums, numFood;
	float timeLastUpdate, timeDelay;
	Grid theGrid;
	Hud theHud;
	dificulty theDificulty;
};
GameScene::GameScene() {
}

GameScene::~GameScene(void) {}

void GameScene::OnEntry(void) {
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
void GameScene::OnExit(void) {}
void GameScene::Update(void) {
	theGrid.update();
	//TODO
	//theHud.update();
}
void GameScene::Draw(void) {
	theGrid.draw();
	//draw Hud;
}