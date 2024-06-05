#include "wen.hpp"

int main() {
    auto manager = new wen::Manager;
    manager->initializeEngine();

    auto interface = manager->initializeRenderer("./sandbox/resources");

    auto vert = interface->createShader("vert.glsl", wen::ShaderStage::eVertex);
    auto frag = interface->createShader("frag.glsl", wen::ShaderStage::eFragment);
    auto program = interface->createShaderProgram(); 
    float offset = 0.3f;
    program->attachShader(vert)
            .attachShader(frag)
            .compile()
            .setFloat("xOffset", offset);

    float vertices[] = {
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };
    uint32_t indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    auto VAO = interface->createVertexArray(); 
    auto VBO = interface->createVertexBuffer(vertices, sizeof(vertices));
    auto EBO = interface->createIndexBuffer(indices, sizeof(indices) / sizeof(uint32_t));
    VBO->setVertexLayout({
        {"positon", wen::VertexType::eFloat3, false},
        {"color", wen::VertexType::eFloat3, false},
        {"uv", wen::VertexType::eFloat2, false}
    });
    VAO->attachVertexBuffer(VBO);
    VAO->attachIndexBuffer(EBO);

    auto texture1 = interface->createTexture2D("container.jpg");
    auto texture2 = interface->createTexture2D("awesomeface.png");
    program->setInt("texture1", 0)
            .setInt("texture2", 1);

    auto renderer = interface->createRenderer();

    while (!manager->shouldClose()) {
        manager->pollEvents();

        renderer->setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        renderer->clear();
        renderer->bindTexture2D(texture1, 0);
        renderer->bindTexture2D(texture2, 1);
        renderer->bindShaderProgram(program);
        renderer->bindVertexArray(VAO);
        renderer->drawIndexed(VAO->getIndexCount());
    }

    manager->destroyRenderer();

    manager->destroyEngine();

    return 0;
}