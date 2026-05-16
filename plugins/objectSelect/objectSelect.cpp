#include "objectSelect.h"
#include <QCoreApplication>

void ObjectSelect::encodeID(const unsigned int i, GLubyte * color) {

    GLubyte R = i & 0xFF;

    GLubyte G = (i >> 8) & 0xFF;

    GLubyte B = (i >> 16) & 0xFF;

    color[0] = R;
    color[1] = G;
    color[2] = B;
    color[3] = 255;
}

void ObjectSelect::decodeID(const GLubyte *color, unsigned int &i) {

    unsigned int R = (unsigned int) color[0];
    unsigned int G = (unsigned int) color[1];
    unsigned int B = (unsigned int) color[2];

    i = R + (G << 8) + (B << 16);
}

void ObjectSelect::onPluginLoad() {
    std::cout << "[ObjectSelect plugin] Ctrl + Right Click - Select object" << std::endl;

    GLWidget &g = *glwidget();
    g.makeCurrent();

    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(g.getPluginPath() + "/../objectSelect/objectSelect.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(g.getPluginPath() + "/../objectSelect/objectSelect.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();

    if (!program->isLinked())
        std::cout << "Shader link error" << std::endl;
}

void ObjectSelect::selectDraw(GLWidget & g) {

    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    program->bind();

    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);

    for (unsigned int i = 0; i < scene()->objects().size(); ++i) {

        GLubyte color[4];

        encodeID(i, color);

        program->setUniformValue("color",
            QVector4D(color[0]/255.0, color[1]/255.0, color[2]/255.0, 1.0));

        drawPlugin()->drawObject(i);
    }

}

void ObjectSelect::mouseReleaseEvent(QMouseEvent* e) {

    if (!(e->button() & Qt::RightButton)) return;

    if (e->modifiers() & (Qt::ShiftModifier)) return;

    if (!(e->modifiers() & Qt::ControlModifier)) return;

    GLWidget &g = *glwidget();
    g.makeCurrent();

    selectDraw(g);

    int x = e->x();

    int y = g.height() - e->y();

    GLubyte read[4];

    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);

    if (read[3] == 255) {

        unsigned int tmp;
        decodeID(read, tmp);

        scene()->setSelectedObject((int) tmp);

        std::cout << tmp << std::endl;
    }
    else {

        scene()->setSelectedObject(-1);
        std::cout << -1 << std::endl;
    }

    g.update();
}
