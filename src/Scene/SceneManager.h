// SceneManager.h
#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include "../ECS/ECS.h"

namespace Motor3D {
namespace Scene {
class Scene {
public:
    Scene(const std::string& name);
    ~Scene();
    void Load();
    void Unload();
    Motor3D::ECS::Registry& GetRegistry();
private:
    std::string name;
    Motor3D::ECS::Registry registry;
};

class SceneManager {
public:
    void LoadScene(const std::string& name);
    void UnloadScene(const std::string& name);
    void UpdateStreaming(float playerX, float playerY, float playerZ);
    Scene* GetActiveScene();
private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> loadedScenes;
    std::string activeScene;
};
}}
