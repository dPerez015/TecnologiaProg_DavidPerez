#pragma once
#include "SDL.h"
#include "Scene.h"
#include "Window.h"
#include "Ranking.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "MenuScene.h"

class RankingScene :public Scene{
public:
	explicit RankingScene();
	~RankingScene()override;
	virtual void OnEntry(void) override;
	virtual void OnExit(void)  override;
	virtual void Update(void)  override;
	virtual void Draw() override;

private:
	SDL_Rect nombres[10];
	SDL_Rect puntuaciones[10];
	SDL_Rect titulo, teclaSalir;
	HighScores players[10];
	
};