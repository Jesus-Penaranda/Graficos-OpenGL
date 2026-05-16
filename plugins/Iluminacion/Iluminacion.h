#ifndef LIGHTING_H
#define LIGHTING_H

#include "plugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class Iluminacion : public QObject, public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Plugin")
    Q_INTERFACES(Plugin)

public:
    void onPluginLoad();
    void preFrame();
    void postFrame();

private:
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;
};

#endif
