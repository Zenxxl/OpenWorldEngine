// InputSystem.h
#pragma once
#include <unordered_map>
#include <string>
#include <cstdint>

namespace Motor3D {
namespace Input {
enum class KeyState : uint8_t { Up, Down, Pressed, Released };

class InputSystem {
public:
    void Update();
    void SetKeyState(int key, KeyState state);
    KeyState GetKeyState(int key) const;
private:
    std::unordered_map<int, KeyState> keyStates;
};
}}
