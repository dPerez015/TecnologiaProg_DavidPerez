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
	float deltatime = 0.f;//Deltatime en segundos
	Uint64 lastTime = Now();//
	float renderTime = 0;
public:
	const float FPS = 60.f;//Fotogramas por segundo predeterminados
	const float TICKS_PER_FRAME = 1.f / FPS;//
	//Singelton
	inline static TimeManager &Ins() {
		static TimeManager TM;
		return TM;
	}
	//Gets the value of the hight resolution counter 
	inline Uint64 Now() {
		return SDL_GetPerformanceCounter();
	}
	inline float GetDeltaTime() { 
		return deltatime; 
	}
	
	void Updating(std::function<void()>gameUpdate) {
		deltatime = float(Now() - lastTime) / SDL_GetPerformanceFrequency();
		lastTime = Now();
		renderTime += deltatime;//Actualiza renderTime
		while (renderTime >= TICKS_PER_FRAME) {
			gameUpdate();
			renderTime -= TICKS_PER_FRAME;
		}
	}

};
