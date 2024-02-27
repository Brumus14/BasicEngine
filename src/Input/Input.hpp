#pragma once

#include <GLFW/glfw3.h>
#include "Keyboard.hpp"
#include "Mouse.hpp"

class Input {
public:
  GLFWwindow * window;
  Keyboard keyboard;
  Mouse mouse;

  Input(GLFWwindow * window);
  ~Input();
};
