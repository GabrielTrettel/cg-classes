#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H
#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "model.h"
class OpenGLWidget:public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    std::shared_ptr<Model> model = nullptr ;
    OpenGLWidget (QWidget * parent = 0);
protected:
    void initializeGL();
    void resizeGL(int width , int height);
    void paintGL();

signals :
    void statusBarMessage(QString);
    public slots:
    void showFileOpenDialog();

};
# endif // OPENGLWIDGET_H
