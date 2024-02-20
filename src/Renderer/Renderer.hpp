#pragma once

#include <bgfx/bgfx.h>
#include "Window/RenderWindow.hpp"

class Renderer {
public:
  Renderer(RenderWindow * window);
  ~Renderer();

  void Render();

private:
  RenderWindow * window;

  //TODO manage views better
  bgfx::ViewId view;
};
