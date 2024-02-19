#include "Window/Window.hpp"
#include <iostream>

int main () {
  Input input;
  Window window(800, 600, "Epic Game !", &input);

  while (!window.ShouldQuit()) {
    window.PollEvents();
    /* std::cout << input.keyboard.GetKey(GLFW_KEY_W).pressed << "   " << (input.keyboard.GetKey(GLFW_KEY_W).state == Keyboard::KeyState::Down) << std::endl; */
    if (input.keyboard.GetKey(GLFW_KEY_ESCAPE).state == Keyboard::KeyState::Down) {
      window.Quit();
    }
    input.keyboard.UpdateKeyStates();
  }

  return 0;
}
