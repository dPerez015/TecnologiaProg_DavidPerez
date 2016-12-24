#pragma once

class GameEngine {
	inline static GameEngine &Instance() {
		static GameEngine gameEngine;
		return gameEngine;
	}
	GameEngine() = default;//optimizacion
	GameEngine(const GameEngine &rhs) = delete;//eliminamos la construccion por copia
	GameEngine &operator=(const GameEngine &rhs) = delete;//eliminamos el operador "="

	void loadRes(){
		//Cargar los archivos en el renderer;
	}

public:
	

	void Run() {
	
	
	}



};