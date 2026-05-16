#include "ResaltatObjecteSeleccionat.h"
#include <QCoreApplication>

void ResaltatObjecteSeleccionat::encodeID(const unsigned int i, GLubyte * color) {

    GLubyte R = i;
    GLubyte G = 0;
    GLubyte B = 0;

    color[0] = R;
    color[1] = G;
    color[2] = B;
    color[3] = 255;
}

void ResaltatObjecteSeleccionat::decodeID(const GLubyte *color, unsigned int &i)
{

    i = color[0];
}

void ResaltatObjecteSeleccionat::onPluginLoad() {
    GLWidget &g = *glwidget();
    g.makeCurrent();

    float vertices[] = {
        0,0,0,  1,0,0,  0,1,0,  1,1,0,
        0,0,1,  1,0,1,  0,1,1,  1,1,1
    };

    unsigned int indices[] = {
        0,1, 1,3, 3,2, 2,0,
        4,5, 5,7, 7,6, 6,4,
        0,4, 1,5, 2,6, 3,7
    };
    numIndices = 24;

    g.glGenVertexArrays(1, &VAO);
    g.glBindVertexArray(VAO);

    g.glGenBuffers(1, &coordBufferID);
    g.glBindBuffer(GL_ARRAY_BUFFER, coordBufferID);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(0);

    g.glGenBuffers(1, &indexBufferID);
    g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    g.glBindVertexArray(0);

    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(
        "#version 330 core\n"
        "layout (location = 0) in vec3 vertex;\n"
        "uniform mat4 MVP;\n"
        "uniform mat4 T;\n"
        "void main() { gl_Position = MVP * T * vec4(vertex, 1.0); }"
    );

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "uniform vec4 colorObj;\n"
        "void main() { fragColor = colorObj; }"
    );

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();

    vsSelect = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsSelect->compileSourceFile(g.getPluginPath() + "/../objectSelect/objectSelect.vert");

    fsSelect = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsSelect->compileSourceFile(g.getPluginPath() + "/../objectSelect/objectSelect.frag");

    programSelect = new QOpenGLShaderProgram(this);
    programSelect->addShader(vsSelect);
    programSelect->addShader(fsSelect);
    programSelect->link();
}

void ResaltatObjecteSeleccionat::selectDraw(GLWidget & g) {

    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    programSelect->bind();

    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    programSelect->setUniformValue("modelViewProjectionMatrix", MVP);

    for (unsigned int i = 0; i < scene()->objects().size(); ++i) {

        GLubyte color[4];

        encodeID(i, color);

        programSelect->setUniformValue("color",
            QVector4D(color[0]/255.0, color[1]/255.0, color[2]/255.0, 1.0));

        drawPlugin()->drawObject(i);
    }

    programSelect->release();
}

void ResaltatObjecteSeleccionat::mouseReleaseEvent(QMouseEvent* e) {

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

        unsigned int id;
        decodeID(read, id);

        scene()->setSelectedObject((int) id);
        std::cout << "Seleccionado ID: " << id << std::endl;
    }
    else {

        scene()->setSelectedObject(-1);
    }

    g.update();
}

void ResaltatObjecteSeleccionat::postFrame() {

    int seleccionat = scene()->selectedObject();

    if (seleccionat >= 0 && seleccionat < (int)scene()->objects().size()) {
        GLWidget &g = *glwidget();
        g.makeCurrent();

        program->bind();

        QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
        program->setUniformValue("MVP", MVP);

        const Object &obj = scene()->objects()[seleccionat];
        Box box = obj.boundingBox();

        QMatrix4x4 T;
        T.translate(box.min());
        T.scale(box.max() - box.min());
        program->setUniformValue("T", T);

        program->setUniformValue("colorObj", QVector4D(1, 0, 0, 1));

        g.glBindVertexArray(VAO);
        g.glDrawElements(GL_LINES, numIndices, GL_UNSIGNED_INT, (GLvoid*)0);
        g.glBindVertexArray(0);

        program->release();
    }
}
