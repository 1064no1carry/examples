#include <iostream>
using namespace std;

#include "vgl.h"
#include "LoadShaders.h"

const GLuint NumVertices = 6;

const GLuint Triangles_ID = 0;
const GLuint NumVAOs = 3;

const GLuint Buffer_ID = 0;
const GLuint NumBuffer = 3;
const GLuint vPosition = 0;

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffer];

static const GLfloat vertices[NumVertices][3] = {
    {-0.9, -0.9, 0.5}, {0.85, -0.9, 0.5}, {-0.9, 0.85, 0.5},
    {0.9, -0.85, 0.5}, {0.9, 0.9, 0.5}, {-0.85, 0.9, 0.5}
};

void init() {
    // glGen*, glBind*
    // create vaos and bind selected vaos to context
    // return NumVAOS unused names for use as vaos in VAOs array
    glGenVertexArrays(NumVAOs, VAOs);
    // attach this vao to opengl context before use
    glBindVertexArray(VAOs[Triangles_ID]);
    GLboolean isVertexArray = glIsVertexArray(VAOs[Triangles_ID]);
    string output = isVertexArray == GL_TRUE? "yes" : "no";
    cout << "is vertex array? " << output << endl;

    // create names of vertex-buffer objects
    glGenBuffers(NumBuffer, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[Buffer_ID]);
    // loading data(vertices) into buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // init shaders
    ShaderInfo  shaders[] =
    {
        {GL_VERTEX_SHADER, "media/shaders/triangles/triangles.vert"},
        {GL_FRAGMENT_SHADER, "media/shaders/triangles/triangles.frag"},
        {GL_NONE, NULL}
    };

    GLuint program = LoadShaders(shaders);
    glUseProgram(program);
    
    // put buffer into VAO attributes position
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);
}

void display() {
    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, black);
    glBindVertexArray(VAOs[Triangles_ID]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}


int main(int argc, char **argv) {
    // initialize a GLFW library
    glfwInit();
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // return a window
    // also create a OpenGL context associated with this window
    GLFWwindow *window = glfwCreateWindow(600, 600, "my triangle app", nullptr, nullptr);
    // make the context of this window current for main thread
    glfwMakeContextCurrent(window);
    
    gl3wInit();
    init();
    
    while (!glfwWindowShouldClose(window))
    {
        display();
        // swap the front and back buffers
        glfwSwapBuffers(window);
        // poll all pending events and process
        glfwPollEvents();
    }
    
    //glDeleteVertexArrays(NumVAOs, VAOs);
    glfwDestroyWindow(window);
    glfwTerminate();
}
