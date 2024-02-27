#pragma once

#include <glm/glm.hpp>
#include "ShaderUniform.hpp"
#include "Window/RenderWindow.hpp"

// TODO cameras for perspective and orthographic (3D/2D)
class Camera {
public:
  //TODO maybe abstract shader uniforms
  Camera(glm::vec3 position, glm::vec3 front, RenderWindow * window, ShaderUniform * viewUniform, ShaderUniform * projectionUniform);
  ~Camera();

  glm::vec3 GetPosition();

  void SetPosition(glm::vec3 position);
  void Move(glm::vec3 deltaPosition);

  void MoveRelativeFront(glm::vec3 deltaPosition);

  void SetFront(glm::vec3 front);

  //TODO is there a more efficient way than recreating the matrices each time?
  void UpdateMatrices();
  void UpdateUniforms();

private:
  RenderWindow * window;

  glm::vec3 position;
  glm::vec3 front;

  ShaderUniform * viewUniform;
  ShaderUniform * projectionUniform;

  glm::mat4 viewMatrix;
  glm::mat4 projectionMatrix;
};
