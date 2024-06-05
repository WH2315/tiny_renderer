#include "resources/shader.hpp"
#include "utils/utils.hpp"
#include "core/log.hpp"

namespace wen {

namespace inner {

static GLenum getShaderType(ShaderStage type) {
    switch (type) {
        case ShaderStage::eVertex:
            return GL_VERTEX_SHADER;
        case ShaderStage::eFragment:
            return GL_FRAGMENT_SHADER;
    }
}

} // namespace inner

Shader::Shader(const std::string& filename, ShaderStage stage) {
    auto shader_type = inner::getShaderType(stage);
    shader_ = glCreateShader(shader_type);
    auto source = readFile(filename);
    const char* src = source.c_str();
    glShaderSource(shader_, 1, &src, nullptr);
    glCompileShader(shader_);
    checkCompileErrors(shader_);
}

Shader::~Shader() {
    glDeleteShader(shader_);
}

void Shader::checkCompileErrors(uint32_t shader) {
    int success;
    char infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        WEN_ERROR("Shader compilation failed: {0}", infoLog);
    }
}

} // namespace wen