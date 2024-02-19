#pragma once

#include <unordered_map>

// Rework to abstract GLFW key codes

class Keyboard {
public:
  enum KeyState {
    None,
    Down,
    Up
  };

  struct KeyData {
    bool pressed;
    KeyState state;
  };

  void UpdateKeyStates();

  KeyData GetKey(int key);
  void SetKey(int key, KeyData data);

private:
  std::unordered_map<int, KeyData> keys;
};
