#include "Window/RenderWindow.hpp"
#include "Renderer/Renderer.hpp"
#include "Utility/File.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/ShaderProgram.hpp"
#include <iostream>

#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

int main () {
  Input input;
  RenderWindow window(800, 600, "Epic Game !", &input);
  Renderer renderer(&window);

  Shader vertexShader("/home/brumus/Documents/Code/C++/BGFX/BasicEngine/res/shaders/vs_basic.bin");
  Shader fragmentShader("/home/brumus/Documents/Code/C++/BGFX/BasicEngine/res/shaders/fs_basic.bin");
  ShaderProgram shaderProgram(&vertexShader, &fragmentShader);

  bgfx::Init bgfxInit;
  bgfxInit.platformData = window.GetPlatformData();
  bgfxInit.resolution.width = 800;
  bgfxInit.resolution.height = 600;
  bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
  bgfxInit.type = bgfx::RendererType::OpenGL;
  bgfx::init(bgfxInit);

  bgfx::ViewId view = 0;
  bgfx::setViewClear(view, BGFX_CLEAR_COLOR);
  bgfx::setViewRect(0, 0, 0, 800, 600);

  bgfx::VertexLayout vertexLayout;
  vertexLayout.begin().add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float).add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true).end();

  struct Vertex {
    float x;
    float y;
    float z;
    uint32_t abgr;
  };

  Vertex vertices[] = {
    {-1.0f,  -1.0f,  0.0f, 0xff000000 },
    { 1.0f,  -1.0f,  0.0f, 0xffffffff },
    { 1.0f, 1.0f,  0.0f, 0xffffffff },
    { -1.0f, 1.0f,  0.0f, 0xff000000 },
  };

  uint16_t indices[] {
    0, 1, 2,
    0, 2, 3
  };

  bgfx::VertexBufferHandle vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(vertices, sizeof(vertices)), vertexLayout);
  bgfx::IndexBufferHandle indexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(indices, sizeof(indices)));

  while (!window.ShouldQuit()) {
    input.keyboard.UpdateKeyStates();
    window.PollEvents();

    if (input.keyboard.GetKey(GLFW_KEY_ESCAPE).state == Keyboard::KeyState::Down) {
      window.Quit();
    }

    renderer.RenderBegin();
    renderer.Render(vertexBuffer, indexBuffer, &shaderProgram);
    renderer.RenderEnd();
  }

  bgfx::destroy(indexBuffer);
  bgfx::destroy(vertexBuffer);

  return 0;
}
