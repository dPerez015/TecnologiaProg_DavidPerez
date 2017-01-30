#include "MenuScene.h"

MenuScene::MenuScene(void) {}
MenuScene::~MenuScene(void) {}
void MenuScene::OnEntry(void) {
	theDif = LvLM.theDif;
	titulo = "SNAKE";

	int tamX = W.GetWidth() / 4;
	int tamY = W.GetHeigth() / 8;
	int posX = (W.GetWidth() / 2) - (tamX / 2);
	int posY = (W.GetHeigth() / 2) - tamY;
	std::string text = "PLAY";
	playBot.initBoton(tamX, tamY, posX, posY, text);
	posY += tamY - 2;
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

void MenuScene::OnExit(void) {
	LvLM.theDif = theDif;
}
void MenuScene::Update(void) {
	if (InMan.lastArrowPressed.size() != 0) {
		moveSelection(InMan.lastArrowPressed.top());
		InMan.emptyArrows();
	}
	//mirar si se ha pulsado enter
	if (InMan.KeyPressed<SDLK_RETURN>()) {
		switch (seleccion) {
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

void MenuScene::Draw(void) {
	GUI::DrawTextSolid<FontID::ARCADE>(titulo, recTitulo);

	playBot.draw();
	selectDifBot.draw();
	RankingBot.draw();
	ExitBot.draw();
}
