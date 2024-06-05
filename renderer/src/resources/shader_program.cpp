#include "resources/shader_program.hpp"
#include "core/log.hpp"
#include <glm/gtc/type_ptr.hpp>

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
    this->bind();
    return *this;
}

void ShaderProgram::bind() const {
    glUseProgram(id_);
}

void ShaderProgram::unbind() const {
    glUseProgram(0);
}

ShaderProgram& ShaderProgram::setBool(const std::string& name, bool value) {
    glUniform1i(glGetUniformLocation(id_, name.c_str()), static_cast<int>(value));
    return *this;
}

ShaderProgram& ShaderProgram::setInt(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
    return *this;
}

ShaderProgram& ShaderProgram::setIntArray(const std::string& name, int* values, uint32_t count) {
    glUniform1iv(glGetUniformLocation(id_, name.c_str()), count, values);
    return *this;
}

ShaderProgram& ShaderProgram::setFloat(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
    return *this;
}

ShaderProgram& ShaderProgram::setVec2(const std::string& name, const glm::vec2& value) {
    glUniform2f(glGetUniformLocation(id_, name.c_str()), value.x, value.y);
    return *this;
}

ShaderProgram& ShaderProgram::setVec3(const std::string& name, const glm::vec3& value) {
    glUniform3f(glGetUniformLocation(id_, name.c_str()), value.x, value.y, value.z);
    return *this;
}

ShaderProgram& ShaderProgram::setVec4(const std::string& name, const glm::vec4& value) {
    glUniform4f(glGetUniformLocation(id_, name.c_str()), value.x, value.y, value.z, value.w);
    return *this;
}

ShaderProgram& ShaderProgram::setMat2(const std::string& name, const glm::mat2& value) {
    glUniformMatrix2fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    return *this;
}

ShaderProgram& ShaderProgram::setMat3(const std::string& name, const glm::mat3& value) {
    glUniformMatrix3fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    return *this;
}

ShaderProgram& ShaderProgram::setMat4(const std::string& name, const glm::mat4& value) {
    glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    return *this;
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