#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <iostream>
#include <cstdint>
#include <vector>

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

//chunk mesher

struct ChunkMesh {
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    int vertexCount = 0;
};

//randomGlobals

int w;
int h;

//chunk

const int ChunkSize = 32;
const float blockSize = 1;

struct Chunk
{
    uint8_t blocks[ChunkSize][ChunkSize][ChunkSize];

    int chunkX;
    int chunkY;
    int chunkZ;

    ChunkMesh mesh;
};

std::vector<Chunk> world;

//sides for drawing

constexpr int FRONT_FACE  = 0;
constexpr int BACK_FACE   = 6;
constexpr int LEFT_FACE   = 12;
constexpr int RIGHT_FACE  = 18;
constexpr int TOP_FACE    = 24;
constexpr int BOTTOM_FACE = 30;

//keyboard movement

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

//pitch clamp

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

//function initialization

void AppendFace(std::vector<float>& mesh, int faceStart, int x, int y, int z);
void GenerateChunk(Chunk& chunk);
void framebuffer_size_callback(GLFWwindow*, int w, int h);
bool IsBlockSolid(Chunk& chunk, int x, int y, int z);
void ChunkMesher(Chunk& chunk);

//main

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

    //ChunkPositions & generation

    Chunk chunk0 = {};
    chunk0.chunkX = 0;
    chunk0.chunkY = 0;
    chunk0.chunkZ = 0;

    Chunk chunk1 = {};
    chunk1.chunkX = 1;
    chunk1.chunkY = 0;
    chunk1.chunkZ = 0;

    GenerateChunk(chunk0);
    GenerateChunk(chunk1);

    ChunkMesher(chunk0);
    ChunkMesher(chunk1);

    world.push_back(chunk0);
    world.push_back(chunk1);

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

    for (Chunk& chunk : world)
    {
        std::cout
            << chunk.chunkX << ' '
            << chunk.chunkY << ' '
            << chunk.chunkZ << '\n';
    }

    std::cout << world.size() << '\n';

    // FPS setup

    double LastFrame = glfwGetTime();
    double previousTime = glfwGetTime();
    int frameCount = 0;

    //Render Loop

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Resize

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        //camera Movement

        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - LastFrame;
        LastFrame = currentFrame;

        //FPS calculation

        frameCount++;
        double currentTime = glfwGetTime();
        double elapsed = currentTime - previousTime;

        if (elapsed >= 0.25)
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

        // Rendering

        for (Chunk& chunk : world) {
            glm::mat4 model = glm::translate(glm::mat4(1.0f),
                glm::vec3(chunk.chunkX * ChunkSize,
                          chunk.chunkY * ChunkSize,
                          chunk.chunkZ * ChunkSize)
                        );

            glUniformMatrix4fv(
                ModelLocation, 
                1, 
                GL_FALSE, 
                glm::value_ptr(model)
            );

            glBindVertexArray(chunk.mesh.VAO);
            glDrawArrays(GL_TRIANGLES, 0, chunk.mesh.vertexCount);
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

//function assignment

void GenerateChunk(Chunk& chunk)
{
    for (int x = 0; x < ChunkSize; x++)
    {
        for (int y = 0; y < ChunkSize - x; y++)
        {
            for (int z = 0; z < ChunkSize - x - y; z++)
            {
                chunk.blocks[x][y][z] = 1;
            }
        }
    }
}

void framebuffer_size_callback(GLFWwindow*, int w, int h){
    glViewport(0, 0, w, h);
}
bool IsBlockSolid(Chunk& chunk, int x, int y, int z){
    if (x < 0 || x >= ChunkSize ||
        y < 0 || y >= ChunkSize ||
        z < 0 || z >= ChunkSize)
    {
        return false;
    }

    return chunk.blocks[x][y][z] != 0;
}

void AppendFace(std::vector<float>& mesh, int faceStart, int x, int y, int z){
    for (int i = 0; i < 6; i++){
        int Base = ( faceStart + i ) * 6;

        mesh.push_back(Vertices[Base + 0] + x);
        mesh.push_back(Vertices[Base + 1] + y);
        mesh.push_back(Vertices[Base + 2] + z); 

        mesh.push_back(Vertices[Base + 3]);
        mesh.push_back(Vertices[Base + 4]);
        mesh.push_back(Vertices[Base + 5]);
    }
}

void ChunkMesher(Chunk& chunk){
    std::vector<float> mesh;

    for (int x = 0; x < ChunkSize; x++){

        for (int y = 0; y < ChunkSize; y++){

            for (int z = 0; z < ChunkSize; z++){

                if (!IsBlockSolid(chunk, x, y, z)) 
                {
                    continue; 
                }

                if (!IsBlockSolid(chunk, x, y + 1, z)) AppendFace(mesh, TOP_FACE    , x, y, z);
                if (!IsBlockSolid(chunk, x, y - 1, z)) AppendFace(mesh, BOTTOM_FACE , x, y, z);
                if (!IsBlockSolid(chunk, x + 1, y, z)) AppendFace(mesh, RIGHT_FACE  , x, y, z);
                if (!IsBlockSolid(chunk, x - 1, y, z)) AppendFace(mesh, LEFT_FACE   , x, y, z);
                if (!IsBlockSolid(chunk, x, y, z + 1)) AppendFace(mesh, FRONT_FACE  , x, y, z);
                if (!IsBlockSolid(chunk, x, y, z - 1)) AppendFace(mesh, BACK_FACE   , x, y, z);

                    
            }
        }
    }

    glGenVertexArrays(1, &chunk.mesh.VAO);
    glGenBuffers(1, &chunk.mesh.VBO);

    glBindVertexArray(chunk.mesh.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, chunk.mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(float), mesh.data(), GL_STATIC_DRAW);
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

    chunk.mesh.vertexCount = mesh.size() / 6;
}