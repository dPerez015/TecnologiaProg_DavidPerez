#pragma once
#include <string>
#include "Scene.h"
#include "Grid.h"

class GameScene: Scene{
public:
	explicit GameScene();
	~GameScene() override;
	virtual void OnEntry(void) override;
	virtual void OnExit(void)  override;
	virtual void Update(void)  override;
	virtual void Draw() override;
private:
	Grid m_grid;
	
};