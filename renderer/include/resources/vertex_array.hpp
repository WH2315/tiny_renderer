#pragma once

#include "resources/vertex_buffer.hpp"
#include <memory>

namespace wen {

class VertexArray final {
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void attachVertexBuffer(const std::shared_ptr<VertexBuffer>& VBO);

private:
    uint32_t id_;
};

} // namespace wen