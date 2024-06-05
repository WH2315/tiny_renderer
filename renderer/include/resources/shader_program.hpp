#pragma once

#include "resources/shader.hpp"
#include <memory>

namespace wen {

class ShaderProgram final {
public:
    ShaderProgram();
    ~ShaderProgram();

    ShaderProgram& attachShader(const std::shared_ptr<Shader>& shader);
    ShaderProgram& compile();

    void bind() const;
    void unbind() const;

private:
    void checkCompileErrors(uint32_t program);

private:
    uint32_t id_;
};

} // namespace wen