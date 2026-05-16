#include "multitex.h"
#include <QFileDialog>

void Multitex::onPluginLoad()
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
      "  vtexCoord = (4.0/radius)*(vertex.xy+vertex.zx);"
      "}";
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_src);

    QString fs_src =
      "#version 330 core\n"
      "uniform sampler2D sampler0;"
      "uniform sampler2D sampler1;"
      "in vec2 vtexCoord;"
      "out vec4 fragColor;"
      "void main() {"
      "fragColor =  mix(texture(sampler0, vtexCoord),"
      "                 texture(sampler1, vtexCoord), 0.5); }";
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_src);

  	program = new QOpenGLShaderProgram(this);
        program->addShader(vs);
	program->addShader(fs);
	program->link();

	QString filename = QFileDialog::getOpenFileName(0, "Open Image", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");
	QImage img0(filename);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QImage im0 = img0.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
#else
	QImage im0 = img0.convertToFormat(QImage::Format_ARGB32).rgbSwapped().flipped(Qt::Vertical);
#endif
        g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE0);
	g.glGenTextures( 1, &textureId0);
	g.glBindTexture(GL_TEXTURE_2D, textureId0);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);

	QString filename2 = QFileDialog::getOpenFileName(0, "Open Image 2", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");
	QImage img1(filename2);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QImage im1 = img0.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
#else
	QImage im1 = img0.convertToFormat(QImage::Format_ARGB32).rgbSwapped().flipped(Qt::Vertical);
#endif
        g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE1);
	g.glGenTextures( 1, &textureId1);
	g.glBindTexture(GL_TEXTURE_2D, textureId1);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);
}

void Multitex::preFrame()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();

    program->bind();
    program->setUniformValue("sampler0", 0);
    program->setUniformValue("sampler1", 1);
    program->setUniformValue("radius", float(scene()->boundingBox().radius()));
    program->setUniformValue("modelViewProjectionMatrix", g.camera()->projectionMatrix() * g.camera()->viewMatrix());

    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, textureId0);
    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, textureId1);
}

void Multitex::postFrame()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();

    g.defaultProgram()->bind();

    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, 0);
}
