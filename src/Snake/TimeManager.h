#pragma once
#include <SDL.h>
#include <functional>

#define TiMan TimeManager::Ins()

class TimeManager{
private:
	//Singelton 
	TimeManager() = default;
	TimeManager(const TimeManager &data) = delete;
	TimeManager &operator=(const TimeManager &data) = delete; 
	//Variables
	float deltatime = 0.f;
	Uint64 lastTime = GetCurTime();
	float renderTime = 0;
public:
	//
	const float FPS = 60.f;
	const float TICKS_PER_FRAME = 1.f / FPS;
	//Singelton
	inline static TimeManager &Ins() {
		static TimeManager TM;
		return TM;
	}

	inline Uint64 GetCurTime() {
		return SDL_GetPerformanceCounter();
	}
	inline float GetDeltaTime() { 
		return deltatime; 
	}
	
	void Updating(std::function<void()>gameUpdate) {
		deltatime = float(GetCurTime() - lastTime) / SDL_GetPerformanceFrequency();
		lastTime = GetCurTime();
		renderTime += deltatime;
		while (renderTime >= TICKS_PER_FRAME) {
			gameUpdate();
			renderTime -= TICKS_PER_FRAME;
		}
	}

};
