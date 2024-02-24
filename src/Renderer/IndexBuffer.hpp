#pragma once

#include <bgfx/bgfx.h>
#include <vector>

class IndexBuffer {
public:
  //TODO maybe use pointers/references instead same with vertex buffer
  IndexBuffer(std::vector<uint16_t> indices);
  ~IndexBuffer();

  bgfx::IndexBufferHandle GetHandle();

private:
  std::vector<uint16_t> indices;
  bgfx::IndexBufferHandle handle;

  //TODO maybe just use int instead of uint16_t
  void Create(std::vector<uint16_t> indices);
};
