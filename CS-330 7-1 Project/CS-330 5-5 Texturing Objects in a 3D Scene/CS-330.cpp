#include <iostream>         // cout, cerr
#include <cstdlib>          // EXIT_FAILURE
#include <GL/glew.h>        // GLEW library
#include <GLFW/glfw3.h>     // GLFW library

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "camera.h" // Camera class

using namespace std; // Standard namespace

/*Shader program Macro*/
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif

// Unnamed namespace
namespace
{
    const char* const WINDOW_TITLE = "CS-330 7-1 Project by Andrew Black"; // Macro for window title

    // Variables for window width and height
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

    // Stores the GL data relative to a given mesh
    struct GLMesh
    {
        GLuint vao;         // Handle for the vertex array object
        GLuint vbos[2];     // Handles for the vertex buffer objects
        GLuint nIndices;    // Number of indices of the mesh
    };

    // Main GLFW window
    GLFWwindow* gWindow = nullptr;
    GLuint gTextureIdFence;
    GLuint gTextureIdGround;
    GLuint gTextureIdBrick;
    GLuint gTextureIdRoof;
    GLuint gTextureIdLog;
    // Triangle mesh data
    GLMesh gMeshGround;
    GLMesh gMeshFences;
    GLMesh gMeshHouseWalls;
    GLMesh gMeshHouseRoof;
    GLMesh gMeshMailbox;
    // UV scale
    glm::vec2 gUVScale(3.0f, 1.0f);
    // Shader program
    GLuint gProgramId;

    // camera
    Camera gCamera(glm::vec3(0.0f, 6.0f, 25.0f));
    float gLastX = WINDOW_WIDTH / 2.0f;
    float gLastY = WINDOW_HEIGHT / 2.0f;
    bool gFirstMouse = true;
    bool gUseOrthoProjection = false;

    // timing
    float gDeltaTime = 0.0f; // time between current frame and last frame
    float gLastFrame = 0.0f;

    // Subject position and scale
    glm::vec3 gObjectPosition(0.0f, 0.0f, 0.0f);
    glm::vec3 gObjectScale(2.0f);

    // Pyramid and light color
    glm::vec3 gLightColor(1.0f, 1.0f, 0.8f);

    // Light position
    glm::vec3 gLightPosition(5.0f, 5.0f, 5.0f);

        // Alphabet mapped to numbers to assist with drawing
    const GLushort A = 0;
    const GLushort B = 1;
    const GLushort C = 2;
    const GLushort D = 3;
    const GLushort E = 4;
    const GLushort F = 5;
    const GLushort G = 6;
    const GLushort H = 7;
    const GLushort I = 8;
    const GLushort J = 9;
    const GLushort K = 10;
    const GLushort L = 11;
    const GLushort M = 12;
    const GLushort N = 13;
    const GLushort O = 14;
    const GLushort P = 15;
    const GLushort Q = 16;
    const GLushort R = 17;
    const GLushort S = 18;
    const GLushort T = 19;
    const GLushort U = 20;
    const GLushort V = 21;
    const GLushort W = 22;
    const GLushort X = 23;
    const GLushort Y = 24;
    const GLushort Z = 25;
    const GLushort AA = 26;
    const GLushort AB = 27;
    const GLushort AC = 28;
    const GLushort AD = 29;
    const GLushort AE = 30;
    const GLushort AF = 31;
    const GLushort AG = 32;
    const GLushort AH = 33;
    const GLushort AI = 34;
    const GLushort AJ = 35;
    const GLushort AK = 36;
    const GLushort AL = 37;
    const GLushort AM = 38;
    const GLushort AN = 39;
    const GLushort AO = 40;
    const GLushort AP = 41;
    const GLushort AQ = 42;
    const GLushort AR = 43;
    const GLushort AS = 44;
    const GLushort AT = 45;
    const GLushort AU = 46;
    const GLushort AV = 47;
    const GLushort AW = 48;
    const GLushort AX = 49;
    const GLushort AY = 50;
    const GLushort AZ = 51;
}

/* User-defined Function prototypes to:
 * initialize the program, set the window size,
 * redraw graphics on the window when resized,
 * and render graphics on the screen
 */
bool UInitialize(int, char* [], GLFWwindow** window);
void UResizeWindow(GLFWwindow* window, int width, int height);
void UProcessInput(GLFWwindow* window);
void UKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
bool UCreateTexture(const char* filename, GLuint& textureId);
void UDestroyTexture(GLuint textureId);
void UCreateMeshGround(GLMesh& mesh);
void UCreateMeshFences(GLMesh& mesh);
void UCreateMeshHouseWalls(GLMesh& mesh);
void UCreateMeshHouseRoof(GLMesh& mesh);
void UCreateMeshMailbox(GLMesh& mesh);
void UDestroyMesh(GLMesh& mesh);
void URender();
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId);
void UDestroyShaderProgram(GLuint programId);


/* Vertex Shader Source Code*/
const GLchar* vertexShaderSource = GLSL(410,
    layout(location = 0) in vec3 position; // VAP position 0 for vertex position data
    layout(location = 1) in vec3 normal; // VAP position 1 for normals
    layout(location = 2) in vec2 textureCoordinate;

    out vec3 vertexNormal; // For outgoing normals to fragment shader
    out vec3 vertexFragmentPos; // For outgoing color / pixels to fragment shader
    out vec2 vertexTextureCoordinate;

    //Uniform / Global variables for the  transform matrices
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(position, 1.0f); // Transforms vertices into clip coordinates

        vertexFragmentPos = vec3(model * vec4(position, 1.0f)); // Gets fragment / pixel position in world space only (exclude view and projection)

        vertexNormal = mat3(transpose(inverse(model))) * normal; // get normal vectors in world space only and exclude normal translation properties
        vertexTextureCoordinate = textureCoordinate;
    }
);


/* Fragment Shader Source Code*/
const GLchar* fragmentShaderSource = GLSL(410,
    in vec3 vertexNormal; // For incoming normals
    in vec3 vertexFragmentPos; // For incoming fragment position
    in vec2 vertexTextureCoordinate;

    out vec4 fragmentColor; // For outgoing pyramid color to the GPU

    // Uniform / Global variables for object color, light color, light position, and camera/view position
    uniform vec3 lightColor;
    uniform vec3 lightPos;
    uniform vec3 viewPosition;
    uniform sampler2D uTexture; // Useful when working with multiple textures
    uniform vec2 uvScale;

    void main()
    {
        // Phong lighting model calculations to generate ambient, diffuse, and specular components

        // Calculate Ambient lighting
        float ambientStrength = 0.1f; // Set ambient or global lighting strength
        vec3 ambient = ambientStrength * lightColor; // Generate ambient light color

        // Calculate Diffuse lighting
        vec3 norm = normalize(vertexNormal); // Normalize vectors to 1 unit
        vec3 lightDirection = normalize(lightPos - vertexFragmentPos); // Calculate distance (light direction) between light source and fragments/pixels on pyramid
        float impact = max(dot(norm, lightDirection), 0.0);// Calculate diffuse impact by generating dot product of normal and light
        vec3 diffuse = impact * lightColor; // Generate diffuse light color

        // Calculate Specular lighting
        float specularIntensity = 0.0f; // Set specular light strength -- in combo with next option, how "metallic" it might appear
        float highlightSize = 16.0f; // Set specular highlight size
        vec3 viewDir = normalize(viewPosition - vertexFragmentPos); // Calculate view direction
        vec3 reflectDir = reflect(-lightDirection, norm); // Calculate reflection vector
        // Calculate specular component
        float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
        vec3 specular = specularIntensity * specularComponent * lightColor;

        // Texture holds the color to be used for all three components
        vec4 textureColor = texture(uTexture, vertexTextureCoordinate * uvScale);

        // Calculate phong result
        vec3 phong = (ambient + diffuse + specular) * textureColor.xyz;

        // Final
        // --------------------------------

        fragmentColor = vec4(phong, 1.0); // Send lighting results to GPU
    }
);


int main(int argc, char* argv[])
{
    if (!UInitialize(argc, argv, &gWindow))
        return EXIT_FAILURE;

    // Create the mesh
    UCreateMeshGround(gMeshGround); // Calls the function to create the Vertex Buffer Object
    UCreateMeshFences(gMeshFences);
    UCreateMeshHouseWalls(gMeshHouseWalls);
    UCreateMeshHouseRoof(gMeshHouseRoof);
    UCreateMeshMailbox(gMeshMailbox);

    // Create the shader program
    if (!UCreateShaderProgram(vertexShaderSource, fragmentShaderSource, gProgramId))
        return EXIT_FAILURE;

    // Load ground texture
    const char* texFilename = "grass.jpg";
    if (!UCreateTexture(texFilename, gTextureIdGround))
    {
        cout << "Failed to load texture " << texFilename << endl;
        return EXIT_FAILURE;
    }
    // Load fence texture
    texFilename = "fence.jpg";
    if (!UCreateTexture(texFilename, gTextureIdFence))
    {
        cout << "Failed to load texture " << texFilename << endl;
        return EXIT_FAILURE;
    }
    // Load brick texture
    texFilename = "brick.jpg";
    if (!UCreateTexture(texFilename, gTextureIdBrick))
    {
        cout << "Failed to load texture " << texFilename << endl;
        return EXIT_FAILURE;
    }
    // Load roof texture
    texFilename = "roof.jpg";
    if (!UCreateTexture(texFilename, gTextureIdRoof))
    {
        cout << "Failed to load texture " << texFilename << endl;
        return EXIT_FAILURE;
    }
    // Load roof texture
    texFilename = "log.jpg";
    if (!UCreateTexture(texFilename, gTextureIdLog))
    {
        cout << "Failed to load texture " << texFilename << endl;
        return EXIT_FAILURE;
    }

    glUseProgram(gProgramId);
    glUniform1i(glGetUniformLocation(gProgramId, "uTextureBase"), 0);
    glUniform1i(glGetUniformLocation(gProgramId, "uTextureExtra"), 0);

    // Sets the background color of the window to black (it will be implicitely used by glClear)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(gWindow))
    {
        // per-frame timing
        // --------------------
        float currentFrame = glfwGetTime();
        gDeltaTime = currentFrame - gLastFrame;
        gLastFrame = currentFrame;

        // input
        // -----
        UProcessInput(gWindow);

        // Render this frame
        URender();

        glfwPollEvents();
    }

    // Release mesh data
    UDestroyMesh(gMeshGround);
    UDestroyMesh(gMeshFences);
    UDestroyMesh(gMeshHouseWalls);
    UDestroyMesh(gMeshHouseRoof);
    UDestroyMesh(gMeshMailbox);

    // Release texture data
    UDestroyTexture(gTextureIdFence);
    UDestroyTexture(gTextureIdGround);
    UDestroyTexture(gTextureIdBrick);
    UDestroyTexture(gTextureIdRoof);

    // Release shader program
    UDestroyShaderProgram(gProgramId);

    exit(EXIT_SUCCESS); // Terminates the program successfully
}


// Initialize GLFW, GLEW, and create a window
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
    // GLFW: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW: window creation
    // ---------------------
    * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (*window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(*window);
    glfwSetKeyCallback(*window, UKeyCallback);
    glfwSetFramebufferSizeCallback(*window, UResizeWindow);
    glfwSetCursorPosCallback(*window, UMousePositionCallback);
    glfwSetScrollCallback(*window, UMouseScrollCallback);
    glfwSetMouseButtonCallback(*window, UMouseButtonCallback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // GLEW: initialize
    // ----------------
    // Note: if using GLEW version 1.13 or earlier
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult)
    {
        std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
        return false;
    }

    // Displays GPU OpenGL version
    cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << endl;

    return true;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void UProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        gCamera.ProcessKeyboard(LEFT, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        gCamera.ProcessKeyboard(RIGHT, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        gCamera.ProcessKeyboard(UP, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        gCamera.ProcessKeyboard(DOWN, gDeltaTime);
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void UResizeWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// glfw: whenever a key is pressed once, not held down
// ---------------------------------------------------
void UKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
        gUseOrthoProjection = !gUseOrthoProjection;
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (gFirstMouse)
    {
        gLastX = xpos;
        gLastY = ypos;
        gFirstMouse = false;
    }

    float xoffset = xpos - gLastX;
    float yoffset = gLastY - ypos; // reversed since y-coordinates go from bottom to top

    gLastX = xpos;
    gLastY = ypos;

    gCamera.ProcessMouseMovement(xoffset, yoffset);
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    gCamera.ProcessMouseScroll(yoffset);
}

// glfw: handle mouse button events
// --------------------------------
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
    {
        if (action == GLFW_PRESS)
            cout << "Left mouse button pressed" << endl;
        else
            cout << "Left mouse button released" << endl;
    }
    break;

    case GLFW_MOUSE_BUTTON_MIDDLE:
    {
        if (action == GLFW_PRESS)
            cout << "Middle mouse button pressed" << endl;
        else
            cout << "Middle mouse button released" << endl;
    }
    break;

    case GLFW_MOUSE_BUTTON_RIGHT:
    {
        if (action == GLFW_PRESS)
            cout << "Right mouse button pressed" << endl;
        else
            cout << "Right mouse button released" << endl;
    }
    break;

    default:
        cout << "Unhandled mouse button event" << endl;
        break;
    }
}

bool UCreateTexture(const char* filename, GLuint& textureId)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
    if (image)
    {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Prevent access violation for some reason? https://stackoverflow.com/a/9950622/6901668
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        if (channels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        else if (channels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        else
        {
            cout << "Not implemented to handle image with " << channels << " channels" << endl;
            return false;
        }

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(image);
        glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

        return true;
    }

    // Error loading the image
    return false;
}

void UDestroyTexture(GLuint textureId)
{
    glGenTextures(1, &textureId);
}


// Functioned called to render a frame
void URender()
{
    // Enable z-depth
    glEnable(GL_DEPTH_TEST);

    // Clear the frame and z buffers
    glClearColor(0.8f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 scale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 rotation = glm::rotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 translation = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 model = translation * rotation * scale;

    // camera/view transformation
    glm::mat4 view = gCamera.GetViewMatrix();

    glm::mat4 projection;
    if (gUseOrthoProjection) {
        // Creates an orthogonal projection
        projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
    }
    else
    {
        // Creates a perspective projection
        projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
    }

    // Set the shader to be used
    glUseProgram(gProgramId);

    // Switch to wireframe (to help with debugging)
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Retrieves and passes transform matrices to the Shader program
    GLint modelLoc = glGetUniformLocation(gProgramId, "model");
    GLint viewLoc = glGetUniformLocation(gProgramId, "view");
    GLint projLoc = glGetUniformLocation(gProgramId, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Reference matrix uniforms from the Pyramid Shader program for the object color, light color, light position, and camera position
    GLint lightColorLoc = glGetUniformLocation(gProgramId, "lightColor");
    GLint lightPositionLoc = glGetUniformLocation(gProgramId, "lightPos");
    GLint viewPositionLoc = glGetUniformLocation(gProgramId, "viewPosition");

    // Pass color, light, and camera data to the Pyramid Shader program's corresponding uniforms
    glUniform3f(lightColorLoc, gLightColor.r, gLightColor.g, gLightColor.b);
    glUniform3f(lightPositionLoc, gLightPosition.x, gLightPosition.y, gLightPosition.z);
    const glm::vec3 cameraPosition = gCamera.Position;
    glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);

    GLint uvScaleLoc = glGetUniformLocation(gProgramId, "uvScale");
    glUniform2fv(uvScaleLoc, 1, glm::value_ptr(gUVScale));
    
    // DRAW: Ground
    // ------------------------------------------------------------------------

    // Activate the ground VBOs contained within the mesh's VAO
    glBindVertexArray(gMeshGround.vao);

    // Activate and bind texture data
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTextureIdGround);

    // Draws the ground triangles
    glDrawElements(GL_TRIANGLES, gMeshGround.nIndices, GL_UNSIGNED_SHORT, NULL);

    // DRAW: Fences
    // ------------------------------------------------------------------------
    
    // Activate the fences VBOs contained within the mesh's VAO
    glBindVertexArray(gMeshFences.vao);

    // Activate and bind texture data
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTextureIdFence);

    // Draws the fences triangles
    glDrawElements(GL_TRIANGLES, gMeshFences.nIndices, GL_UNSIGNED_SHORT, NULL);

    // DRAW: House Walls
    // ------------------------------------------------------------------------

    // Activate the ground VBOs contained within the mesh's VAO
    glBindVertexArray(gMeshHouseWalls.vao);

    // Activate and bind texture data
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTextureIdBrick);

    // Draws the ground triangles
    glDrawElements(GL_TRIANGLES, gMeshHouseWalls.nIndices, GL_UNSIGNED_SHORT, NULL);

    // DRAW: Roof
    // ------------------------------------------------------------------------

    // Activate the ground VBOs contained within the mesh's VAO
    glBindVertexArray(gMeshHouseRoof.vao);

    // Activate and bind texture data
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTextureIdRoof);

    // Draws the ground triangles
    glDrawElements(GL_TRIANGLES, gMeshHouseRoof.nIndices, GL_UNSIGNED_SHORT, NULL);

    // DRAW: Mailbox
    // ------------------------------------------------------------------------

    // Activate the ground VBOs contained within the mesh's VAO
    glBindVertexArray(gMeshMailbox.vao);

    // Activate and bind texture data
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTextureIdLog);

    // Draws the ground triangles
    glDrawElements(GL_TRIANGLES, gMeshMailbox.nIndices, GL_UNSIGNED_SHORT, NULL);

    // DEALLOCATE
    // ------------------------------------------------------------------------

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(gWindow);    // Flips the the back buffer with the front buffer every frame.
}


// Implements the UCreateMesh function
void UCreateMeshGround(GLMesh& mesh)
{
    // Position and Color data
    GLfloat verts[] = {
        // Vertex Positions    // Normals          // UV coordinates

        // Outer bottom
        -10.0f, 0.0f,  10.0f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // A 0 back-left
        -10.0f, 0.0f, -10.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // B 1 front-left
         10.0f, 0.0f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // C 2 front-right
         10.0f, 0.0f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // D 3 back-right
    };

    // Index data to share position data
    GLushort indices[] = {
        // Ground
        A, B, C,
        C, D, A,
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    mesh.nIndices = sizeof(indices) / sizeof(indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Strides between vertex coordinates is 5 (x, y, z, u, v). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}


// Implements the UCreateMesh function
void UCreateMeshFences(GLMesh& mesh)
{
    // Position and Color data
    GLfloat verts[] = {
        // Vertex Positions     // Normals           // UV coordinates

        // Outer bottom
       -10.0f, 0.0f,  10.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, // A 0 back-left
       -10.0f, 0.0f, -10.0f,    1.0f, 1.0f, 0.0f,    0.0f, 0.0f, // B 1 front-left
        10.0f, 0.0f, -10.0f,   -1.0f, 1.0f, 0.0f,    1.0f, 0.0f, // C 2 front-right
        10.0f, 0.0f,  10.0f,   -1.0f, 1.0f, 0.0f,    0.0f, 0.0f, // D 3 back-right

        // Inner bottom
       -9.5f,  0.0f,  10.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, // E 4
       -9.5f,  0.0f, -9.5f,     1.0f, 1.0f, 0.0f,    0.0f, 0.0f, // F 5
        9.5f,  0.0f, -9.5f,    -1.0f, 1.0f, 0.0f,    1.0f, 0.0f, // G 6
        9.5f,  0.0f,  10.0f,   -1.0f, 1.0f, 0.0f,    0.0f, 0.0f, // H 7

        // Outer top
       -10.0f, 2.0f,  10.0f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f, // I 8
       -10.0f, 2.0f, -10.0f,    1.0f, 0.0f, 1.0f,    0.0f, 1.0f, // J 9
        10.0f, 2.0f, -10.0f,   -1.0f, 0.0f, 1.0f,    1.0f, 1.0f, // K 10
        10.0f, 2.0f,  10.0f,   -1.0f, 0.0f, 0.0f,    0.0f, 1.0f, // L 11

        // Inner top
       -9.5f,  2.0f,  10.0f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f, // M 12
       -9.5f,  2.0f, -9.5f,     1.0f, 0.0f, 1.0f,    0.0f, 1.0f, // N 13
        9.5f,  2.0f, -9.5f,    -1.0f, 0.0f, 1.0f,    1.0f, 1.0f, // O 14
        9.5f,  2.0f,  10.0f,   -1.0f, 0.0f, 0.0f,    0.0f, 1.0f, // P 15
    };

    // Index data to share position data
    GLushort indices[] = {
        // Outer walls
        // Left
        I, A, B,
        B, J, I,
        // Front
        J, B, C,
        C, K, J,
        // Right
        K, C, D,
        D, L, K,

        // Wall caps
        // Left
        I, A, E,
        E, M, I,
        // Right
        P, H, D,
        D, L, P,

        // Inner walls
        // Left
        M, E, F,
        F, N, M,
        // Front
        N, F, G,
        G, O, N,
        // Right
        O, G, H,
        H, P, O,

        // Wall tops
        // Left
        I, J, N,
        N, M, I,
        // Front
        N, J, K,
        K, O, N,
        // Right
        K, L, P,
        P, O, K,
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    mesh.nIndices = sizeof(indices) / sizeof(indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Strides between vertex coordinates is 5 (x, y, z, u, v). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}


// Implements the UCreateMesh function
void UCreateMeshHouseWalls(GLMesh& mesh)
{
    // Position and Color data
    GLfloat verts[] = {
        // Vertex Positions    // Normals          // UV coordinates

        // Front
        -5.0f, 0.0f,  5.0f,  0.0f, 1.0f,  0.0f,   1.0f, 1.0f, // A
        -5.0f, 3.0f,  5.0f,  0.0f, 1.0f,  0.0f,   1.0f, 0.0f, // B
         5.0f, 3.0f,  5.0f,  0.0f, 1.0f,  0.0f,   0.0f, 0.0f, // C
         5.0f, 0.0f,  5.0f,  0.0f, 1.0f,  0.0f,   0.0f, 1.0f, // D

        // Right
         5.0f, 0.0f,  5.0f,  0.0f, 1.0f,  0.0f,   0.0f, 0.0f, // E = D
         5.0f, 3.0f,  5.0f,  0.0f, 1.0f,  0.0f,   0.0f, 1.0f, // F = C
         5.0f, 3.0f, -5.0f,  0.0f, 1.0f,  0.0f,   1.0f, 1.0f, // G
         5.0f, 0.0f, -5.0f,  0.0f, 1.0f,  0.0f,   1.0f, 0.0f, // H

        // Back
         5.0f, 0.0f, -5.0f,  0.0f, 1.0f,  0.0f,   0.0f, 0.0f, // I
         5.0f, 3.0f, -5.0f,  0.0f, 1.0f,  0.0f,   0.0f, 1.0f, // J
        -5.0f, 3.0f, -5.0f,  0.0f, 1.0f,  0.0f,   1.0f, 1.0f, // K
        -5.0f, 0.0f, -5.0f,  0.0f, 1.0f,  0.0f,   1.0f, 0.0f, // L

        // Left
        -5.0f, 0.0f, -5.0f,  0.0f, 1.0f,  0.0f,   0.0f, 0.0f, // M
        -5.0f, 3.0f, -5.0f,  0.0f, 1.0f,  0.0f,   0.0f, 1.0f, // N
        -5.0f, 3.0f,  5.0f,  0.0f, 1.0f,  0.0f,   1.0f, 1.0f, // O
        -5.0f, 0.0f,  5.0f,  0.0f, 1.0f,  0.0f,   1.0f, 0.0f, // P
    };

    // Index data to share position data
    GLushort indices[] = {
        // Front
        A, B, C,
        C, D, A,
        
        // Right
        E, F, G,
        G, H, E,

        // Back
        I, J, K,
        K, L, I,

        // Left
        M, N, O,
        O, P, M,
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    mesh.nIndices = sizeof(indices) / sizeof(indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Strides between vertex coordinates is 5 (x, y, z, u, v). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}


// Implements the UCreateMesh function
void UCreateMeshHouseRoof(GLMesh& mesh)
{
    // Position and Color data
    GLfloat verts[] = {
        // Vertex Positions    // Normals          // UV coordinates

        // Left Pyramid
        // Front
        -5.0f, 3.0f,  5.0f,  1.0f, 0.0f,  0.0f,   0.0f, 0.0f, // A
        -3.0f, 5.0f,  5.0f,  1.0f, 0.0f,  0.0f,   0.5f, 1.0f, // B
        -1.0f, 3.0f,  5.0f,  1.0f, 0.0f,  0.0f,   1.0f, 0.0f, // C

        // Right
        -1.0f, 3.0f,  5.0f,  1.0f, 0.0f,  0.0f,   0.0f, 0.0f, // D
        -3.0f, 5.0f,  5.0f,  1.0f, 0.0f,  0.0f,   0.0f, 1.0f, // E
        -3.0f, 5.0f, -5.0f,  1.0f, 0.0f,  0.0f,   1.0f, 1.0f, // F
        -3.0f, 5.0f, -5.0f,  1.0f, 0.0f,  0.0f,   1.0f, 1.0f, // G
        -1.0f, 3.0f, -5.0f,  1.0f, 0.0f,  0.0f,   1.0f, 0.0f, // H
        -1.0f, 3.0f,  5.0f,  1.0f, 0.0f,  0.0f,   0.0f, 0.0f, // I

        // Back
        -1.0f, 3.0f, -5.0f,  1.0f, 0.0f,  0.0f,   0.0f, 0.0f, // J
        -3.0f, 5.0f, -5.0f,  1.0f, 0.0f,  0.0f,   0.5f, 1.0f, // K
        -5.0f, 3.0f, -5.0f,  1.0f, 0.0f,  0.0f,   1.0f, 0.0f, // L

        // Left
        -5.0f, 3.0f, -5.0f,  1.0f, 0.0f,  0.0f,   0.0f, 0.0f, // M
        -3.0f, 5.0f, -5.0f,  1.0f, 0.0f,  0.0f,   0.0f, 1.0f, // N
        -3.0f, 5.0f,  5.0f,  1.0f, 0.0f,  0.0f,   1.0f, 1.0f, // O
        -3.0f, 5.0f,  5.0f,  1.0f, 0.0f,  0.0f,   1.0f, 1.0f, // P
        -5.0f, 3.0f,  5.0f,  1.0f, 0.0f,  0.0f,   1.0f, 0.0f, // Q
        -5.0f, 3.0f, -5.0f,  1.0f, 0.0f,  0.0f,   0.0f, 0.0f, // R

        // Right Pyramid
        // Right
         5.0f, 3.0f,  5.0f,  0.0f, 1.0f,  0.0f,   0.0f, 0.0f, // S = Front of right triangle
         5.0f, 5.0f,  0.0f,  0.0f, 0.0f,  1.0f,   0.5f, 1.0f, // T = Top of right triangle
         5.0f, 3.0f, -5.0f,  0.0f, 0.0f,  1.0f,   1.0f, 0.0f, // U = Back of right triangle

        // Front
        -1.0f, 3.0f,  5.0f,  1.0f, 0.0f,  1.0f,   0.25f, 0.0f, // V
        -3.0f, 5.0f,  0.0f,  0.0f, 0.0f,  1.0f,   0.0f, 1.0f, // W
         5.0f, 5.0f,  0.0f,  0.0f, 0.0f,  1.0f,   1.0f, 1.0f, // X
         5.0f, 5.0f,  0.0f,  0.0f, 0.0f,  1.0f,   1.0f, 1.0f, // Y
         5.0f, 3.0f,  5.0f,  0.0f, 1.0f,  1.0f,   1.0f, 0.0f, // Z
        -1.0f, 3.0f,  5.0f,  1.0f, 0.0f,  1.0f,   0.25f, 0.0f, // AA

        // Back
         5.0f, 3.0f, -5.0f,  0.0f, 0.0f,  1.0f,   0.0f, 0.0f, // AB
         5.0f, 5.0f,  0.0f,  0.0f, 0.0f,  1.0f,   0.0f, 1.0f, // AC
        -3.0f, 5.0f,  0.0f,  1.0f, 0.0f,  0.0f,   1.0f, 1.0f, // AD
        -3.0f, 5.0f,  0.0f,  1.0f, 0.0f,  0.0f,   1.0f, 1.0f, // AE
        -1.0f, 3.0f, -5.0f,  0.0f, 0.0f,  1.0f,   0.75f, 0.0f, // AF
         5.0f, 3.0f, -5.0f,  0.0f, 0.0f,  1.0f,   0.0f, 0.0f, // AG
    };

    // Index data to share position data
    GLushort indices[] = {
        // Left Pyramid Front
        A, B, C,
        // Left Pyramid Right
        D, E, F,
        G, H, I,
        // Left Pyramid Back
        J, K, L,
        // Left Pyramid Left
        M, N, O,
        P, Q, R,
        // Right Pyramid Right
        S, T, U,
        // Right Pyramid Front
        V, W, X,
        Y, Z, AA,
        // Right Pyramid Back
        AB, AC, AD,
        AE, AF, AG,
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    mesh.nIndices = sizeof(indices) / sizeof(indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Strides between vertex coordinates is 5 (x, y, z, u, v). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}


// Implements the UCreateMesh function
void UCreateMeshMailbox(GLMesh& mesh)
{
    // Position and Color data
    GLfloat verts[] = {
        // Vertex Positions    // Normals          // UV coordinates

        // Post
        // Front
         2.0f, 0.0f, 8.0f,  0.0f, 1.0f,  0.0f,   0.0f, 0.0f, // A
         2.0f, 1.0f, 8.0f,  0.0f, 1.0f,  0.0f,   0.0f, 1.0f, // B
         2.5f, 1.0f, 8.0f,  0.0f, 1.0f,  0.0f,   1.0f, 1.0f, // C
         2.5f, 0.0f, 8.0f,  0.0f, 1.0f,  0.0f,   1.0f, 0.0f, // D

        // Right
         2.5f, 0.0f, 8.0f,  0.0f, 1.0f,  0.0f,   0.0f, 0.0f, // E
         2.5f, 1.0f, 8.0f,  0.0f, 1.0f,  0.0f,   0.0f, 1.0f, // F
         2.5f, 1.0f, 7.5f,  0.0f, 1.0f,  0.0f,   1.0f, 1.0f, // G
         2.5f, 0.0f, 7.5f,  0.0f, 1.0f,  0.0f,   1.0f, 0.0f, // H

        // Back
         2.5f, 0.0f, 7.5f,  0.0f, 1.0f,  0.0f,   0.0f, 0.0f, // I
         2.5f, 1.0f, 7.5f,  0.0f, 1.0f,  0.0f,   0.0f, 1.0f, // J
         2.0f, 1.0f, 7.5f,  0.0f, 1.0f,  0.0f,   1.0f, 1.0f, // K
         2.0f, 0.0f, 7.5f,  0.0f, 1.0f,  0.0f,   1.0f, 0.0f, // L

        // Left
         2.0f, 0.0f, 7.5f,  0.0f, 1.0f,  0.0f,   0.0f, 0.0f, // M
         2.0f, 1.0f, 7.5f,  0.0f, 1.0f,  0.0f,   0.0f, 1.0f, // N
         2.0f, 1.0f, 8.0f,  0.0f, 1.0f,  0.0f,   1.0f, 1.0f, // O
         2.0f, 0.0f, 8.0f,  0.0f, 1.0f,  0.0f,   1.0f, 0.0f, // P

        // Top
        // Bottom
         2.0f, 1.0f, 8.25f,  0.0f, 1.0f,  0.0f,   0.0f, 0.0f, // Q
         2.0f, 1.0f, 7.25f,  0.0f, 1.0f,  0.0f,   0.0f, 1.0f, // R
         2.5f, 1.0f, 7.25f,  0.0f, 1.0f,  0.0f,   1.0f, 1.0f, // S
         2.5f, 1.0f, 8.25f,  0.0f, 1.0f,  0.0f,   1.0f, 0.0f, // T

        // Front
         2.0f, 1.0f, 8.25f,  0.0f, 1.0f,  0.0f,   0.0f, 0.0f, // U
         2.0f, 1.5f, 8.25f,  0.0f, 1.0f,  0.0f,   0.0f, 1.0f, // V
         2.5f, 1.5f, 8.25f,  0.0f, 1.0f,  0.0f,   1.0f, 1.0f, // W
         2.5f, 1.0f, 8.25f,  0.0f, 1.0f,  0.0f,   1.0f, 0.0f, // X

        // Right
         2.5f, 1.0f, 8.25f,  0.0f, 1.0f,  0.0f,   0.0f, 0.0f, // Y
         2.5f, 1.5f, 8.25f,  0.0f, 1.0f,  0.0f,   0.0f, 1.0f, // Z
         2.5f, 1.5f, 7.25f,  0.0f, 1.0f,  0.0f,   1.0f, 1.0f, // AA
         2.5f, 1.0f, 7.25f,  0.0f, 1.0f,  0.0f,   1.0f, 0.0f, // AB

        // Back
         2.5f, 1.0f, 7.25f,  0.0f, 1.0f,  0.0f,   0.0f, 0.0f, // AC
         2.5f, 1.5f, 7.25f,  0.0f, 1.0f,  0.0f,   0.0f, 1.0f, // AD
         2.0f, 1.5f, 7.25f,  0.0f, 1.0f,  0.0f,   1.0f, 1.0f, // AE
         2.0f, 1.0f, 7.25f,  0.0f, 1.0f,  0.0f,   1.0f, 0.0f, // AF

        // Left
         2.0f, 1.0f, 7.25f,  0.0f, 1.0f,  0.0f,   0.0f, 0.0f, // AG
         2.0f, 1.5f, 7.25f,  0.0f, 1.0f,  0.0f,   0.0f, 1.0f, // AH
         2.0f, 1.5f, 8.25f,  0.0f, 1.0f,  0.0f,   1.0f, 1.0f, // AI
         2.0f, 1.0f, 8.25f,  0.0f, 1.0f,  0.0f,   1.0f, 0.0f, // AJ

        // Top
         2.0f, 1.5f, 8.25f,  0.0f, 1.0f,  0.0f,   0.0f, 0.0f, // AK
         2.0f, 1.5f, 7.25f,  0.0f, 1.0f,  0.0f,   0.0f, 1.0f, // AL
         2.5f, 1.5f, 7.25f,  0.0f, 1.0f,  0.0f,   1.0f, 1.0f, // AM
         2.5f, 1.5f, 8.25f,  0.0f, 1.0f,  0.0f,   1.0f, 0.0f, // AN
    };

    // Index data to share position data
    GLushort indices[] = {
        // Post
        // Front
        A, B, C,
        C, D, A,
        // Right
        E, F, G,
        G, H, E,
        // Back
        I, J, K,
        K, L, I,
        // Left
        M, N, O,
        O, P, M,

        // Top
        // Bottom
        Q, R, S,
        S, T, Q,
        // Front
        U, V, W,
        W, X, U,
        // Right
        Y, Z, AA,
        AA, AB, Y,
        // Back
        AC, AD, AE,
        AE, AF, AC,
        // Left
        AG, AH, AI,
        AI, AJ, AG,
        // Top
        AK, AL, AM,
        AM, AN, AK,
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    mesh.nIndices = sizeof(indices) / sizeof(indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Strides between vertex coordinates is 5 (x, y, z, u, v). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}


void UDestroyMesh(GLMesh& mesh)
{
    glDeleteVertexArrays(1, &mesh.vao);
    glDeleteBuffers(2, mesh.vbos);
}


// Implements the UCreateShaders function
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId)
{
    // Compilation and linkage error reporting
    int success = 0;
    char infoLog[512];

    // Create a Shader program object.
    programId = glCreateProgram();

    // Create the vertex and fragment shader objects
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // Retrive the shader source
    glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
    glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

    // Compile the vertex shader, and print compilation errors (if any)
    glCompileShader(vertexShaderId); // compile the vertex shader
    // check for shader compile errors
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glCompileShader(fragmentShaderId); // compile the fragment shader
    // check for shader compile errors
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    // Attached compiled shaders to the shader program
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);   // links the shader program
    // check for linking errors
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glUseProgram(programId);    // Uses the shader program

    return true;
}


void UDestroyShaderProgram(GLuint programId)
{
    glDeleteProgram(programId);
}

