#pragma once

#include "resources/shader_program.hpp"
#include "resources/vertex_array.hpp"

namespace wen {

class Renderer final {
public:
    Renderer();
    ~Renderer();

public:
    void setClearColor(float r, float g, float b, float a) const;
    void clear() const;
    void submit(const std::shared_ptr<ShaderProgram>& program,
                const std::shared_ptr<VertexArray>& VAO) const;
    void draw() const;
    void drawIndexed() const;
};

} // namespace wen