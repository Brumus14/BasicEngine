#include "Renderer.hpp"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include "Platform/Platform.hpp"

Renderer::Renderer(Window * window) : window(window) {
  bgfx::renderFrame();

  bgfx::Init bgfxInit;

  bgfx::init(bgfxInit);
}

Renderer::~Renderer() {}
