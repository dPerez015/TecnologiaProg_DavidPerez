#pragma once
#include "Scene.h"
#include <typeindex>
#include <unordered_map>
#include <string>
#include "IOManager.h"
#include "ResourceFiles.h"

#define SM SceneManager::Instance()
using namespace std::string_literals;

// SceneManager class to store and control the whole game scenes
class SceneManager {
public:
	~SceneManager() { for (auto &scene : m_scenes) delete scene.second; }
	inline static SceneManager &Instance() {
		static SceneManager sceneManager;
		return sceneManager;
	}
	template<class S> void AddScene(void) {
		static_assert(std::is_base_of<Scene, S>::value, "Can't add scene that doesn't inherit from IScene");
		m_scenes.emplace(typeid(S), new S);
	}
	template<class S> void SetCurScene(void) {
		try {
			static_assert(std::is_base_of<Scene, S>::value, "Can't add scene that doesn't inherit from IScene, estaba seteando currscene");
			if (m_curScene != nullptr)
				m_curScene->OnExit(),
				m_curScene->SetState<SceneState::SLEEP>();
			if ((m_curScene = GetScene<S>()) != nullptr) {
				m_curScene->SetState<SceneState::RUNNING>();
				m_curScene->OnEntry();
			}
			else throw "La escena no existe"s;
		}
		catch (const std::string &msg) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", (msg + "\nSDL_Error:" + SDL_GetError()).c_str(), nullptr);
		}
	}
	inline Scene *&GetCurScene(void) { return m_curScene; }

private:
	SceneManager() = default;
	SceneManager(const SceneManager &rhs) = delete;
	SceneManager &operator=(const SceneManager &rhs) = delete;
	template<class S> S *GetScene(void) {
		auto scene = m_scenes.find(typeid(S));
		return (scene != m_scenes.end()) ? dynamic_cast<S*>(scene->second) : nullptr;
	}
	
	
private:
	
	std::unordered_map<std::type_index, Scene*> m_scenes;	// Array of screens
	Scene *m_curScene{ nullptr };							// Pointer to the current scene
};