/*#pragma once
#include <string>
#include "Scene.h"
#include "Grid.h"
#include "Hud.h"
#include "SceneManager.h"

class GameScene: Scene{
public:
	explicit GameScene();
	~GameScene() override;
	virtual void OnEntry(void) override;
	virtual void OnExit(void)  override;
	virtual void Update(void)  override;
	virtual void Draw() override;
	void loadResources();
private:
	int numOfRows, numOfColums, numFood;
	float timeDelay;
	Grid theGrid;
	Hud theHud;
	dificulty theDificulty;
};*/