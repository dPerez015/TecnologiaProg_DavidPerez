#include "RankingScene.h"

RankingScene::RankingScene(void) {}
RankingScene::~RankingScene(void) {}

void RankingScene::OnEntry(void) {
	
	titulo.h = W.GetHeigth() * 1 / 6;
	titulo.w = W.GetWidth() * 2 / 5;
	titulo.x = (W.GetWidth() / 2) - W.GetWidth() / 5;
	titulo.y = 10;

	int tamX = W.GetWidth()/5;
	int tamY = (W.GetHeigth()*9/12)/10;
	int posX=titulo.x;
	int posY= titulo.y+W.GetHeigth()*3/12;

	for (int i = 0; i < 10;i++) {
		puntuaciones[i].x = posX + tamX;
		puntuaciones[i].y = posY;
		puntuaciones[i].w = tamX;
		puntuaciones[i].h = tamY;
		nombres[i].x = posX;
		nombres[i].y = posY;
		nombres[i].w = tamX;
		nombres[i].h = tamY;
		posY += tamY;

		players[i] = BinF.readBin(i);
	}

	teclaSalir.h = W.GetHeigth() / 12;
	teclaSalir.w = W.GetWidth() / 6;
	teclaSalir.x = 5;
	teclaSalir.y = 5;
	
}

void RankingScene::OnExit(void) {}

void RankingScene::Update(void) {
	if (InMan.KeyPressed<SDLK_ESCAPE>()) {
		SM.SetCurScene<MenuScene>();
	}
}
void RankingScene::Draw() {
	GUI::DrawTextSolid<FontID::ARCADE>(std::string("Ranking"), titulo);
	GUI::DrawTextSolid<FontID::ARCADE>(std::string("ESC"), teclaSalir);
	SDL_RenderDrawRect(R.getRenderer(), &titulo);
	for (int i = 0; i < 10;i++) {
		if (players[i].name != "") {
			GUI::DrawTextSolid<FontID::ARCADE>(players[i].name,nombres[i]);
			SDL_RenderDrawRect(R.getRenderer(),&nombres[i] );
			GUI::DrawTextSolid<FontID::ARCADE>(std::to_string(players[i].score),puntuaciones[i]);
		}
		else {
			GUI::DrawTextSolid<FontID::ARCADE>(std::string("-"),nombres[i]);
			GUI::DrawTextSolid<FontID::ARCADE>(std::string("-"),puntuaciones[i]);
		}
	}


}