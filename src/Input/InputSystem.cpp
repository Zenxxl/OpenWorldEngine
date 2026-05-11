// InputSystem.cpp
#include "InputSystem.h"

namespace Motor3D {
namespace Input {

void InputSystem::Update() {
    // Aquí se actualizarían los estados de las teclas (transiciones Pressed/Released)
}

void InputSystem::SetKeyState(int key, KeyState state) {
    keyStates[key] = state;
}

KeyState InputSystem::GetKeyState(int key) const {
    auto it = keyStates.find(key);
    if (it != keyStates.end()) return it->second;
    return KeyState::Up;
}

}}
