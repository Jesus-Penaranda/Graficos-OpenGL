#include "AnimateVertices.h"
#include "glwidget.h"

void AnimateVertices::onPluginLoad()
{
	elapsedTimer.start();
	QString vs_src = R"""(
		#version 330 core
		const float pi = 3.141592;
		const float amplitude = 0.1;
		const float freq = 1.0;
		layout (location = 0) in vec3 vertex;
		layout (location = 1) in vec3 normal;
		layout (location = 2) in vec3 color;
		out vec4 vertColor;
		uniform mat4 modelViewProjectionMatrix;
		uniform mat3 normalMatrix;
		uniform float time;
		vec3 animation() {
			return vertex + normal * amplitude * sin(2.0 * pi * freq * time);
		}

		void main() {
		vec3 N = normalize(normalMatrix * normal);
		vertColor = vec4(N.zzz, 1.0);
		gl_Position = modelViewProjectionMatrix * vec4(animation(), 1.0);
		}
	)""";
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs->compileSourceCode(vs_src);
	cout << "VS log:" << vs->log().toStdString() << endl;

	QString fs_src = R"""(
		#version 330 core
		out vec4 fragColor;
		in vec4 vertColor;
		void main() {
			fragColor=vertColor;
		}
	)""";
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fs->compileSourceCode(fs_src);
	cout << "FS log:" << fs->log().toStdString() << endl;

	program = new QOpenGLShaderProgram(this);
	program->addShader(vs);
	program->addShader(fs);
	program->link();
	cout << "Link log:" << program->log().toStdString() << endl;
}

void AnimateVertices::preFrame()
{
    program->bind();

    float currentTime = elapsedTimer.elapsed() / 1000.0f;
    int currentSecond = int(currentTime);
    static int lastSecond = -1;
    if (currentSecond != lastSecond)
	{
        cout << "Tiempo: " << currentSecond << " segundos" << endl;
        lastSecond = currentSecond;
    }

    program->setUniformValue("time", currentTime);
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    QMatrix3x3 N = camera()->viewMatrix().normalMatrix();
    program->setUniformValue("normalMatrix", N);
}

void AnimateVertices::postFrame()
{
	program->release();
}

void AnimateVertices::onObjectAdd()
{

}

bool AnimateVertices::drawScene()
{
	return false;
}

bool AnimateVertices::drawObject(int)
{
	return false;
}

bool AnimateVertices::paintGL()
{
	return false;
}

void AnimateVertices::keyPressEvent(QKeyEvent *)
{

}

void AnimateVertices::mouseMoveEvent(QMouseEvent *)
{

}
