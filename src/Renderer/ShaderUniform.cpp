#include "ShaderUniform.hpp"

ShaderUniform::ShaderUniform(std::string name, bgfx::UniformType::Enum type) {
  Create(name, type);
}

ShaderUniform::~ShaderUniform() {
  if(bgfx::isValid(handle)) {
    bgfx::destroy(handle);
  }
}

bgfx::UniformHandle ShaderUniform::GetHandle() { return handle; }

//TODO make this more safe
void ShaderUniform::Set(void * value) {
  bgfx::setUniform(handle, value);
}

//TODO abstract so can have float uniform instead of using vec4
void ShaderUniform::Create(std::string name, bgfx::UniformType::Enum type) {
  handle = bgfx::createUniform(name.c_str(), type);
}
