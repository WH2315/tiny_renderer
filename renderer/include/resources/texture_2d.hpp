#pragma once

#include <string>
#include <glad/glad.h>

namespace wen {

class Texture2D final {
public:
    Texture2D(const std::string& filename);
    Texture2D(uint32_t width, uint32_t height);
    ~Texture2D();

    void bind(uint32_t slot = 0) const;
    void setData(const void* data, uint32_t size);

    uint32_t getID() const { return id_; }

private:
    uint32_t id_;
    uint32_t width_, height_;
    GLint internal_format_ = 0;
    GLenum data_format_ = 0;
};

} // namespace wen