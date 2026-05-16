#include "renderdefault.h"
#include "glwidget.h"

bool RenderDefault::paintGL()
{
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if (drawPlugin())
        drawPlugin()->drawScene();

    glwidget()->drawAxes();

    return true;
}
