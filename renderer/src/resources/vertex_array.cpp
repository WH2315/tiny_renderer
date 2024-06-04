#include "resources/vertex_array.hpp"
#include "core/log.hpp"

namespace wen {

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id_);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id_);
}

void VertexArray::bind() const {
    glBindVertexArray(id_);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::attachVertexBuffer(const std::shared_ptr<VertexBuffer>& VBO) {
    if (VBO->layout_.elements_.size() == 0) {
        WEN_ERROR("you don't set layout for vertex buffer!")
    }

    this->bind();
    VBO->bind();

    uint32_t index = 0;
    const auto& layout = VBO->layout_;
    for (const auto& element : layout) {
        switch (element.type) {
            case GL_FLOAT: {
                glVertexAttribPointer(
                    index,
                    element.size / 4,
                    element.type,
                    element.normalized ? GL_TRUE : GL_FALSE,
                    layout.stride_,
                    reinterpret_cast<const void*>(element.offset)
                );
                break;
            }
            case GL_INT: {
                glVertexAttribIPointer(
                    index,
                    element.size / 4,
                    element.type,
                    layout.stride_,
                    reinterpret_cast<const void*>(element.offset)
                );
                break;
            }
            case GL_BOOL: {
                glVertexAttribIPointer(
                    index,
                    element.size,
                    element.type,
                    layout.stride_,
                    reinterpret_cast<const void*>(element.offset)
                );
                break;
            }
            default: {
                WEN_ERROR("unknown vertex type!")
                break;
            }
        }
        glEnableVertexAttribArray(index);
        index++;
    }
}

} // namespace wen