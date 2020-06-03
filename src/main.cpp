#include "camera/camera.h"
#include "model/model.h"

#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera;

float lastX = 0;
float lastY = 0;
bool firstMouse = true;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    camera.position = glm::vec3(0.0f, 0.0f, 3.0f);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ============================================configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // =========================================================创建着色器程序
    Shader* shader = new Shader();
    if (shader == NULL) {
        std::cout << "Failed to initialize Shader" << std::endl;
        return -1;
    }
    shader->setVertexCode("src/shader/vertex/shader1.vs")->setFragmentCode("src/shader/fragment/shader1.fs")->compile();

    // =========================================================输入顶点数据
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // ===========================================================load and create a texture 
    Texture* texture1 = new Texture("src/texture/Wallpapers/container2.png");
    texture1->minFilter = GL_LINEAR_MIPMAP_LINEAR;
    texture1->magFilter = GL_LINEAR;
    texture1->use();

    Texture* texture2 = texture1->clone()->setFilename("src/texture/Wallpapers/container2_specular.png");
    texture2->unit = 1;
    texture2->use();

    shader->use()->setUniform("material.diffuse", 0)->setUniform("material.specular", 1);

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    // positions of the point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };
    // positions all containers
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();

        // render the cube
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat3 normalModel = glm::mat3(glm::transpose(glm::inverse(model)));

        shader
            ->use()
            ->setUniform("viewPos", camera.position)
            ->setUniform("normalModel", normalModel)
            ->setUniform("material.shininess", 32.0f)
            // directional light
            ->setUniform("dirLights[0].direction", -0.2f, -1.0f, -0.3f)
            ->setUniform("dirLights[0].ambient", 0.05f, 0.05f, 0.05f)
            ->setUniform("dirLights[0].diffuse", 0.4f, 0.4f, 0.4f)
            ->setUniform("dirLights[0].specular", 0.5f, 0.5f, 0.5f)
            // point light 1
            ->setUniform("pointLights[0].position", pointLightPositions[0])
            ->setUniform("pointLights[0].ambient", 0.05f, 0.05f, 0.05f)
            ->setUniform("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f)
            ->setUniform("pointLights[0].specular", 1.0f, 1.0f, 1.0f)
            ->setUniform("pointLights[0].constant", 1.0f)
            ->setUniform("pointLights[0].linear", 0.09f)
            ->setUniform("pointLights[0].quadratic", 0.032f)
            // point light 2
            ->setUniform("pointLights[1].position", pointLightPositions[1])
            ->setUniform("pointLights[1].ambient", 0.05f, 0.05f, 0.05f)
            ->setUniform("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f)
            ->setUniform("pointLights[1].specular", 1.0f, 1.0f, 1.0f)
            ->setUniform("pointLights[1].constant", 1.0f)
            ->setUniform("pointLights[1].linear", 0.09f)
            ->setUniform("pointLights[1].quadratic", 0.032f)
            // point light 3
            ->setUniform("pointLights[2].position", pointLightPositions[2])
            ->setUniform("pointLights[2].ambient", 0.05f, 0.05f, 0.05f)
            ->setUniform("pointLights[2].specular", 1.0f, 1.0f, 1.0f)
            ->setUniform("pointLights[2].constant", 1.0f)
            ->setUniform("pointLights[2].linear", 0.09f)
            ->setUniform("pointLights[2].quadratic", 0.032f)
            // point light 4
            ->setUniform("pointLights[3].position", pointLightPositions[3])
            ->setUniform("pointLights[3].ambient", 0.05f, 0.05f, 0.05f)
            ->setUniform("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f)
            ->setUniform("pointLights[3].specular", 1.0f, 1.0f, 1.0f)
            ->setUniform("pointLights[3].constant", 1.0f)
            ->setUniform("pointLights[3].linear", 0.09f)
            ->setUniform("pointLights[3].quadratic", 0.032f)
            // spotLight
            ->setUniform("spotLights[0].position", camera.position)
            ->setUniform("spotLights[0].direction", camera.front)
            ->setUniform("spotLights[0].ambient", 0.0f, 0.0f, 0.0f)
            ->setUniform("spotLights[0].diffuse", 1.0f, 1.0f, 1.0f)
            ->setUniform("spotLights[0].specular", 1.0f, 1.0f, 1.0f)
            ->setUniform("spotLights[0].constant", 1.0f)
            ->setUniform("spotLights[0].linear", 0.09f)
            ->setUniform("spotLights[0].quadratic", 0.032f)
            ->setUniform("spotLights[0].innerCutOff", glm::cos(glm::radians(12.5f)))
            ->setUniform("spotLights[0].outerCutOff", glm::cos(glm::radians(15.0f)))
            ->setUniform("lightCount[0]", 1)
            ->setUniform("lightCount[1]", 4)
            ->setUniform("lightCount[2]", 1)
            ->setUniform("view", view)
            ->setUniform("projection", projection);
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader->setUniform("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    delete shader;
    shader = NULL;
    delete texture1;
    texture1 = NULL;
    delete texture2;
    texture2 = NULL;

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll(yoffset);
}
