#include "S4_skyplane.h"
#include "glwidget.h"

void S4_skyplane::onPluginLoad()
{
	GLWidget &g = *glwidget();
    g.makeCurrent();

	m_fs = new QOpenGLShader(QOpenGLShader::Fragment);
	m_vs = new QOpenGLShader(QOpenGLShader::Vertex);

	m_fs->compileSourceFile("mirror.frag");
	m_vs->compileSourceFile("mirror.vert");

	s_fs = new QOpenGLShader(QOpenGLShader::Fragment);
	s_vs = new QOpenGLShader(QOpenGLShader::Vertex);

	s_fs->compileSourceFile("sky.frag");
	s_vs->compileSourceFile("sky.vert");

	program_M = new QOpenGLShaderProgram();
	program_S = new QOpenGLShaderProgram();

	program_M->addShader(m_fs);
	program_M->addShader(m_vs);

	program_S->addShader(s_fs);
	program_S->addShader(s_vs);
	QImage img0("sky.jpg");
	QImage im0 = img0.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
	g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE0);
	g.glGenTextures( 1, &texID);
	g.glBindTexture(GL_TEXTURE_2D, texID);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);

	g.glGenVertexArrays(1, &rectVAO);
    g.glBindVertexArray(rectVAO);

	float far = 0.99999;
    float coords[] = { -1, -1, far,
                        1, -1, far,
                       -1,  1, far,
                        1,  1, far};

    GLuint VBO_coords;
    g.glGenBuffers(1, &VBO_coords);
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
	g.glEnableVertexAttribArray(0);
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    g.glBindVertexArray(0);

}

void S4_skyplane::preFrame()
{

}

void S4_skyplane::postFrame()
{

}

void S4_skyplane::onObjectAdd()
{

}

bool S4_skyplane::drawScene()
{
	return false;
}

bool S4_skyplane::drawObject(int)
{
	return false;
}

bool S4_skyplane::paintGL()
{
	GLWidget & g = *glwidget();
	g.makeCurrent();

	g.glClearColor(0,0,0,0);
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	program_S->link();
	program_S->bind();
	g.makeCurrent();

	g.glBindTexture(GL_TEXTURE_2D, texID);

	program_S->setUniformValue("sampler0", 0);
	program_S->setUniformValue("modelViewMatrix", g.camera()->viewMatrix());
	program_S->setUniformValue("modelViewProjectionMatrix", g.camera()->projectionMatrix() *  g.camera()->viewMatrix());

	g.glBindVertexArray(rectVAO);
	g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	g.glBindVertexArray(0);

	program_M->link();
	program_M->bind();
	g.glBindTexture(GL_TEXTURE_2D, texID);
	program_S->setUniformValue("sampler0", 0);
	program_M->setUniformValue("modelViewMatrix", g.camera()->viewMatrix());
	program_M->setUniformValue("modelViewProjectionMatrix", g.camera()->projectionMatrix() *  g.camera()->viewMatrix());

	drawPlugin()->drawScene();

	return true;
}

void S4_skyplane::keyPressEvent(QKeyEvent *)
{

}

void S4_skyplane::mouseMoveEvent(QMouseEvent *)
{

}
