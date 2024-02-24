#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer(std::vector<uint16_t> indices) {
  Create(indices);
}

IndexBuffer::~IndexBuffer() {
  if (bgfx::isValid(handle)) {
    bgfx::destroy(handle);
  }
}

bgfx::IndexBufferHandle IndexBuffer::GetHandle() { return handle; }

void IndexBuffer::Create(std::vector<uint16_t> indices) {
  this->indices = indices;

  handle = bgfx::createIndexBuffer(bgfx::makeRef(this->indices.data(), indices.size() * sizeof(uint16_t)));
}
