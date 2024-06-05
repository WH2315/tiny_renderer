#pragma once

#include "resources/shader_program.hpp"
#include "resources/vertex_array.hpp"
#include "resources/texture_2d.hpp"

namespace wen {

class Renderer final {
public:
    Renderer();
    ~Renderer();

public:
    void setClearColor(float r, float g, float b, float a) const;
    void clear() const;
    void bindTexture2D(const std::shared_ptr<Texture2D>& texture, uint32_t slot = 0) const;
    void bindShaderProgram(const std::shared_ptr<ShaderProgram>& shader_program) const;
    void bindVertexArray(const std::shared_ptr<VertexArray>& vertex_array) const;
    void draw() const;
    void drawIndexed(uint32_t index_count) const;
};

} // namespace wen