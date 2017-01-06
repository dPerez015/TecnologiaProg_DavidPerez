#pragma once
enum class SceneState {
	NONE, //estado por defecto
	RUNNING, //escena activa
	EXIT, //escena saliendo 
	SLEEP //escena parada
};

class Scene{
public:
	explicit Scene()=default;//explicit elimina las conversiones implicitas y las inicializacion por copia
	virtual ~Scene()=default;

	virtual void OnEntry(void)=0;//definicion de un metodo puramente virtual, obligas a sobre-escribirlo
	virtual void OnExit(void)=0;
	virtual void Update(void) = 0;
	virtual void Draw() = 0;

	template <SceneState state> inline void SetState(void) { currentState = state; };
	inline SceneState GetState(void) const { return currentState; }; //el const del final impide que el metodo cambie los valores de las variables de la clase

protected:
	SceneState currentState{ SceneState::NONE };//estado actual de la escena (por defecto NONE)
};

