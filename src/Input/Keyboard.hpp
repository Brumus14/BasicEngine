#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>

// Rework to abstract GLFW key codes

class Keyboard {
public:
  enum KeyState {
    NoState,
    Down,
    Up
  };

  struct KeyData {
    bool pressed;
    KeyState state;
  };

  Keyboard(GLFWwindow * window);
  ~Keyboard();

  void UpdateKeyStates();

  KeyData GetKey(int key);
  void UpdateKey(int key, KeyData data);

private:
  GLFWwindow * window;

  std::unordered_map<int, KeyData> keys;

  static void KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);
};
