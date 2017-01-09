#pragma once
#include "GameScene.h"
#include "TypeEnums.h"

#define SM SceneManager::Instance()
class SceneManager {
private:
	SceneManager() {
		currentScene = new GameScene(dificulty::EASY);
	}
	~SceneManager() {}
public:
	inline static SceneManager &Instance() {
		static SceneManager sceneManager;
		return sceneManager;
	}
	inline GameScene*& GetCurScene() { return currentScene; }
private:
	GameScene* currentScene;
};