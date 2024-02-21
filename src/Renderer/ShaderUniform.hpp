#pragma once

#include <bgfx/bgfx.h>
#include <string>

class ShaderUniform {
public:
  ShaderUniform(std::string name, bgfx::UniformType::Enum type);
  ~ShaderUniform();

  //TODO maybe abstract bgfx handles
  bgfx::UniformHandle GetHandle();

  void Set(void * value);

private:
  bgfx::UniformHandle handle;

  //TODO abstract bgfx uniform type enum
  void Create(std::string name, bgfx::UniformType::Enum type);
};
