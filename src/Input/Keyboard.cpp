#include "Keyboard.hpp"
#include <iostream>
#include <GLFW/glfw3.h>

void Keyboard::UpdateKeyStates() {
  for (auto & [key, data] : keys) {
    if (data.state == KeyState::Down || data.state == KeyState::Up) {
      data.state = KeyState::NoState;
    }
  }
}

Keyboard::KeyData Keyboard::GetKey(int key) {
  return keys[key];
}

void Keyboard::SetKey(int key, KeyData data) {
  keys[key] = data;
}
