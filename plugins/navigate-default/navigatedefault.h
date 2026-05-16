#ifndef _NAVIGATEDEFAULT_H
#define _NAVIGATEDEFAULT_H

#include "plugin.h"

class NavigateDefault : public QWidget, public Plugin
 {
     Q_OBJECT
     Q_PLUGIN_METADATA(IID "Plugin")
     Q_INTERFACES(Plugin)

 public:
    NavigateDefault();

    void	keyPressEvent ( QKeyEvent *  ) {};
    void	keyReleaseEvent ( QKeyEvent *  ) {};

    void	mouseMoveEvent ( QMouseEvent * event );
    void	mousePressEvent ( QMouseEvent * event );
    void	mouseReleaseEvent ( QMouseEvent * event );
    void	wheelEvent ( QWheelEvent *  ) {};

 private:
    typedef  enum {NONE, ROTATE, ZOOM, PAN} MouseAction;
    MouseAction pmouseAction;
    int   pxClick, pyClick;
 };

#endif
