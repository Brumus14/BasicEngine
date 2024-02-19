#pragma once

#include "Window/Window.hpp"

class Renderer {
public:
  Renderer(Window * window);
  ~Renderer();

private:
  Window * window;
};
