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
	void Updating(std::function<void()>gameUpdate) {
		deltatime = float(Now() - lastTime) / SDL_GetPerformanceFrequency();//Calcula la diferencia de tiempo
		lastTime = Now();
		renderTime += deltatime;//Actualiza renderTime(Se le aplica la diferencia de tiempo)
		while (renderTime >= TICKS_PER_FRAME) {
			gameUpdate();//Passa el estado en el que se encuentra el juego(si esta activo, si no lo esta, etc.)
			renderTime -= TICKS_PER_FRAME;//Se aplican los millisecs por frame al renderTime
		}
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
	float renderTime = 0;//Controlador de tiempo para el rendering
};
