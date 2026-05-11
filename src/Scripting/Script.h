// Script.h
#pragma once
#include <cstdint>

namespace Motor3D {
namespace Scripting {
class Script {
public:
    virtual ~Script() = default;
    virtual void OnCreate() {}
    virtual void OnDestroy() {}
    virtual void OnUpdate(float dt) {}
};
}}
