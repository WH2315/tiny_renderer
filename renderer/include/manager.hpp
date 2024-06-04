#pragma once

#include "interface.hpp"

namespace wen {

struct Manager {
    void initializeEngine();
    std::shared_ptr<Interface> initializeRenderer(const std::string& path);
    bool shouldClose();
    void pollEvents();
    void destroyRenderer();
    void destroyEngine();
};

} // namespace wen