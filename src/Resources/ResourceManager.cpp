// ResourceManager.cpp
#include "ResourceManager.h"

namespace Motor3D {
namespace Resources {

void ResourceManager::Unload(const std::string& name) {
    resources.erase(name);
}

void ResourceManager::UnloadAll() {
    resources.clear();
}

// Nota: La función Load<T> debe ser especializada para cada tipo de recurso (textura, modelo, shader, etc.)
}}
