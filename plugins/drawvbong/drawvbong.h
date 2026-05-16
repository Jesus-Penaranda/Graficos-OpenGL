#ifndef _DRAW_VBONG_H
#define _DRAW_VBONG_H

#include <vector>
#include "plugin.h"

using namespace std;

class DrawVBOng : public QObject, public Plugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "Plugin")
  Q_INTERFACES(Plugin)

 public:
  ~DrawVBOng();
  void cleanUp();

  void onSceneClear();
  void onPluginLoad();
  void onObjectAdd();
  bool drawScene();
  bool drawObject(int);

 private:
  void addVBO(unsigned int currentObject);

  vector<GLuint> VAOs;
  vector<GLuint> coordBuffers;
  vector<GLuint> normalBuffers;
  vector<GLuint> stBuffers;
  vector<GLuint> colorBuffers;
  vector<GLuint> numIndices;
};

#endif
