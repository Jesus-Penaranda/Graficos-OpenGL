#ifndef _RESALTATOBJECTESELECCIONAT_H
#define _RESALTATOBJECTESELECCIONAT_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class ResaltatObjecteSeleccionat : public QObject, public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Plugin")
    Q_INTERFACES(Plugin)

public:
    void onPluginLoad();
    void postFrame();
    void mouseReleaseEvent(QMouseEvent* e);

private:

    void encodeID(const unsigned int i, GLubyte * color);
    void decodeID(const GLubyte *color, unsigned int &i);
    void selectDraw(GLWidget & g);

    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;
    GLuint VAO;
    GLuint coordBufferID;
    GLuint indexBufferID;
    unsigned int numIndices;

    QOpenGLShaderProgram* programSelect;
    QOpenGLShader* vsSelect;
    QOpenGLShader* fsSelect;
};

#endif
