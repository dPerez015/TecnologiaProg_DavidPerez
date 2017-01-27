#pragma once
#include "Scene.h"
#include "botones.h"

class MenuScene : public Scene {
public:
	explicit MenuScene();
	~MenuScene() override;
	virtual void OnEntry(void) override;
	virtual void OnExit(void)  override;
	virtual void Update(void)  override;
	virtual void Draw() override;
private:
	int seleccion;
	dificulty theDif;
	Boton playBot;
	Boton selectDifBot;
	Boton RankingBot;
	Boton ExitBot;
}
//setear la posicion de los botones y la dificultad por defecto
MenuScene::MenuScene(void) {
	theDif = dificulty::MEDIUM;
}

MenuScene::~MenuScene(void) {}

void MenuScene::OnEntry(void) {}

//si se pulsa un boton mover la posicion, si se pulsa enter hacer lo que toque
void MenuScene::Update() {

}
//dibujar los botones 
void MenuScene::Draw() {}