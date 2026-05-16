#ifndef VIEWER_OBJECTSELECT_H
#define VIEWER_OBJECTSELECT_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class ObjectSelect : public QObject, public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Plugin")
    Q_INTERFACES(Plugin)

private:
    void encodeID(const unsigned int, GLubyte *);
    void decodeID(const GLubyte *, unsigned int &);
    void selectDraw(GLWidget&);
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;
public:
    void onPluginLoad();
    void mouseReleaseEvent(QMouseEvent*);
};

#endif
