#define GLFW_EXPOSE_NATIVE_X11

#include "RenderWindow.hpp"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "Input/Keyboard.hpp"
#include <iostream>

RenderWindow::RenderWindow(unsigned int width, unsigned int height, std::string title, Input * input) : size(width, height), title(title), input(input) {
  Initialise();
  Create();
}

RenderWindow::~RenderWindow() {
  Destroy();
}

void RenderWindow::PollEvents() {
  glfwPollEvents();

  shouldQuit = glfwWindowShouldClose(window);
}

bgfx::PlatformData RenderWindow::GetPlatformData() {
  bgfx::PlatformData platformData;

  //TODO return platform specific data
  platformData.ndt = glfwGetX11Display();
  platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(window);

  return platformData;
}

bool RenderWindow::ShouldQuit() { return shouldQuit; }
void RenderWindow::Quit() { shouldQuit = true; }

glm::tvec2<unsigned int> RenderWindow::GetSize() { return size; }

void RenderWindow::Initialise() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialise GLFW" << std::endl;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void RenderWindow::Create() {
  window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);

  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
  }

  //TODO Use video mode to get monitor size to properly centre
  /* glfwSetWindowPos(window, 2400, 400); */

  // Associate the input pointer with the window
  glfwSetWindowUserPointer(window, input);

  glfwSetKeyCallback(window, KeyCallback);
}

void RenderWindow::Destroy() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void RenderWindow::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {
  if (action == GLFW_REPEAT) { return; }

  //TODO Account for that user pointer may not always be the input
  Input * input = reinterpret_cast<Input*>(glfwGetWindowUserPointer(window));

  Keyboard::KeyData oldData = input->keyboard.GetKey(key);

  Keyboard::KeyData data = { action == GLFW_PRESS, Keyboard::KeyState::NoState };

  if (!oldData.pressed && data.pressed) {
    data.state = Keyboard::KeyState::Down;
  }

  else if (oldData.pressed && !data.pressed) {
    data.state = Keyboard::KeyState::Up;
  }

  input->keyboard.SetKey(key, data);
}
