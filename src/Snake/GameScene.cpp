#include "GameScene.h"
#include "InputManager.h"
GameScene::GameScene(dificulty dif) :theDificulty(dif) {
	numOfRows = 10;
	numOfColums = 15;
	m_grid=Grid(numOfColums, numOfRows);
}
GameScene::~GameScene(void) {}
void GameScene::OnEntry(void) {
	currentState = SceneState::RUNNING;
}
void GameScene::OnExit(void) {}
void GameScene::Update(void) {
	//UPdate player dir
}
void GameScene::Draw(void) {
	m_grid.draw();
	//draw Hud;
}