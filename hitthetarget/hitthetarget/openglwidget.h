#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QElapsedTimer>
//#include <QRandomGenerator>

#include <memory>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT

    GLuint vboVertices = 0;
    GLuint vboColors = 0;
    GLuint vboIndices = 0;

    GLuint vao = 0;

    std::unique_ptr<QVector4D []> vertices = nullptr;
    std::unique_ptr<QVector4D []> colors = nullptr;
    std::unique_ptr<unsigned int[]> indices = nullptr;

    GLuint shaderProgram;

    float playerPosYOffset; // Player displacement along Y axis
    float playerPosXOffset; // Player displacement along X axis
    float playerPosY; // Current player Y position
    float playerPosX; // Current player Y position


    float targetPosYOffset; // Target displacement along Y axis
    float targetPosY; // Current target Y position

    bool shooting; // Whether the projectile is being animated
    bool blocked_game;

    float projectilePosX; // Projectile X position
    float projectilePosY; // Projectile Y position
    int numHits; // Number of hits

    qint64 max_time = 0;
    qint64 elapsed_time = 0;

    QElapsedTimer el_timer;

    QTimer timer;
    QTime time;

public:
    explicit OpenGLWidget (QWidget *parent = 0);
    ~OpenGLWidget();

    void createVBOs();
    void createShaders();

    void destroyVBOs();
    void destroyShaders();

protected :
    void initializeGL();
    void resizeGL (int width, int height);
    void paintGL();

    void checkPlayerBounds();
    void update_score();
    void restart_game();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
    void updateHitsLabel(QString);

public slots:
    void animate();
};
#endif
