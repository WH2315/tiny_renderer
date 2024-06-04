#pragma once

#include "enums.hpp"
#include <glad/glad.h>
#include <cstdint>
#include <string>

namespace wen {

class Shader final {
    friend class ShaderProgram;

public:
    Shader(const std::string& filename, ShaderStage stage);
    ~Shader();

private:
    void checkCompileErrors(uint32_t shader);

private:
    uint32_t shader_;
};

} // namespace wen