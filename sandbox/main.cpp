#include "wen.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    auto VAO = interface->createVertexArray(); 
    auto VBO = interface->createVertexBuffer(vertices, sizeof(vertices));
    VBO->setVertexLayout({
        {"positon", wen::VertexType::eFloat3, false},
        {"uv", wen::VertexType::eFloat2, false}
    });
    VAO->attachVertexBuffer(VBO);

    auto texture1 = interface->createTexture2D("container.jpg");
    auto texture2 = interface->createTexture2D("awesomeface.png");
    program->setInt("texture1", 0)
            .setInt("texture2", 1);

    auto camera = new wen::Camera();
    auto renderer = interface->createRenderer();

    while (!manager->shouldClose()) {
        manager->pollEvents();

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        camera->update(deltaTime);

        renderer->setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        renderer->clear();
        renderer->bindTexture2D(texture1, 0);
        renderer->bindTexture2D(texture2, 1);
        renderer->bindShaderProgram(program);
        renderer->bindVertexArray(VAO);

        glm::mat4 model = glm::mat4(1.0f);
        float angle = currentFrame * 30.0f;;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        program->setMat4("model", model);
        program->setMat4("view", camera->data.view);
        program->setMat4("project", camera->data.project);

        renderer->draw(36);
    }

    manager->destroyRenderer();

    manager->destroyEngine();

    return 0;
}