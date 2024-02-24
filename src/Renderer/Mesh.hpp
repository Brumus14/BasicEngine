#pragma once

#include <bgfx/bgfx.h>
#include <glm/glm.hpp>
#include <vector>

class Mesh {
public:
  //TODO separate structs into separate class
  //TODO Add different types of vertices like texture, colour, normal
  struct Vertex {
    /* glm::vec3 position; */
    float x, y, z;
    /* uint32_t colour; */
  };

  Mesh(std::vector<Vertex> vertices, std::vector<uint16_t> indices);
  ~Mesh();

  bgfx::VertexBufferHandle GetVertexBufferHandle();
  bgfx::IndexBufferHandle GetIndexBufferHandle();

private:
  std::vector<Vertex> vertices;
  std::vector<uint16_t> indices;

  bgfx::VertexLayout vertexLayout;
  bgfx::VertexBufferHandle vertexBufferHandle;
  bgfx::IndexBufferHandle indexBufferHandle;

  //TODO maybe use arrays instead
  void Create(std::vector<Vertex> vertices, std::vector<uint16_t> indices);
};
