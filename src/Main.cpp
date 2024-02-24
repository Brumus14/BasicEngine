#include "Window/RenderWindow.hpp"
#include "Renderer/Renderer.hpp"
#include "Utility/File.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/ShaderProgram.hpp"
#include "Renderer/ShaderUniform.hpp"
#include "Renderer/Mesh.hpp"
#include "Renderer/VertexBuffer.hpp"
#include "Renderer/IndexBuffer.hpp"
#include "Renderer/Camera.hpp"

#include <glm/ext.hpp>
#include <iostream>

int main () {
  Input input;
  RenderWindow window(1920, 1080, "Epic Game !", &input);
  Renderer renderer(&window);

  ShaderUniform timeUniform("time", bgfx::UniformType::Vec4);
  /* ShaderUniform viewMatrixUniform("viewMatrix", bgfx::UniformType::Mat4); */
  /* ShaderUniform projectionMatrixUniform("projectionMatrix", bgfx::UniformType::Mat4); */
  ShaderUniform modelUniform("model", bgfx::UniformType::Mat4);
  ShaderUniform viewUniform("view", bgfx::UniformType::Mat4);
  ShaderUniform projectionUniform("projection", bgfx::UniformType::Mat4);
  Shader vertexShader("/home/brumus/Documents/Code/C++/BGFX/BasicEngine/res/shaders/vs_basic.bin");
  Shader fragmentShader("/home/brumus/Documents/Code/C++/BGFX/BasicEngine/res/shaders/fs_basic.bin");
  ShaderProgram shaderProgram(&vertexShader, &fragmentShader);

  Camera camera(glm::vec3(0.0f, 0.0f, -10.0f), &window, &viewUniform, &projectionUniform);

  float deltaTime = 0;
  float runTime = 0;

  std::vector<Vertex> vertices = {
    { -0.5f,  -0.5f,  0.5f },
    { 0.5f,  -0.5f,  0.5f },
    { 0.5f, 0.5f,  0.5f },
    { -0.5f, 0.5f,  0.5f },
    { -0.5f,  -0.5f, -0.5f },
    { 0.5f,  -0.5f, -0.5f },
    { 0.5f, 0.5f, -0.5f },
    { -0.5f, 0.5f, -0.5f }
  };

  std::vector<uint16_t> indices = {
    0, 1, 2,
    0, 2, 3,
    1, 5, 6,
    1, 6, 2,
    5, 4, 7,
    5, 7, 6,
    4, 0, 3,
    4, 3, 7,
    3, 2, 6,
    3, 6, 7,
    4, 5, 1,
    4, 1, 0
  };

  VertexBuffer vertexBuffer(vertices);
  IndexBuffer indexBuffer(indices);

  glm::vec3 camPos(0.0f);

  while (!window.ShouldQuit()) {
    input.keyboard.UpdateKeyStates();
    window.PollEvents();

    if (input.keyboard.GetKey(GLFW_KEY_ESCAPE).state == Keyboard::KeyState::Down) {
      window.Quit();
    }

    if (input.keyboard.GetKey(GLFW_KEY_A).pressed) {
      camPos.x += 2.0f * deltaTime;
    }

    if (input.keyboard.GetKey(GLFW_KEY_D).pressed) {
      camPos.x -= 2.0f * deltaTime;
    }

    if (input.keyboard.GetKey(GLFW_KEY_SPACE).pressed) {
      camPos.y += 2.0f * deltaTime;
    }

    if (input.keyboard.GetKey(GLFW_KEY_LEFT_SHIFT).pressed) {
      camPos.y -= 2.0f * deltaTime;
    }

    if (input.keyboard.GetKey(GLFW_KEY_W).pressed) {
      camPos.z += 2.0f * deltaTime;
    }

    if (input.keyboard.GetKey(GLFW_KEY_S).pressed) {
      camPos.z -= 2.0f * deltaTime;
    }

    //TODO more precise delta time calculation with timer utility class
    deltaTime = static_cast<float>(bgfx::getStats()->cpuTimeFrame) / static_cast<float>(bgfx::getStats()->cpuTimerFreq);
    runTime += deltaTime;

    float timeUniformValue[4] = { 0.0, 0.0, 0.0, 0.0 };
    timeUniformValue[0] = runTime;
    timeUniform.Set(timeUniformValue);

    camera.SetPosition(camPos);

    camera.UpdateMatrices();
    camera.UpdateUniforms();

    //TODO display fps in debug text
    /* std::cout << 1 / deltaTime << std::endl; */

    renderer.RenderBegin();

    glm::mat4 model = glm::mat4(1.0f);
    /* model = glm::translate(model, glm::vec3(std::sin(runTime), std::cos(runTime), -5.0f)); */
    /* model = glm::rotate(model, runTime * glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); */
    modelUniform.Set(glm::value_ptr(model));
    renderer.Render(vertexBuffer.GetHandle(), indexBuffer.GetHandle(), &shaderProgram, runTime);

    renderer.RenderEnd();
  }

  return 0;
}
