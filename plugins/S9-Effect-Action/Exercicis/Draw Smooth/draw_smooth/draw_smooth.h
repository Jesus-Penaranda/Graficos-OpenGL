#ifndef _DRAW_SMOOTH_H
#define _DRAW_SMOOTH_H

#include "plugin.h"
#include <vector>
#include <QPainter>

using namespace std;

class Draw_smooth: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin")
	Q_INTERFACES(Plugin)

    public:
        ~Draw_smooth();

        void onSceneClear();
        void onPluginLoad();
        void onObjectAdd();
        bool drawObject(int i);
        bool drawScene();
        void postFrame();
        void keyPressEvent(QKeyEvent*);

    private:
        void addVBO(unsigned int currentObject);
        void cleanUp();

        bool useIndices = false;

        vector<GLuint> VAOs;
        vector<GLuint> coordBuffers;
        vector<GLuint> normalBuffers;
        vector<GLuint> stBuffers;
        vector<GLuint> colorBuffers;
        vector<GLuint> indexBuffers;
        vector<GLuint> numElements;

        QPainter painter;
};

#endif
