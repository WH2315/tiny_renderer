#pragma once

#include <cstdint>

namespace wen {

class IndexBuffer final {
    friend class VertexArray;

public:
    IndexBuffer(uint32_t* indices, uint32_t count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

private:
    uint32_t id_;
    uint32_t count_;
};

} // namespace wen