#ifndef _PluginLoader_H
#define _PluginLoader_H

#include "plugin.h"
#include "glwidget.h"
#include <QDateTime>

using namespace std;

class PluginLoader : public QObject, public Plugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "Plugin")
  Q_INTERFACES(Plugin)

 public:
  PluginLoader();
  void onPluginLoad();
  void postFrame();
  void keyPressEvent(QKeyEvent*);

 public slots:
   void createDefaultPlugin();
   void createPluginFromTemplate();
   void attachPlugin();
   void attachPlugin(QString name);
   void openFilesInTextEditor();

   void resetCamera();
   void cameraPreset1();
   void cameraPreset2();
   void cameraPreset3();
   void cameraPreset4();
   void cameraPreset5();

   void loadObject();
   void loadObject(const QString& file);

 private:

   int  currentPlugin;
   void reloadPlugin();
   void checkForUpdates();
   void showMenu(const QPoint&);

   QString filename;
   bool pluginEnabled;
   int pluginVersion;

   QDateTime lastModifiedH;
   QDateTime lastModifiedCPP;

   QTimer timer;
   QString origCWD;
   QString qmakePath;
   qint64 graceTime;
};

#endif
