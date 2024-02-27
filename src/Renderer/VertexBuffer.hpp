#pragma once

#include <bgfx/bgfx.h>
#include <glm/glm.hpp>
#include <vector>

//TODO is global struct ok?
//TODO have different vertex types that can be chosen
struct Vertex {
  /* glm::vec3 position; */
  float x, y, z;
  int16_t texCoordX, texCoordY;
  /* uint32_t colour; */
};

class VertexBuffer {
public:
  VertexBuffer(std::vector<Vertex> vertices);
  ~VertexBuffer();

  bgfx::VertexBufferHandle GetHandle();

private:
  //TODO initialise layout differently based on the chosen vertex type
  bgfx::VertexLayout vertexLayout;
  std::vector<Vertex> vertices;
  bgfx::VertexBufferHandle handle;

  void Create(std::vector<Vertex> vertices);
};
