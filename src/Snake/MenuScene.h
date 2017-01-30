#pragma once
#include "Scene.h"
#include "botones.h"
#include "Window.h"
//#include "LvlManager.h"
#include "InputManager.h"
#include <iostream>
#include "SceneManager.h"
#include "GameScene.h"

class MenuScene : public Scene {
public:
	//explicit MenuScene(void);
	explicit MenuScene(void);
	~MenuScene() override;
	virtual void OnEntry(void) override;
	virtual void OnExit(void)  override;
	virtual void Update(void)  override;
	virtual void Draw() override;
private:
	void moveSelection(direction& dir) {
		//desseleccionamos la opcion actual
		switch (seleccion) {
		case 0:
			playBot.desSelect();
			break;
		case 1:
			selectDifBot.desSelect();
			break;
		case 2:
			RankingBot.desSelect();
			break;
		case 3:
			ExitBot.desSelect();
			break;
		default:
			break;
		}
		//cambiamos la variable seleccion
		switch (dir) {
		case direction::UP:
			if (--seleccion< 0) {
				seleccion = 3;
			}
			break;
		case direction::LEFT:
			if (seleccion == 1) {
				switch (theDif)
				{
				case dificulty::EASY:
					theDif = dificulty::HARD;
					selectDifBot.setText("Difficulty  Hard");
					break;
				case dificulty::MEDIUM:
					theDif = dificulty::EASY;
					selectDifBot.setText("Difficulty  easy");
					break;
				case dificulty::HARD:
					theDif = dificulty::MEDIUM;
					selectDifBot.setText("Difficulty  medium");
					break;
				default:
					break;
				}
			}
			break;
		case direction::DOWN:
			if (++seleccion> 3) {
				seleccion = 0;
			}
			break;
		case direction::RIGHT:
			if (seleccion == 1) {
				switch (theDif)
				{
				case dificulty::EASY:
					theDif = dificulty::MEDIUM;
					selectDifBot.setText("Difficulty  medium");
					break;
				case dificulty::MEDIUM:
					theDif = dificulty::HARD;
					selectDifBot.setText("Difficulty  hard");
					break;
				case dificulty::HARD:
					theDif = dificulty::EASY;
					selectDifBot.setText("Difficulty  easy");
					break;
				default:
					break;
				}
			}
			break;
		case direction::NONE:
			break;
		default:
			break;
		}
		//"seleccionamos" el boton adecuado
		switch (seleccion) {
		case 0:
			playBot.select();
			break;
		case 1:
			selectDifBot.select();
			break;
		case 2:
			RankingBot.select();
			break;
		case 3:
			ExitBot.select();
			break;
		default:
			break;
		}
	}

private:
	int seleccion;
	std::string titulo;
	SDL_Rect recTitulo;
	dificulty theDif;
	Boton playBot;
	deslizador selectDifBot;
	Boton RankingBot;
	Boton ExitBot;
};