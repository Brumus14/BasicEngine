#pragma once

#include <GLFW/glfw3.h>
#include <bgfx/platform.h>
#include <glm/glm.hpp>
#include <string>
#include "Input/Input.hpp"

class RenderWindow {
public:
  RenderWindow(unsigned int width, unsigned int height, std::string title);
  ~RenderWindow();

  void PollEvents();

  GLFWwindow * GetGLFWWindow();

  //TODO move into platform code / class
  bgfx::PlatformData GetPlatformData();

  //TODO Manage  quitting globally instead of the window?
  bool ShouldQuit();
  void Quit();

  glm::tvec2<unsigned int> GetSize();

private:
  GLFWwindow * window = nullptr;
  glm::tvec2<unsigned int> size;
  std::string title;

  bool shouldQuit = false;

  void Initialise();
  void Create();
  void Destroy();

  //TODO maybe separate into keyboard class
  /* static void KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods); */
};
