#pragma once

#include "enums.hpp"
#include <glad/glad.h>
#include <string>
#include <vector>

namespace wen {

static GLenum type_to_gltype(VertexType type) {
    switch (type) {
        case VertexType::eFloat:
        case VertexType::eFloat2:
        case VertexType::eFloat3:
        case VertexType::eFloat4:  return GL_FLOAT;
        case VertexType::eInt:
        case VertexType::eInt2:
        case VertexType::eInt3:
        case VertexType::eInt4:    return GL_INT;
        case VertexType::eBool:    return GL_BOOL;
        default:                   return GL_NONE;
    }
}

static uint32_t type_to_size(VertexType type) {
    switch (type) {
        case VertexType::eFloat:   return 4 * 1;
        case VertexType::eFloat2:  return 4 * 2;
        case VertexType::eFloat3:  return 4 * 3;
        case VertexType::eFloat4:  return 4 * 4;
        case VertexType::eInt:     return 4 * 1;
        case VertexType::eInt2:    return 4 * 2;
        case VertexType::eInt3:    return 4 * 3;
        case VertexType::eInt4:    return 4 * 4;
        case VertexType::eBool:    return 1;
        default:                   return 0;
    }
}

struct VertexElement {
    std::string name;
    GLenum type;
    uint32_t size;
    uint32_t offset;
    bool normalized;

    VertexElement(const std::string& name, VertexType type, bool normalized = false)
        : name(name),
          type(type_to_gltype(type)),
          size(type_to_size(type)),
          offset(0),
          normalized(normalized){};
};

class VertexLayout {
    friend class VertexArray;

public:
    VertexLayout() = default;

    VertexLayout(const std::initializer_list<VertexElement>& elements) : elements_(elements) {
        for (auto& element : elements_) {
            element.offset = stride_;
            stride_ += element.size;
        }
    }

    std::vector<VertexElement>::iterator begin() { return elements_.begin(); }
    std::vector<VertexElement>::iterator end() { return elements_.end(); }
    std::vector<VertexElement>::const_iterator begin() const { return elements_.begin(); }
    std::vector<VertexElement>::const_iterator end() const { return elements_.end(); }

private:
    std::vector<VertexElement> elements_;
    uint32_t stride_ = 0;
};

} // namespace wen