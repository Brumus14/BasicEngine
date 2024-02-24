#include "Mesh.hpp"

#include <iostream>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint16_t> indices) {
  Create(vertices, indices);
}

Mesh::~Mesh() {
  if (bgfx::isValid(vertexBufferHandle)) {
    bgfx::destroy(vertexBufferHandle);
  }

  if (bgfx::isValid(indexBufferHandle)) {
    bgfx::destroy(indexBufferHandle);
  }
}

bgfx::VertexBufferHandle Mesh::GetVertexBufferHandle() {
  return vertexBufferHandle;
}

bgfx::IndexBufferHandle Mesh::GetIndexBufferHandle() {
  return indexBufferHandle;
}

void Mesh::Create(std::vector<Vertex> vertices, std::vector<uint16_t> indices) {
  this->vertices = vertices;
  this->indices = indices;

  /* vertexLayout.begin().add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float).add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true).end(); */
  vertexLayout.begin().add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float).end();

  vertexBufferHandle = bgfx::createVertexBuffer(bgfx::makeRef(this->vertices.data(), vertices.size() * sizeof(Vertex)), vertexLayout);
  indexBufferHandle = bgfx::createIndexBuffer(bgfx::makeRef(this->indices.data(), indices.size() * sizeof(uint16_t)));
}
