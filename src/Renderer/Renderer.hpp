#pragma once

#include <bgfx/bgfx.h>
#include "Window/RenderWindow.hpp"
#include "ShaderProgram.hpp"

class Renderer {
public:
  Renderer(RenderWindow * window);
  ~Renderer();

  void RenderBegin();
  void Render(bgfx::VertexBufferHandle vertexBuffer, bgfx::IndexBufferHandle indexBuffer, ShaderProgram * shaderProgram, float runTime);
  void RenderEnd();

private:
  RenderWindow * window;

  //TODO manage views better
  bgfx::ViewId view;
};
