#pragma once
#include "Scene.h"
#include "botones.h"
#include "Window.h"
#include "LvlManager.h"
#include "InputManager.h"
#include <iostream>
#include "SceneManager.h"
#include "GameScene.h"

class MenuScene : public Scene {
public:
	//explicit MenuScene(void);
	explicit MenuScene(void) {
		
	}
	~MenuScene() override {};
	virtual void OnEntry(void) override{
		theDif = LvLM.theDif;
		titulo = "SNAKE";

		int tamX = W.GetWidth() / 4;
		int tamY = W.GetHeigth() / 8;
		int posX = (W.GetWidth() / 2) - (tamX / 2);
		int posY = (W.GetHeigth() / 2) - tamY;
		std::string text = "PLAY";
		playBot.initBoton(tamX, tamY,posX, posY ,text);
		posY += tamY-2;
		text = "Difficulty  MEDIUM";
		selectDifBot.initDeslizador(tamX, tamY, posX, posY, text);
		posY += tamY - 2;
		text = "RANKING";
		RankingBot.initBoton(tamX, tamY, posX, posY, text);
		posY += tamY - 2;
		text = "EXIT";
		ExitBot.initBoton(tamX, tamY, posX, posY, text);

		recTitulo.h = ((W.GetHeigth() * 3) / 8) - 10;
		recTitulo.w = W.GetWidth() / 2;
		recTitulo.x = W.GetWidth() / 4;
		recTitulo.y = 5;

		seleccion = 0;
		playBot.select();
	}
	virtual void OnExit(void)  override{
		LvLM.theDif = theDif;
	}
	virtual void Update(void)  override{
		if (InMan.lastArrowPressed.size() != 0) {
			moveSelection(InMan.lastArrowPressed.top());
			InMan.emptyArrows();
		}
		//mirar si se ha pulsado enter
		if (InMan.KeyPressed<SDLK_RETURN>()) {
			switch (seleccion){
			case 0:
				SM.SetCurScene<GameScene>();
				break;
			case 2:
				//cargar ranking
				break;
			case 3:
				InMan.Kill();
				break;
			default:
				break;
			}

		}

	}
	virtual void Draw() override{
		GUI::DrawTextSolid<FontID::ARCADE>(titulo,recTitulo);

		playBot.draw();
		selectDifBot.draw();
		RankingBot.draw();
		ExitBot.draw();
	}
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