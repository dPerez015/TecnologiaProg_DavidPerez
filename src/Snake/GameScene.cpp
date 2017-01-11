/*#include "GameScene.h"
#include "InputManager.h"
#include "IOManager.h"

GameScene::GameScene():theDificulty(dificulty::EASY) {
	
	//theGrid=Grid(numOfColums, numOfRows);
}

void GameScene::loadResources() {
	switch (theDificulty)
	{
	case dificulty::EASY:
		timeDelay = SM.defaultStats.speed;
		numOfColums = SM.defaultStats.numCol * 5;
		numOfRows = SM.defaultStats.numRows * 5;
		numFood = SM.defaultStats.numOfFood;
		numFood = SM.defaultStats.incrementFood;
		break;
	case dificulty::MEDIUM:
		timeDelay = SM.defaultStats.speed;
		numOfColums = SM.defaultStats.numCol * 2;
		numOfRows = SM.defaultStats.numRows * 2;
		numFood = SM.defaultStats.numOfFood*2;
		numFood = SM.defaultStats.incrementFood*2;
		break;
	case dificulty::HARD:
		timeDelay = SM.defaultStats.speed;
		numOfColums = SM.defaultStats.numCol * 5;
		numOfRows = SM.defaultStats.numRows * 5;
		numFood = SM.defaultStats.numOfFood;
		numFood = SM.defaultStats.incrementFood;
		break;
	default:
		break;
	}
}
GameScene::~GameScene(void) {}
void GameScene::OnEntry(void) {
	currentState = SceneState::RUNNING;
	loadResources();
}
void GameScene::OnExit(void) {}
void GameScene::Update(void) {
	//UPdate player dir
}
void GameScene::Draw(void) {
	theGrid.draw();
	//draw Hud;
}*/