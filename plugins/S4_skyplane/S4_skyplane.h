#ifndef _S4_SKYPLANE_H
#define _S4_SKYPLANE_H

#include "plugin.h"

class S4_skyplane: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin")
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

	 void onObjectAdd();
	 bool drawScene();
	 bool drawObject(int);

	 bool paintGL();

	 void keyPressEvent(QKeyEvent *);
	 void mouseMoveEvent(QMouseEvent *);
  private:

	QOpenGLShaderProgram * program_M, * program_S;
	QOpenGLShader *m_vs, *m_fs, *s_vs, *s_fs;

	GLuint texID, rectVAO;
};

#endif
