#include "Mouse.hpp"

#include "Input.hpp"

Mouse::Mouse(GLFWwindow * window) {
  glfwSetCursorPosCallback(window, CursorPositionCallback);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Mouse::~Mouse() {}

glm::vec2 Mouse::GetPosition() { return cursorPosition; }

void Mouse::UpdatePosition(glm::vec2 position) { this->cursorPosition = position; }

void Mouse::CursorPositionCallback(GLFWwindow * window, double xpos, double ypos) {
  Input * input = static_cast<Input*>(glfwGetWindowUserPointer(window));

  input->mouse.UpdatePosition(glm::tvec2<float>(xpos, ypos));
}
