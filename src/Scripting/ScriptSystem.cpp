// ScriptSystem.cpp
#include "ScriptSystem.h"

namespace Motor3D {
namespace Scripting {

void ScriptSystem::AddScript(std::shared_ptr<Script> script) {
    scripts.push_back(script);
    script->OnCreate();
}
void ScriptSystem::RemoveScript(std::shared_ptr<Script> script) {
    scripts.erase(std::remove(scripts.begin(), scripts.end(), script), scripts.end());
    script->OnDestroy();
}
void ScriptSystem::Update(float dt) {
    for (auto& script : scripts) {
        script->OnUpdate(dt);
    }
}

}}
