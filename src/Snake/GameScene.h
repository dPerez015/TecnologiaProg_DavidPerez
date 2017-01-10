#pragma once
#include <string>
#include "Scene.h"
#include "Grid.h"

class GameScene: Scene{
public:
	explicit GameScene(dificulty);
	~GameScene() override;
	virtual void OnEntry(void) override;
	virtual void OnExit(void)  override;
	virtual void Update(void)  override;
	virtual void Draw() override;
private:
	int numOfRows, numOfColums;
	Grid m_grid;
	dificulty theDificulty;
};