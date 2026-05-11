// ResourceManager.h
#pragma once
#include <string>
#include <unordered_map>
#include <memory>

namespace Motor3D {
namespace Resources {
class Resource {
public:
    virtual ~Resource() = default;
};

class ResourceManager {
public:
    template<typename T>
    std::shared_ptr<T> Load(const std::string& name);
    void Unload(const std::string& name);
    void UnloadAll();
private:
    std::unordered_map<std::string, std::shared_ptr<Resource>> resources;
};
}}
