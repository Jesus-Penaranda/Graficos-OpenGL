#ifndef _SHOWHELPNG_H
#define _SHOWHELPNG_H

#include "plugin.h"
#include <QPainter>

class ShowHelpNg : public QObject, Plugin
 {
     Q_OBJECT
     Q_PLUGIN_METADATA(IID "Plugin")
     Q_INTERFACES(Plugin)

 public:
    void postFrame() Q_DECL_OVERRIDE;
 private:
    QPainter painter;
 };

#endif
