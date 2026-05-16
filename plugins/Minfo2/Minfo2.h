#ifndef _MINFO2_H
#define _MINFO2_H

#include "plugin.h"
#include <QPainter>

class Minfo2: public QObject, public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Plugin")
    Q_INTERFACES(Plugin)

  public:

     void onPluginLoad();
     void preFrame();
     void postFrame();

     void print();
     void compute();

  private:

    int objs;
    int num_tr;
    int num_vt;
    int num_pl;
    QPainter painter;
};

#endif
