#include "openglwidget.h"

//OpenGLWidget::OpenGLWidget(QWidget *parent) : QWidget(parent) {

//}

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
}


OpenGLWidget::~OpenGLWidget() {
    destroyVBOs();
    destroyShaders();
}


void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
}


void OpenGLWidget::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
}


void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);
}


void OpenGLWidget::toggleBackgroundColor(bool changeBColor) {
    makeCurrent();
    if (changeBColor)
        glClearColor(0.0, 0, 0, 1);
    else
        glClearColor(1, 1, 1, 1);

    update();
}



void OpenGLWidget::createShaders() {
    // makeCurrent()

    destroyShaders();
    QString vertexShaderFile(":/shaders/vshader1.glsl");
    QString fragmentShaderFile(":/shaders/fshader1.glsl");

    QFile vs(vertexShaderFile);
    QFile fs(fragmentShaderFile);

    vs.open(QFile::ReadOnly | QFile::Text);
    fs.open(QFile::ReadOnly | QFile::Text);

    QTextStream streamVs(&vs), streamFs(&fs);

    QString qtStringVs = streamVs.readAll();
    QString qtStringFs = streamFs.readAll();

    std::string stdStringVs = qtStringVs.toStdString();
    std::string stdStringFs = qtStringFs.toStdString();

    // Create an empty vertex shader handle
    GLuint vertexShader = 0;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Sed the vertex shader source code to GL
    const GLchar *source = stdStringVs.c_str();
    glShaderSource(vertexShader, 1, &source, 0);

    // Compile vertex shader
    glCompileShader(vertexShader);
    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

    if(isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
        qDebug("%s", &infoLog[0]);

        glDeleteShader(vertexShader);
        return;
    }

    // Create an empty fragment shader handle
    GLuint fragmentShader = 0;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Send the gragment shader soice code to GL
    // Note that std::string's.c_str is NULL characeter terminated
    source = stdStringFs.c_str();
    glShaderSource(fragmentShader, 1, &source , 0);

    // Compile the fragment shader
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
        qDebug("%s", &infoLog[0]);
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
        return;
    }

    shaderProgram = glCreateProgram();
    // Attach our shaders to our program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Link our program
    GLint isLinked = 0;


    glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);
        qDebug("%s", &infoLog[0]);

        glDeleteProgram(shaderProgram);
        glDeleteProgram(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    vs.close();
    fs.close();
}











//
