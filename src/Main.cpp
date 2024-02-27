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
#include "stb_image.h"
#include <iostream>
#include <algorithm>

int main() {
  RenderWindow window(1920, 1080, "Epic Game !");
  Input input(window.GetGLFWWindow());
  Renderer renderer(&window);

  ShaderUniform timeUniform("time", bgfx::UniformType::Vec4);
  ShaderUniform modelUniform("model", bgfx::UniformType::Mat4);
  ShaderUniform viewUniform("view", bgfx::UniformType::Mat4);
  ShaderUniform projectionUniform("projection", bgfx::UniformType::Mat4);
  Shader vertexShader("/home/brumus/Documents/Code/C++/BGFX/BasicEngine/res/Shaders/vs_basic.bin");
  Shader fragmentShader("/home/brumus/Documents/Code/C++/BGFX/BasicEngine/res/Shaders/fs_basic.bin");
  ShaderProgram shaderProgram(&vertexShader, &fragmentShader);

  Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), &window, &viewUniform, &projectionUniform);

  int width, height, channels;
  unsigned char * data = stbi_load("/home/brumus/Documents/Code/C++/BGFX/BasicEngine/res/Textures/blocks.png", &width, &height, &channels, STBI_rgb);
  if (data == NULL) { std::cout << "\n\n\n\n\n\n\n\n\nERROR LOADING IMAGE\n\n\n\n\n\n\n\n\n" << std::endl; }
  bgfx::TextureHandle textureHandle = bgfx::createTexture2D(width, height, false, 1, bgfx::TextureFormat::RGB8, BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT, bgfx::makeRef(data, width * height * 3));

  ShaderUniform textureUniform("s_tex", bgfx::UniformType::Sampler);

  float deltaTime = 0;
  float runTime = 0;

  std::vector<Vertex> vertices = {
    /* { -0.5f, -0.5f, 0.5f, { 0.0f, 0.0f } }, */
    /* { 0.5f, -0.5f, 0.5f, { 1.0f, 0.0f } }, */
    /* { 0.5f, 0.5f, 0.5f, { 0.0f, 1.0f } }, */
    /* { -0.5f, 0.5f, 0.5f, { 1.0f, 1.0f } }, */
    /* { -0.5f, -0.5f, -0.5f, { 0.0f, 0.0f } }, */
    /* { 0.5f, -0.5f, -0.5f, { 1.0f, 0.0f } }, */
    /* { 0.5f, 0.5f, -0.5f, { 0.0f, 1.0f } }, */
    /* { -0.5f, 0.5f, -0.5f, { 1.0f, 1.0f } } */
    { 0.5f, 0.5f, 0.0f, INT16_MAX, 0 },
    { 0.5f, -0.5f, 0.0f, INT16_MAX, INT16_MAX },
    { -0.5f, -0.5f, 0.0f, 0, INT16_MAX },
    { -0.5f, 0.5f, 0.0f, 0, 0 },
  };

  std::vector<uint16_t> indices = {
    0, 1, 2,
    0, 2, 3,
    /* 1, 5, 6, */
    /* 1, 6, 2, */
    /* 5, 4, 7, */
    /* 5, 7, 6, */
    /* 4, 0, 3, */
    /* 4, 3, 7, */
    /* 3, 2, 6, */
    /* 3, 6, 7, */
    /* 4, 5, 1, */
    /* 4, 1, 0 */
  };

  VertexBuffer vertexBuffer(vertices);
  IndexBuffer indexBuffer(indices);

  glm::vec3 camDelta(0.0f);
  float pitch = 0.0f;
  float yaw = 0.0f;

  glm::vec2 lastCursorPos(0.0f);
  glm::vec2 cursorPos;
  glm::vec2 cursorPosDelta;
  const float sensitivity = 0.1f;

  while (!window.ShouldQuit()) {
    input.keyboard.UpdateKeyStates();
    window.PollEvents();

    if (input.keyboard.GetKey(GLFW_KEY_ESCAPE).state == Keyboard::KeyState::Down) {
      window.Quit();
    }

    if (input.keyboard.GetKey(GLFW_KEY_D).pressed) {
      camDelta.x += 1.0f;
    }

    if (input.keyboard.GetKey(GLFW_KEY_A).pressed) {
      camDelta.x -= 1.0f;
    }

    if (input.keyboard.GetKey(GLFW_KEY_SPACE).pressed) {
      camDelta.y += 1.0f;
    }

    if (input.keyboard.GetKey(GLFW_KEY_LEFT_SHIFT).pressed) {
      camDelta.y -= 1.0f;
    }

    if (input.keyboard.GetKey(GLFW_KEY_W).pressed) {
      camDelta.z += 1.0f;
    }

    if (input.keyboard.GetKey(GLFW_KEY_S).pressed) {
      camDelta.z -= 1.0f;
    }

    //TODO more precise delta time calculation with timer utility class
    deltaTime = static_cast<float>(bgfx::getStats()->cpuTimeFrame) / static_cast<float>(bgfx::getStats()->cpuTimerFreq);
    runTime += deltaTime;

    float timeUniformValue[4] = { 0.0, 0.0, 0.0, 0.0 };
    timeUniformValue[0] = runTime;
    timeUniform.Set(timeUniformValue);

    cursorPos = input.mouse.GetPosition();
    cursorPosDelta = glm::vec2(cursorPos.x - lastCursorPos.x, lastCursorPos.y - cursorPos.y);
    lastCursorPos = cursorPos;

    yaw += cursorPosDelta.x * sensitivity;
    pitch += cursorPosDelta.y * sensitivity;

    pitch = std::clamp(pitch, -89.9f, 89.9f);

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(direction);
    camera.SetFront(direction);

    camera.MoveRelativeFront(camDelta * 2.0f * deltaTime);
    camDelta = glm::vec3(0.0f);

    camera.UpdateMatrices();
    camera.UpdateUniforms();

    //TODO display fps in debug text
    /* std::cout << 1 / deltaTime << std::endl; */

    renderer.RenderBegin();

    glm::mat4 model = glm::mat4(1.0f);
    /* model = glm::translate(model, glm::vec3(std::sin(runTime), std::cos(runTime), -5.0f)); */
    /* model = glm::rotate(model, runTime * glm::radians(90.0f), glm::vec3(0.5f, 1.0f, 0.0f)); */
    modelUniform.Set(glm::value_ptr(model));

    bgfx::setTexture(0, textureUniform.GetHandle(), textureHandle);

    renderer.Render(vertexBuffer.GetHandle(), indexBuffer.GetHandle(), &shaderProgram, runTime);

    bgfx::dbgTextPrintf(0, 2, 0x0f, "Front: %f, %f, %f", direction.x, direction.y, direction.z);
    bgfx::dbgTextPrintf(0, 3, 0x0f, "Pos: %f, %f, %f", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

    renderer.RenderEnd();
  }

  return 0;
}
