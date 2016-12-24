#pragma once

#include <SDL.h>
#include <queue>
#include <unordered_map>
#include <iostream>

#define InMan InputManager::Ins()

class InputManager {
private:
	//estados de las keys
	enum class StatesKey{
		NO_PRESSED,
		PRESSED,
		HOLD, 
		NOT_HOLD
	};
	//determinar si has salido del juego
	bool outGame = false;
	//mapa de las keys (las keys son la clave de las teclas y se guarda un estado)
	std::unordered_map<Uint32 ,StatesKey> inpValMap;
	//cola que va guardando los estados que se van produciendo en el map
	std::queue<StatesKey*> inpVal;
	//Singleton
	InputManager() = default;
	InputManager(const InputManager &data) = delete;
	InputManager &operator=(const InputManager &data) = delete;

	//le pasas un estado y te devuelve true si esta en ese, false si no. 
	template<Uint32 key, StatesKey val> bool IsCorrect() {
		auto it = inpValMap.find(key);
		return (it != inpValMap.end()) ? it->second == val: false;/*comprueba que no esta al final de la iteracion y despues comprueba si val es igual
																  al valor de la key en la que esta, en el caso de que asi sea devuelbe false*/
	}
public:

	//Singelton
	inline static InputManager &Ins() {
		static InputManager IM;
		return IM;
	}
	//Update del estado de las teclas
	void Updating(void) {
		SDL_Event events;
		while (SDL_PollEvent(&events) != 0) {
			switch (events.type) {
			case SDL_QUIT:
				outGame = true;//al salir del juego cambia el estado de la variable a true
				break;
			case SDL_KEYDOWN:
				inpVal.push(&(inpValMap[events.key.keysym.sym] = StatesKey::PRESSED));//Cuando se aprieta una tecla se guarda el estado Pressed
				break;
			case SDL_KEYUP:
				inpVal.push(&(inpValMap[events.key.keysym.sym] = StatesKey::NO_PRESSED));//Cuando la tecla no esta apretada se guarda el estado No_Pressed
				break;
			}
		}
	}
	//Comprobación de outGame
	inline bool stillThere(){
		return outGame;
	}
	//Comprueba que la tecla este apretada
	template<Uint32 key> bool KeyPressed() {
		return IsCorrect<key, StatesKey::PRESSED>();
	}
	//Comprueba que la tecla no este apretada 
	template<Uint32 key> bool KeyUnPressed() {
		return IsCorrect<key, StatesKey::NO_PRESSED>();
	}
};

