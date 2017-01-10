#pragma once
#include <iostream>
#include <unordered_map>
#include <list>

#define LvLM LevelManager::Ins()

class LevelManager {
private:
	//Singelton
	LevelManager() = default;
	LevelManager(const LevelManager &data) = delete;
	LevelManager &operator=(const LevelManager &data) = delete;
public:
	//Singelton
	inline static LevelManager &Ins() {
		static LevelManager LvlMan;
		return LvlMan;
	}



};