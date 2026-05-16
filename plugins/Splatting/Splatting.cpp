#include "Splatting.h"
#include <QFileDialog>

void Splatting::onPluginLoad()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();

    QString vs_src = \
      "#version 330 core\n"
      "uniform float radius = 1.0;"
      "uniform mat4 modelViewProjectionMatrix;"
      "layout (location = 0) in vec3 vertex;"
      "out vec2 vtexCoord;"
      "void main() {"

      "  gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.);"

      "  vtexCoord = (4.0/radius)*vertex.xz;"
      "}";

    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_src);

    QString fs_src =
      "#version 330 core\n"
      "uniform sampler2D sampler0;"
      "uniform sampler2D sampler1;"
      "uniform sampler2D sampler2;"
      "in vec2 vtexCoord;"
      "out vec4 fragColor;"
      "void main() {"

      "  vec4 colorRoca = texture(sampler0, vtexCoord);"

      "  vec4 colorHierba = texture(sampler1, vtexCoord);"

      "  float ruido = texture(sampler2, vtexCoord).r;"

      "  vec4 colorFinal = mix(colorRoca, colorHierba, ruido);"

      "  fragColor = colorFinal;"
      "}";

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_src);

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();

    QString filename = QFileDialog::getOpenFileName(
        0,
        "Open Image 1 (Roca)",
        "/assig/grau-g/Textures",
        "Image file (*.png *.jpg)"
    );

    QImage img0(filename);

    QImage im0 = img0.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();

    g.makeCurrent();
    g.glActiveTexture(GL_TEXTURE0);
    g.glGenTextures(1, &textureId0);
    g.glBindTexture(GL_TEXTURE_2D, textureId0);
    g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                   im0.width(), im0.height(), 0,
                   GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    g.glBindTexture(GL_TEXTURE_2D, 0);

    QString filename2 = QFileDialog::getOpenFileName(
        0,
        "Open Image 2 (Hierba)",
        "/assig/grau-g/Textures",
        "Image file (*.png *.jpg)"
    );
    QImage img1(filename2);

    QImage im1 = img1.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();

    g.makeCurrent();
    g.glActiveTexture(GL_TEXTURE1);
    g.glGenTextures(1, &textureId1);
    g.glBindTexture(GL_TEXTURE_2D, textureId1);
    g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                   im1.width(), im1.height(), 0,
                   GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    g.glBindTexture(GL_TEXTURE_2D, 0);

    QString filename3 = QFileDialog::getOpenFileName(
        0,
        "Open Image 3 (Ruido)",
        "/assig/grau-g/Textures",
        "Image file (*.png *.jpg)"
    );
    QImage img3(filename3);

    QImage im3 = img3.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();

    g.makeCurrent();
    g.glActiveTexture(GL_TEXTURE2);
    g.glGenTextures(1, &textureId2);
    g.glBindTexture(GL_TEXTURE_2D, textureId2);
    g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                   im3.width(), im3.height(), 0,
                   GL_RGBA, GL_UNSIGNED_BYTE, im3.bits());
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    g.glBindTexture(GL_TEXTURE_2D, 0);
}

void Splatting::preFrame()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();

    program->bind();

    program->setUniformValue("sampler0", 0);
    program->setUniformValue("sampler1", 1);
    program->setUniformValue("sampler2", 2);

    program->setUniformValue("radius", float(scene()->boundingBox().radius()));

    program->setUniformValue("modelViewProjectionMatrix",
                             g.camera()->projectionMatrix() * g.camera()->viewMatrix());

    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, textureId0);

    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, textureId1);

    g.glActiveTexture(GL_TEXTURE2);
    g.glBindTexture(GL_TEXTURE_2D, textureId2);
}

void Splatting::postFrame()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();

    g.defaultProgram()->bind();

    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, 0);

    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, 0);

    g.glActiveTexture(GL_TEXTURE2);
    g.glBindTexture(GL_TEXTURE_2D, 0);
}
