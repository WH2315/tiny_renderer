#pragma once

#include "resources/vertex_buffer.hpp"
#include "resources/index_buffer.hpp"
#include <memory>

namespace wen {

class VertexArray final {
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void attachVertexBuffer(const std::shared_ptr<VertexBuffer>& VBO);
    void attachIndexBuffer(const std::shared_ptr<IndexBuffer>& EBO);

    uint32_t getIndexCount() const { return index_count_; }

private:
    uint32_t id_;
    uint32_t index_count_;
};

} // namespace wen