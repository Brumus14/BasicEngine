#include "Window/RenderWindow.hpp"
#include "Renderer/Renderer.hpp"
#include "Utility/File.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/ShaderProgram.hpp"
#include "Renderer/ShaderUniform.hpp"
#include "Renderer/Mesh.hpp"
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

  float deltaTime = 0;
  float runTime = 0;

  /* struct Vertex { */
  /*   float x; */
  /*   float y; */
  /*   float z; */
  /*   uint32_t colour; */
  /* }; */

  struct Vertex {
    float x;
    float y;
    float z;
  };


  std::vector<Vertex> vertices = {
    { -0.5f, -0.5f, 0.0f },
    { 0.5f, -0.5f, 0.0f },
    { 0.0f, 0.5f, 0.0f }
  };

  std::vector<uint16_t> indices = {
    0, 1, 2
  };

  std::vector<float> textureCoords = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.5f, 1.0f
  };



  bgfx::VertexLayout vertexLayout;
  vertexLayout.begin().add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float).end();
  bgfx::VertexBufferHandle vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(vertices.data(), vertices.size() * sizeof(Vertex)), vertexLayout);
  bgfx::IndexBufferHandle indexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(indices.data(), indices.size() * sizeof(uint16_t)));

  glm::mat4 model = glm::mat4(1.0f);

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

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    viewUniform.Set(glm::value_ptr(view));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float)window.GetSize().x / (float)window.GetSize().y, 0.1f, 100.0f);
    projectionUniform.Set(glm::value_ptr(projection));

    //TODO display fps in debug text
    /* std::cout << 1 / deltaTime << std::endl; */

    renderer.RenderBegin();

    modelUniform.Set(glm::value_ptr(model));
    renderer.Render(vertexBuffer, indexBuffer, &shaderProgram, runTime);

    /* model = glm::mat4(1.0f); */
    /* model = glm::rotate(model, runTime * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); */
    /* model = glm::translate(model, glm::vec3(-0.3f, -0.5f, 0.3f)); */
    /* modelUniform.Set(glm::value_ptr(model)); */

    /* renderer.Render(tet.GetVertexBufferHandle(), tet.GetIndexBufferHandle(), &shaderProgram, runTime); */

    /* model = glm::mat4(1.0f); */
    /* model = glm::rotate(model, runTime * glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)); */
    /* modelUniform.Set(glm::value_ptr(model)); */
    /**/
    /* renderer.Render(cube.GetVertexBufferHandle(), cube.GetIndexBufferHandle(), &shaderProgram, runTime); */

    renderer.RenderEnd();
  }

  return 0;
}
