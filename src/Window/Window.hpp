#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include "Input/Input.hpp"

class Window {
public:
  Window(unsigned int width, unsigned int height, std::string title, Input * input);
  ~Window();

  void PollEvents();

  //TODO Manage  quitting globally instead of the window?
  bool ShouldQuit();
  void Quit();

private:
  GLFWwindow * window = nullptr;
  glm::tvec2<unsigned int> size;
  std::string title;
  Input * input;

  bool shouldQuit = false;

  void Initialise();
  void Create();
  void Destroy();

  static void KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);
};
