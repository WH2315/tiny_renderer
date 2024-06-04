#include "wen.hpp"

int main() {
    auto manager = new wen::Manager;
    manager->initializeEngine();

    auto interface = manager->initializeRenderer("./sandbox/resources");

    auto vert = interface->createShader("vert.glsl", wen::ShaderStage::eVertex);
    auto frag = interface->createShader("frag.glsl", wen::ShaderStage::eFragment);
    auto program = interface->createShaderProgram(); 
    program->attachShader(vert)
            .attachShader(frag)
            .compile();

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f,  -0.5f, 0.0f, // right
        0.0f,  0.5f,  0.0f  // top
    };

    auto VAO = interface->createVertexArray(); 
    auto VBO = interface->createVertexBuffer(vertices, sizeof(vertices));
    VBO->setVertexLayout({
        {"positon", wen::VertexType::eFloat3, false}
    });
    VAO->attachVertexBuffer(VBO);

    auto renderer = interface->createRenderer();

    while (!manager->shouldClose()) {
        manager->pollEvents();

        renderer->setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        renderer->clear();
        renderer->submit(program, VAO);
        renderer->draw();
    }

    manager->destroyRenderer();

    manager->destroyEngine();

    return 0;
}