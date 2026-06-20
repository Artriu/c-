#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <iostream>
#include <cstdint>

uint8_t Cubeing[4][4][4] =
{
    {
        {1, 1, 1, 1},
        {1, 0, 0, 1},
        {1, 0, 1, 1},
        {1, 1, 1, 1}
    },

    {
        {1, 1, 1, 1},
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {1, 1, 1, 1}
    },

    {
        {1, 1, 1, 1},
        {1, 1, 0, 1},
        {1, 0, 0, 1},
        {1, 1, 1, 1}
    },

    {
        {1, 1, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 1}
    }
};

const char* VertexShaderSource = R"(
    #version 330 core

    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;

    out vec3 ourColor;

    uniform mat4 uModel;
    uniform mat4 uView;
    uniform mat4 uProjection;

    void main()
    {
        gl_Position =
            uProjection *
            uView *
            uModel *
            vec4(aPos, 1.0);
        
        ourColor = aColor;
    }
)";

const char* FragmentShaderSource = R"(
    #version 330 core

    in vec3 ourColor;
    out vec4 FragColour;

    void main()
    {
        FragColour = vec4(ourColor, 1.0);
    }
)";

unsigned int CompileShaders()
{
    unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &VertexShaderSource,nullptr);
    glCompileShader(VertexShader);

    int success;
    char log[512];

    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(VertexShader, 512, nullptr, log);
        std::cerr << "VERTEX SHADER ERROR : " <<  log;
    }

    unsigned int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &FragmentShaderSource,nullptr);
    glCompileShader(FragmentShader);

    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(FragmentShader, 512, nullptr, log);
        std::cerr << "Fragment SHADER ERROR : " <<  log;
    }

    unsigned int Program = glCreateProgram();
    glAttachShader(Program, VertexShader);
    glAttachShader(Program, FragmentShader);
    glLinkProgram(Program);

    glGetProgramiv(Program, GL_LINK_STATUS, &success);
    if(! success)
    {
        glGetProgramInfoLog(Program, 512, nullptr, log);
        std::cerr << "Program Link Error : " << log;
    }

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    return Program;
}

float Vertices[] =
{
    // Front - Red
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

    // Back - Green
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

     0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

    // Left - Blue
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

    // Right - Yellow
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,

     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,

    // Top - Magenta
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,

     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f,

    // Bottom - Cyan
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,

     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f
};

//keyboard movement

const int ChunkSize = 4;
const float blockSize = 1;

glm::vec3 cameraPos( 0.0f, 3.0f, 3.0f);
float cameraSpeed = 5.0f;

//mouse movement

glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

float yaw = -90.0f;
float pitch = 0.0f;

float lastX = 400.0f;
float lastY = 400.0f;

bool firstMouse = true;

float sensitivity = 0.05f;

//Keyboard movement

void ProcessInput(GLFWwindow* window, float deltaTime)
{
    float speed = cameraSpeed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraFront * speed;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraFront * speed;
    
    glm::vec3 right = glm::normalize(
        glm::cross(cameraFront, cameraUp)
    );

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= right * speed;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += right * speed;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPos.y += speed;
    
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraPos.y -= speed;
}

//pitch clamp, i currently do not understand

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;

    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraFront = glm::normalize(direction);
}

int main()
{
    if (!glfwInit())
    {
        std::cout << "GLFW init failed\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(
        1920,
        1080,
        "Project : BADMINECRAFT",
        NULL,
        NULL
    );

    if (!window)
    {
        std::cout << "Window creation failed\n";
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwMakeContextCurrent(window);

    //glfwSwapInterval(1);
    //glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    std::cout << width << " x " << height << '\n';

    glViewport(0, 0, width, height);

    unsigned int shaderProgram = CompileShaders();

    std::cout << "Program ID: "
          << shaderProgram
          << '\n';

    //VAO and VBO setup

    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    //send to the GPU

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    int ModelLocation = glGetUniformLocation(
        shaderProgram,
        "uModel"
    );

    int ViewLocation = glGetUniformLocation(
        shaderProgram,
        "uView"
    );

    int ProjectionLocation = glGetUniformLocation(
        shaderProgram,
        "uProjection"
    );

    // FPS setup

    double LastFrame = glfwGetTime();
    double previousTime = glfwGetTime();
    int frameCount = 0;

    //Render Loop

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //camera Movement

        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - LastFrame;
        LastFrame = currentFrame;

        //FPS calculation

        frameCount++;
        double currentTime = glfwGetTime();
        double elapsed = currentTime - previousTime;

        if (elapsed >= 1.0)
        {
            double fps = frameCount / elapsed;

            std::string title = "Bad Minecraft - ";
            title.append(std::to_string((int)fps));
            glfwSetWindowTitle(window, title.c_str());
        
            frameCount = 0;
            previousTime = currentTime;
        }

        //end

        ProcessInput(window, deltaTime);

        glUseProgram(shaderProgram);

        //View stuff

        glm::mat4 view = glm::lookAt(
            cameraPos,
            cameraPos + cameraFront,
            cameraUp
        );

        //perspective

        glm::mat4 projection = glm::perspective(
            glm::radians(90.0f), // this is the FOV
            (float)width / (float)height,
            0.1f,
            100.0f
        );

        //sending the View and perspective to the shader

        glUniformMatrix4fv(
            ViewLocation,
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );

        glUniformMatrix4fv(
            ProjectionLocation,
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );

        // Rotation

        glBindVertexArray(VAO);

        for(int x = 0; x < sizeof(Cubeing) / sizeof(Cubeing[0]); x++){

            for(int y = 0; y < sizeof(Cubeing[0][0]) / sizeof(Cubeing[0][0][0]); y++){

                for(int z = 0; z < sizeof(Cubeing[0][0]) / sizeof(Cubeing[0][0][0]); z++){

                    if(Cubeing[x][y][z] == 0){ //cheak for air
                       continue;
                    }
                    
                    glm::mat4 model = glm::mat4(1.0f);

                    model = glm::translate(
                        model,
                        glm::vec3(
                            (x - ChunkSize / 2.0f) * blockSize,
                            (y - ChunkSize / 2.0f) * blockSize,
                            -z * blockSize
                        )
                    );

                    model = glm::scale(
                        model,
                        glm::vec3(blockSize)
                    );

                    glUniformMatrix4fv(
                        ModelLocation,
                        1,
                        GL_FALSE,
                        glm::value_ptr(model)
                    );

                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
            }
        }

        //error stuff

        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
            std::cerr << "GL ERROR: " << err << "\n";

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}