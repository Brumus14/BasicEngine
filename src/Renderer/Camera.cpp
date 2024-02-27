#include "Camera.hpp"

#include <glm/ext.hpp>
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 front, RenderWindow * window, ShaderUniform * viewUniform, ShaderUniform * projectionUniform) : position(position), window(window), viewUniform(viewUniform), projectionUniform(projectionUniform) {
  this->front = glm::normalize(front);
}

Camera::~Camera() {}

glm::vec3 Camera::GetPosition() { return position; }

void Camera::SetPosition(glm::vec3 position) { this->position = position; }
void Camera::Move(glm::vec3 deltaPosition) { position += deltaPosition; }

void Camera::MoveRelativeFront(glm::vec3 deltaPosition) {
  glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
  glm::vec3 up = glm::normalize(glm::cross(right, front));

  position += right * deltaPosition.x;
  position += up * deltaPosition.y;
  position += front * deltaPosition.z;
}

void Camera::SetFront(glm::vec3 front) { this->front = glm::normalize(front); }

void Camera::UpdateMatrices() {
  viewMatrix = glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));

  projectionMatrix = glm::perspective(glm::radians(45.0f), (float)window->GetSize().x / (float)window->GetSize().y, 0.1f, 100.0f);
}

void Camera::UpdateUniforms() {
  viewUniform->Set(glm::value_ptr(viewMatrix));
  projectionUniform->Set(glm::value_ptr(projectionMatrix));
}
