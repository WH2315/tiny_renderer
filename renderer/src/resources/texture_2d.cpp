#include "resources/texture_2d.hpp"
#include "core/log.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace wen {

Texture2D::Texture2D(const std::string& filename) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
    width_ = width;
    height_ = height;
    GLenum internal_format = 0, data_format = 0;
    if (channels == 4) {
        internal_format = GL_RGBA8;
        data_format = GL_RGBA;
    } else if (channels == 3) {
        internal_format = GL_RGB8;
        data_format = GL_RGB;
    }
    internal_format_ = internal_format;
    data_format_ = data_format;
    glCreateTextures(GL_TEXTURE_2D, 1, &id_);
    glTextureStorage2D(id_, 1, internal_format_, width_, height_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureSubImage2D(id_, 0, 0, 0, width_, height_, data_format_, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

Texture2D::Texture2D(uint32_t width, uint32_t height) : width_(width), height_(height) {
    internal_format_ = GL_RGBA8;
    data_format_ = GL_RGBA;
    glCreateTextures(GL_TEXTURE_2D, 1, &id_);
    glTextureStorage2D(id_, 1, internal_format_, width_, height_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &id_);
}

void Texture2D::bind(uint32_t slot) const {
    glBindTextureUnit(slot, id_);
}

void Texture2D::setData(const void* data, uint32_t size) {
    uint32_t bpp = data_format_ == GL_RGBA ? 4 : 3;
    if (size != width_ * height_ * bpp) {
        WEN_ERROR("Data must be entire texture!");
        return;
    }
    glTextureSubImage2D(id_, 0, 0, 0, width_, height_, data_format_, GL_UNSIGNED_BYTE, data);
}

} // namespace wen