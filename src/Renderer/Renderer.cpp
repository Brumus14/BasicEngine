//TODO manage platform specific defines better
#define GLFW_EXPOSE_NATIVE_X11

#include "Renderer.hpp"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Platform/Platform.hpp"

Renderer::Renderer(RenderWindow * window) : window(window) {
  // Don't create a separate render thread
  bgfx::renderFrame();

  //TODO manage better e.g. cross-platform window managing and vsync variable
  bgfx::Init bgfxInit;
  bgfxInit.platformData = window->GetPlatformData();
  bgfxInit.resolution.width = window->GetSize().x;
  bgfxInit.resolution.height = window->GetSize().y;
  bgfxInit.resolution.reset = BGFX_RESET_VSYNC;

  //TODO More dynamic backends, will need to be implemented with shader platform compilation
  bgfxInit.type = bgfx::RendererType::OpenGL;

  bgfx::init(bgfxInit);

  //TODO this doesn't seem very dynamic for multiple renderers
  view = 0;
  bgfx::setViewClear(view, BGFX_CLEAR_COLOR);
  bgfx::setViewRect(view, 0, 0, window->GetSize().x, window->GetSize().y);
}

Renderer::~Renderer() {
  bgfx::shutdown();
}

void Renderer::RenderBegin() {
  bgfx::setDebug(BGFX_DEBUG_TEXT);

  bgfx::touch(view);

  //TODO temp text
  bgfx::dbgTextClear();
  bgfx::dbgTextPrintf(0, 0, 0x0f, "Hello, World!");
}

//TODO implement default shader program
//TODO implement batch rendering where multiple submitted at once
void Renderer::Render(bgfx::VertexBufferHandle vertexBuffer, bgfx::IndexBufferHandle indexBuffer, ShaderProgram * shaderProgram) {
  bgfx::setState(BGFX_STATE_WRITE_R | BGFX_STATE_WRITE_G | BGFX_STATE_WRITE_B | BGFX_STATE_WRITE_A);
  bgfx::setVertexBuffer(0, vertexBuffer);
  bgfx::setIndexBuffer(indexBuffer);
  bgfx::submit(view, shaderProgram->GetHandle());
}

void Renderer::RenderEnd() {
  bgfx::frame();
}
