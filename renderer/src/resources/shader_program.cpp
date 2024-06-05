#include "resources/shader_program.hpp"
#include "core/log.hpp"

namespace wen {

ShaderProgram::ShaderProgram() {
    id_ = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(id_);
}

ShaderProgram& ShaderProgram::attachShader(const std::shared_ptr<Shader>& shader) {
    glAttachShader(id_, shader->shader_);
    return *this;
}

ShaderProgram& ShaderProgram::compile() {
    glLinkProgram(id_);
    checkCompileErrors(id_);
    return *this;
}

void ShaderProgram::bind() const {
    glUseProgram(id_);
}

void ShaderProgram::unbind() const {
    glUseProgram(0);
}

void ShaderProgram::checkCompileErrors(uint32_t program) {
    int success;
    char infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, nullptr, infoLog);
        WEN_ERROR("Shader program compilation failed: {0}", infoLog);
    }
}

} // namespace wen