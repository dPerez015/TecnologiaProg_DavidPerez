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
public:
	const float FPS = 60.f;//Fotogramas por segundo predeterminados
	const float TICKS_PER_FRAME = 1.f / FPS;//Obtencion del numero de millisecs por Frame
	//Singelton
	inline static TimeManager &Ins() {
		static TimeManager TM;
		return TM;
	}
	//Actualiza el tiempo del juego 
	void Updating() {
		deltatime = float(Now() - lastTime) / SDL_GetPerformanceFrequency();//Calcula la diferencia de tiempo
		lastTime = Now();
	}
	//Obtiene el valor del contador de tiempo     
	inline Uint64 Now() {
		return SDL_GetPerformanceCounter();
	}
	inline float GetDeltaTime() {
		return deltatime;
	}

private:
	//Variables
	float deltatime = 0.f;//Deltatime en segundos
	Uint64 lastTime = Now();//Variable que guarda el ultimo valor de tiempo
};
