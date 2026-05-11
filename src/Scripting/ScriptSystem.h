// ScriptSystem.h
#pragma once
#include "Script.h"
#include <vector>
#include <memory>

namespace Motor3D {
namespace Scripting {
class ScriptSystem {
public:
    void AddScript(std::shared_ptr<Script> script);
    void RemoveScript(std::shared_ptr<Script> script);
    void Update(float dt);
private:
    std::vector<std::shared_ptr<Script>> scripts;
};
}}
