#include "manager.hpp"
#include "core/log.hpp"
#include "base/window.hpp"

namespace wen {

void Manager::initializeEngine() {
    g_log = new Log("wen");
}

std::shared_ptr<Interface> Manager::initializeRenderer(const std::string& path) {
    g_window = std::make_unique<Window>(WindowInfo{"wen", 1600, 900});
    return std::make_shared<Interface>(path);
}

bool Manager::shouldClose() {
    return g_window->shouldClose();
}

void Manager::pollEvents() {
    g_window->pollEvents();
}

void Manager::destroyRenderer() {
    g_window.reset();
}

void Manager::destroyEngine() {
    g_log = nullptr;
    delete g_log;
}

} // namespace wen