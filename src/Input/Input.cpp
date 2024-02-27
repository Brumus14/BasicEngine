#include "Input.hpp"

Input::Input(GLFWwindow * window) : window(window), keyboard(window), mouse(window) {
  glfwSetWindowUserPointer(window, this);
}

Input::~Input() {}
