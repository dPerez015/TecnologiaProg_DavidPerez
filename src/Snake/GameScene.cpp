#include "GameScene.h"

GameScene::GameScene(void) {
	
}

void GameScene::OnEntry(void){
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

void GameScene::OnExit(void) {
	BinF.writeBin(LvLM.PlayerName,theGrid.getPunt());
}

void GameScene::Update(void) {
	LvLM.timeLastUpdate += TiMan.GetDeltaTime();//coge el tiempo que lleva en esta iteracion cuando porfin ejecuta el update
	if (LvLM.timeLastUpdate>LvLM.timeDelay) {//si el tiempo desde el ultimo update>el tiempo que prentendemos que haya de delay actualiza la grid
		if (theGrid.isPAlive()) {
			theGrid.update();
			//TODO
			theHud.update(theGrid.getPunt(), theGrid.getVidas());

			LvLM.timeLastUpdate -= LvLM.timeDelay;
		}
		else {
			SM.SetCurScene<MenuScene>();
		}
	}
}

void GameScene::Draw(void) {
	theGrid.draw();
	//draw Hud;
	theHud.draw();
}