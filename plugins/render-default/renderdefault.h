#ifndef _RENDERDEFAULT_H
#define _RENDERDEFAULT_H

#include "plugin.h"

 class RenderDefault : public QObject, public Plugin
 {
     Q_OBJECT
     Q_PLUGIN_METADATA(IID "Plugin")
     Q_INTERFACES(Plugin)

 public:
     bool paintGL();
 };

#endif
