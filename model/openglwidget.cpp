#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent):QOpenGLWidget(parent)
{

}
void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport (0, 0, w, h);
}
void OpenGLWidget :: paintGL ()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor(1,1,1,1);
    if(! model )
        return ;
    model->drawModel ();
}
void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    qDebug("OpenGL version : %s", glGetString(GL_VERSION));
    qDebug("GLSL %s", glGetString(GL_SHADING_LANGUAGE_VERSION ));
    glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::showFileOpenDialog()
{
    QByteArray fileFormat = "off";
    QString fileName = QFileDialog::getOpenFileName(this,"Open File", QDir::homePath(),
            QString("\%1Files (*.\%2)").arg(QString(fileFormat.toUpper())).arg(QString(fileFormat)), 0
#ifdef Q_OS_LINUX
    , QFileDialog::DontUseNativeDialog
# endif
    );
    if(!fileName.isEmpty())
    {
        model = std::make_shared<Model>(this);
        model->readOFFFile(fileName);
        emit statusBarMessage(QString("Vertices: \%1, Faces: \%2").arg(model->numVertices).arg(model->numFaces));
    }
    update();
}


