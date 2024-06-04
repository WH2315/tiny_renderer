#include "base/window.hpp"
#include "core/log.hpp"

namespace wen {

std::unique_ptr<Window> g_window = nullptr;

Window::Window(const WindowInfo& info) {
    data_.title = info.title;
    data_.width = info.width;
    data_.height = info.height;
    WEN_INFO("Create window:({0}, {1}, {2})", info.title, info.width, info.height)

    // glfw: initialize and configure
    if (!glfwInit()) {
        WEN_ERROR("Failed to init glfw!")
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    window_ = glfwCreateWindow(info.width, info.height, info.title.c_str(), nullptr, nullptr);
    if (!window_) {
        WEN_ERROR("Failed to create GLFW window!")
        glfwTerminate();
    }
    glfwMakeContextCurrent(window_);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        WEN_ERROR("Failed to init glad!")
    }

    WEN_INFO("OpenGL Info:");
    WEN_INFO("\tVendor: {0}", (char*)glGetString(GL_VENDOR));
    WEN_INFO("\tRenderer: {0}", (char*)glGetString(GL_RENDERER));
    WEN_INFO("\tVersion: {0}", (char*)glGetString(GL_VERSION));

    glfwSetWindowUserPointer(window_, &data_);
    glfwSwapInterval(1);

    glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
        Data& data = *(Data*)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;
        glViewport(0, 0, width, height);
    });

    glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
        Data& data = *(Data*)glfwGetWindowUserPointer(window);
    });
}

void Window::pollEvents() const {
    glfwPollEvents();
    glfwSwapBuffers(window_);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window_);
}

Window::~Window() {
    glfwDestroyWindow(window_);
    window_ = nullptr;
    glfwTerminate();
}

} // namespace wen