#include "Window/RenderWindow.hpp"
#include "Renderer/Renderer.hpp"
#include <iostream>

int main () {
  Input input;
  RenderWindow window(800, 600, "Epic Game !", &input);
  Renderer renderer(&window);

  while (!window.ShouldQuit()) {
    input.keyboard.UpdateKeyStates();
    window.PollEvents();

    if (input.keyboard.GetKey(GLFW_KEY_ESCAPE).state == Keyboard::KeyState::Down) {
      window.Quit();
    }
  }

  return 0;
}
