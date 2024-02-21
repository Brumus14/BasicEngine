#include "Window/RenderWindow.hpp"
#include "Renderer/Renderer.hpp"
#include "Utility/File.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/ShaderProgram.hpp"
#include "Renderer/ShaderUniform.hpp"
#include <iostream>

int main () {
  Input input;
  RenderWindow window(1920, 1080, "Epic Game !", &input);
  Renderer renderer(&window);

  ShaderUniform timeUniform("iTime", bgfx::UniformType::Vec4);
  Shader vertexShader("/home/brumus/Documents/Code/C++/BGFX/BasicEngine/res/shaders/vs_basic.bin");
  Shader fragmentShader("/home/brumus/Documents/Code/C++/BGFX/BasicEngine/res/shaders/fs_basic.bin");
  ShaderProgram shaderProgram(&vertexShader, &fragmentShader);

  float deltaTime = 0;
  float runTime = 0;

  bgfx::VertexLayout vertexLayout;
  vertexLayout.begin().add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float).add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true).end();

  struct Vertex {
    float x;
    float y;
    float z;
    uint32_t abgr;
  };

  Vertex vertices[] = {
    { -1.0f,  -1.0f,  0.0f, 0xff000000 },
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

    //TODO more precise delta time calculation with timer utility class
    deltaTime = static_cast<float>(bgfx::getStats()->cpuTimeFrame) / static_cast<float>(bgfx::getStats()->cpuTimerFreq);
    runTime += deltaTime;

    float timeUniformValue[4] = { 0.0, 0.0, 0.0, 0.0 };
    timeUniformValue[0] = runTime;
    timeUniform.Set(timeUniformValue);

    //TODO display fps in debug text
    std::cout << 1 / deltaTime << std::endl;

    renderer.RenderBegin();
    renderer.Render(vertexBuffer, indexBuffer, &shaderProgram);
    renderer.RenderEnd();
  }

  bgfx::destroy(indexBuffer);
  bgfx::destroy(vertexBuffer);

  return 0;
}
