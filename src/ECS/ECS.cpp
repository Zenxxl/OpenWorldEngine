// ECS.cpp
#include "ECS.h"
#include <cassert>

namespace Motor3D {
namespace ECS {

Entity Registry::CreateEntity() {
    return nextEntity++;
}

void Registry::DestroyEntity(Entity entity) {
    for (auto& [type, array] : componentArrays) {
        // No se puede hacer un cast a ComponentArray<void>.
        // En vez de eso, se puede hacer una función virtual para borrar componentes o usar plantillas en el header.
        // Por simplicidad, aquí no se borra explícitamente, pero se puede mejorar con un sistema de callbacks.
    }
}

template<typename T, typename... Args>
void Registry::AddComponent(Entity entity, Args&&... args) {
    auto type = std::type_index(typeid(T));
    if (componentArrays.find(type) == componentArrays.end()) {
        componentArrays[type] = std::make_unique<ComponentArray<T>>();
    }
    auto* array = static_cast<ComponentArray<T>*>(componentArrays[type].get());
    array->components[entity] = T(std::forward<Args>(args)...);
}

template<typename T>
T* Registry::GetComponent(Entity entity) {
    auto type = std::type_index(typeid(T));
    if (componentArrays.find(type) == componentArrays.end()) return nullptr;
    auto* array = static_cast<ComponentArray<T>*>(componentArrays[type].get());
    auto it = array->components.find(entity);
    if (it != array->components.end()) return &it->second;
    return nullptr;
}

template<typename T>
void Registry::RemoveComponent(Entity entity) {
    auto type = std::type_index(typeid(T));
    if (componentArrays.find(type) == componentArrays.end()) return;
    auto* array = static_cast<ComponentArray<T>*>(componentArrays[type].get());
    array->components.erase(entity);
}

// Nota: Las funciones template deben implementarse en el header o especializarse explícitamente.
}}
