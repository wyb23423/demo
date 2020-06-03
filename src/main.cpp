#include "camera/camera.h"
#include "model/model.h"

#include <GLFW/glfw3.h>
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
    shader->setVertexCode("src/shader/vertex/shader1.vs")->setFragmentCode("src/shader/fragment/shader3.fs")->compile();

    // =========================================================
    vector<Mesh*>* meshes = loadModel("src/model/obj/nanosuit/nanosuit.obj");

    // positions of the point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();
        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));	// it's a bit too big for our scene, so scale it down

        glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));

        shader
            ->use()
            ->setUniform("viewPos", camera.position)
            ->setUniform("normalMatrix", normalMatrix)
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
            ->setUniform("view", view)
            ->setUniform("projection", projection)
            ->setUniform("model", model);
        paintModel(meshes, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    delete shader;
    shader = NULL;

    clearModelCache();
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
