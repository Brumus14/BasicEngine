#pragma once

#include <bgfx/bgfx.h>
#include "Window/RenderWindow.hpp"

class Renderer {
public:
  Renderer(RenderWindow * window);
  ~Renderer();

private:
  RenderWindow * window;

  //TODO manage views better
  bgfx::ViewId view;
};
