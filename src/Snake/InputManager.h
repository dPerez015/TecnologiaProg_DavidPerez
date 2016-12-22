#pragma once

#include <SDL.h>
#include <queue>
#include <unordered_map>
#include <iostream>

#define InMan InputManager::Ins()

class InputManager {
private:
	enum class StatesKey {
		NO_PRESSED,
		PRESSED,
		PRESSING
	};

	bool outGame = false;
	std::unordered_map<Uint32 ,StatesKey> inpValMap;
	std::queue<StatesKey*> inpVal;

	InputManager() = default;
	InputManager(const InputManager &data) = delete;
	InputManager &operator=(const InputManager &data) = delete;

	template<Uint32 key, StatesKey val> bool IsCorrect() {
		auto it = inpValMap.find(key);
		return (it != inpValMap.end()) ? it->second == val: false;
	}
public:

	//Singelton
	inline static InputManager &Ins() {
		static InputManager IM;
		return IM;
	}

	void Updating(void) {
		SDL_Event events;
		while (SDL_PollEvent(&events) != 0) {
			switch (events.type) {
			case SDL_QUIT:
				outGame = true;
				break;
			case SDL_KEYDOWN:
				inpVal.push(&(inpValMap[events.key.keysym.sym] = StatesKey::PRESSED));
				break;
			case SDL_KEYUP:
				inpVal.push(&(inpValMap[events.key.keysym.sym] = StatesKey::NO_PRESSED));
				break;
			}
		}
	}

	inline bool stillThere(){
		return outGame;
	}

	template<Uint32 key> bool KeyPressed() {
		return IsCorrect<key, StatesKey::PRESSED>();
	}

	template<Uint32 key> bool KeyUnPressed() {
		return IsCorrect<key, StatesKey::NO_PRESSED>();
	}
};

