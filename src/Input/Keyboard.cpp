#include "Keyboard.hpp"

#include <iostream>
#include "Input.hpp"

Keyboard::Keyboard(GLFWwindow * window) : window(window) {
  glfwSetKeyCallback(window, KeyCallback);
}

Keyboard::~Keyboard() {}

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

void Keyboard::UpdateKey(int key, KeyData data) {
  keys[key] = data;
}

void Keyboard::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {
  if (action == GLFW_REPEAT) { return; }

  //TODO Account for that user pointer may not always be the input
  Input * input = static_cast<Input*>(glfwGetWindowUserPointer(window));

  Keyboard::KeyData oldData = input->keyboard.GetKey(key);

  Keyboard::KeyData data = { action == GLFW_PRESS, Keyboard::KeyState::NoState };

  if (!oldData.pressed && data.pressed) {
    data.state = Keyboard::KeyState::Down;
  }

  else if (oldData.pressed && !data.pressed) {
    data.state = Keyboard::KeyState::Up;
  }

  input->keyboard.UpdateKey(key, data);
}
