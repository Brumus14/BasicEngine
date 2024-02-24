#include "Camera.hpp"

#include <glm/ext.hpp>

Camera::Camera(glm::vec3 position, RenderWindow * window, ShaderUniform * viewUniform, ShaderUniform * projectionUniform) : position(position), viewUniform(viewUniform), projectionUniform(projectionUniform) {}

Camera::~Camera() {}

glm::vec3 Camera::GetPosition() { return position; }

void Camera::SetPosition(glm::vec3 position) {
  this->position = position;
}

void Camera::Move(glm::vec3 deltaPosition) {
  position += deltaPosition;
}

void Camera::UpdateMatrices() {
  viewMatrix = glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

  projectionMatrix = glm::perspective(glm::radians(45.0f), (float)1920 / (float)1080, 0.1f, 100.0f);
}

void Camera::UpdateUniforms() {
  viewUniform->Set(glm::value_ptr(viewMatrix));
  projectionUniform->Set(glm::value_ptr(projectionMatrix));
}
