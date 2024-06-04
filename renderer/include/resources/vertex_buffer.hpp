#pragma once

#include "resources/vertex_layout.hpp"

namespace wen {

class VertexBuffer final {
    friend class VertexArray;

public:
    VertexBuffer(uint32_t size);
    VertexBuffer(float* vertices, uint32_t size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
    void setData(const void* data, uint32_t size);

    void setVertexLayout(const VertexLayout& layout) { layout_ = layout; }

private:
    uint32_t id_;
    VertexLayout layout_;
};

} // namespace wen