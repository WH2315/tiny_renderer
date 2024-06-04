#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

namespace wen {

struct WindowInfo {
    std::string title;
    uint32_t width, height;
};

class Window final {
public:
    struct Data {
        std::string title;
        uint32_t width, height;
    };

public:
    Window(const WindowInfo& info);
    ~Window();

    void pollEvents() const;
    bool shouldClose() const;

    void* getWindow() const { return window_; }
    Data getData() const { return data_; }

private:
    GLFWwindow* window_;
    Data data_;
};

extern std::unique_ptr<Window> g_window;

} // namespace wen