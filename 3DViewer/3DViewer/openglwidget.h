#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "model.h"


//class OpenGLWidget
//{
//public:
//    OpenGLWidget();
//};


class OpenGLWidget : public QOpenGLWidget , protected QOpenGLExtraFunctions {
    Q_OBJECT

public:
    OpenGLWidget (QWidget * parent = 0);
    std::shared_ptr<Model> model = nullptr;
protected:
    void initializeGL () ;
    void resizeGL (int width , int height ) ;
    void paintGL () ;

signals :
    void statusBarMessage ( QString ) ;
public slots :
    void showFileOpenDialog () ;
};

#endif // OPENGLWIDGET_H
