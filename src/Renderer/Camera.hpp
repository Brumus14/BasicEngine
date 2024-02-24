#pragma once

#include <glm/glm.hpp>
#include "ShaderUniform.hpp"
#include "Window/RenderWindow.hpp"

// TODO cameras for perspective and orthographic (3D/2D)
class Camera {
public:
  //TODO maybe abstract shader uniforms
  Camera(glm::vec3 position, RenderWindow * window, ShaderUniform * viewUniform, ShaderUniform * projectionUniform);
  ~Camera();

  glm::vec3 GetPosition();

  void SetPosition(glm::vec3 position);
  void Move(glm::vec3 deltaPosition);

  //TODO is there a more efficient way than recreating the matrices each time?
  void UpdateMatrices();
  void UpdateUniforms();

private:
  glm::vec3 position;

  ShaderUniform * viewUniform;
  ShaderUniform * projectionUniform;

  glm::mat4 viewMatrix;
  glm::mat4 projectionMatrix;
};
