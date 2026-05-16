#include "Iluminacion.h"
#include <QCoreApplication>

void Iluminacion::onPluginLoad() {
    GLWidget &g = *glwidget();
    g.makeCurrent();

    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(g.getPluginPath() + "/../Iluminacion/Iluminacion.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(g.getPluginPath() + "/../Iluminacion/Iluminacion.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);

    program->bindAttributeLocation("vertex", 0);
    program->bindAttributeLocation("normal", 1);

    program->link();
}

void Iluminacion::preFrame() {
    GLWidget &g = *glwidget();
    g.makeCurrent();

    program->bind();

    g.glDisable(GL_CULL_FACE);

    QMatrix4x4 projection = camera()->projectionMatrix();
    QMatrix4x4 view = camera()->viewMatrix();

    QMatrix4x4 modelView = view;

    QMatrix4x4 modelViewProjection = projection * view;

    QMatrix3x3 normalMatrix = view.normalMatrix();

    program->setUniformValue("modelViewProjectionMatrix", modelViewProjection);
    program->setUniformValue("modelViewMatrix", modelView);
    program->setUniformValue("normalMatrix", normalMatrix);

    program->setUniformValue("lightPosition", QVector4D(0, 0, 0, 1));

    program->setUniformValue("lightAmbient", QVector4D(0.1, 0.1, 0.1, 1.0));

    program->setUniformValue("lightDiffuse", QVector4D(1.0, 1.0, 1.0, 1.0));

    program->setUniformValue("lightSpecular", QVector4D(1.0, 1.0, 1.0, 1.0));

    program->setUniformValue("matAmbient", QVector4D(0.7, 0.1, 0.1, 1.0));

    program->setUniformValue("matDiffuse", QVector4D(0.7, 0.1, 0.1, 1.0));

    program->setUniformValue("matSpecular", QVector4D(1.0, 1.0, 1.0, 1.0));

    program->setUniformValue("matShininess", 64.0f);
}

void Iluminacion::postFrame() {
    GLWidget &g = *glwidget();
    g.makeCurrent();

    g.glEnable(GL_CULL_FACE);

    program->release();
}
