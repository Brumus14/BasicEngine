#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(std::vector<Vertex> vertices) {
  vertexLayout.begin().add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float).end();

  Create(vertices);
}

VertexBuffer::~VertexBuffer() {
  if (bgfx::isValid(handle)) {
    bgfx::destroy(handle);
  }
}

bgfx::VertexBufferHandle VertexBuffer::GetHandle() { return handle; }

void VertexBuffer::Create(std::vector<Vertex> vertices) {
  this->vertices = vertices;

  handle = bgfx::createVertexBuffer(bgfx::makeRef(this->vertices.data(), vertices.size() * sizeof(Vertex)), vertexLayout);
}
