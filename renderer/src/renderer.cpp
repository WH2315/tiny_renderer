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

void Renderer::submit(const std::shared_ptr<ShaderProgram>& program,
                      const std::shared_ptr<VertexArray>& VAO) const {
    program->bind();
    VAO->bind();
}

void Renderer::draw() const {
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::drawIndexed() const {}

} // namespace wen