#ifndef _ALPHABLENDING_H
#define _ALPHABLENDING_H

#include "plugin.h"

class AlphaBlending : public QObject, public Plugin
 {
     Q_OBJECT
     Q_PLUGIN_METADATA(IID "Plugin")
     Q_INTERFACES(Plugin)

 public:
    void preFrame();
    void postFrame();
 };

 #endif
