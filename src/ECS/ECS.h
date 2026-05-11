// ECS.h
#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <typeindex>
#include <type_traits>

namespace Motor3D {
namespace ECS {
using Entity = uint32_t;
constexpr Entity INVALID_ENTITY = 0;

class IComponentArray {
public:
    virtual ~IComponentArray() = default;
};

template<typename T>
class ComponentArray : public IComponentArray {
public:
    std::unordered_map<Entity, T> components;
};

class Registry {
public:
    Entity CreateEntity();
    void DestroyEntity(Entity entity);
    template<typename T, typename... Args>
    void AddComponent(Entity entity, Args&&... args);
    template<typename T>
    T* GetComponent(Entity entity);
    template<typename T>
    void RemoveComponent(Entity entity);
private:
    Entity nextEntity = 1;
    std::unordered_map<std::type_index, std::unique_ptr<IComponentArray>> componentArrays;
};
}}
