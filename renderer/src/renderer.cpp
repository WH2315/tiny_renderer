#include "renderer.hpp"

namespace wen {

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::setClearColor(float r, float g, float b, float a) const {
    glClearColor(r, g, b, a);
}

void Renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::bindTexture2D(const std::shared_ptr<Texture2D>& texture, uint32_t slot) const {
    texture->bind(slot);
}

void Renderer::bindShaderProgram(const std::shared_ptr<ShaderProgram>& shader_program) const {
    shader_program->bind();
}

void Renderer::bindVertexArray(const std::shared_ptr<VertexArray>& vertex_array) const {
    vertex_array->bind();
}

void Renderer::draw() const {
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::drawIndexed(uint32_t count) const {
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

} // namespace wen