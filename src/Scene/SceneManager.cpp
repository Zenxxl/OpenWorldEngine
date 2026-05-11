// SceneManager.cpp
#include "SceneManager.h"

namespace Motor3D {
namespace Scene {

Scene::Scene(const std::string& name) : name(name) {}
Scene::~Scene() { Unload(); }
void Scene::Load() {/* Cargar recursos y entidades */}
void Scene::Unload() {/* Liberar recursos y entidades */}
Motor3D::ECS::Registry& Scene::GetRegistry() { return registry; }

void SceneManager::LoadScene(const std::string& name) {
    if (loadedScenes.find(name) == loadedScenes.end()) {
        loadedScenes[name] = std::make_unique<Scene>(name);
        loadedScenes[name]->Load();
    }
    activeScene = name;
}
void SceneManager::UnloadScene(const std::string& name) {
    loadedScenes.erase(name);
    if (activeScene == name) activeScene.clear();
}
void SceneManager::UpdateStreaming(float playerX, float playerY, float playerZ) {
    // Aquí se implementaría la lógica de streaming de mundo abierto
}
Scene* SceneManager::GetActiveScene() {
    if (activeScene.empty()) return nullptr;
    return loadedScenes[activeScene].get();
}
}}
