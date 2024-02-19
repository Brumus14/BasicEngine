#include "Window.hpp"

#include "Input/Keyboard.hpp"
#include <iostream>

Window::Window(unsigned int width, unsigned int height, std::string title, Input * input) : size(width, height), title(title), input(input) {
  Initialise();
  Create();
}

Window::~Window() {
  Destroy();
}

void Window::PollEvents() {
  glfwPollEvents();

  shouldQuit = glfwWindowShouldClose(window);
}

bool Window::ShouldQuit() { return shouldQuit; }
void Window::Quit() { shouldQuit = true; }

void Window::Initialise() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialise GLFW" << std::endl;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void Window::Create() {
  window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);

  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
  }

  //TODO Use video mode to get monitor size to properly centre
  glfwSetWindowPos(window, 2400, 400);

  // Associate the input pointer with the window
  glfwSetWindowUserPointer(window, input);

  glfwSetKeyCallback(window, KeyCallback);
}

void Window::Destroy() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void Window::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {
  if (action == GLFW_REPEAT) { return; }

  //TODO Account for that user pointer may not always be the input
  Input * input = reinterpret_cast<Input*>(glfwGetWindowUserPointer(window));

  Keyboard::KeyData oldData = input->keyboard.GetKey(key);

  Keyboard::KeyData data = {
    action == GLFW_PRESS,
    Keyboard::KeyState::None
  };

  if (!oldData.pressed && data.pressed) {
    data.state = Keyboard::KeyState::Down;
  }

  else if (oldData.pressed && !data.pressed) {
    data.state = Keyboard::KeyState::Up;
  }

  input->keyboard.SetKey(key, data);
}
