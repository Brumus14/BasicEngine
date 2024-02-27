#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Mouse {
public:
  Mouse(GLFWwindow * window);
  ~Mouse();

  glm::tvec2<float> GetPosition();
  void UpdatePosition(glm::tvec2<float> position);

private:
  GLFWwindow * window;

  glm::tvec2<float> cursorPosition;

  //TODO change parameter names
  static void CursorPositionCallback(GLFWwindow * window, double xpos, double ypos);
};
