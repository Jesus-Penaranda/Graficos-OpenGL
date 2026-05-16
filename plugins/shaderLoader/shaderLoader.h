#ifndef _SHADERLOADER_H
#define _SHADERLOADER_H

#include "plugin.h"
#include "glwidget.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLFramebufferObjectFormat>
#include <QDateTime>
#include <QElapsedTimer>
#include <QWidget>
#include <map>
using namespace std;

class ShaderLoader : public QObject, public Plugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "Plugin")
    Q_INTERFACES(Plugin)

    public:
  ShaderLoader();
  ~ShaderLoader();
  void onPluginLoad();
  bool paintGL();
  void keyPressEvent(QKeyEvent*);
  void createDefaultShaders(bool createAlsoGS);

  public slots:
    void createDefaultShadersVSFS();
    void createDefaultShadersVSGSFS();

    void createShaderFromTemplate();

    void attachShaders();
    void attachShaders(QString name);
    void openFilesInTextEditor();
    void switchStatusVS();
    void switchStatusGS();
    void switchStatusFS();
    void switchStatusWireframe();
    void switchStatusShowAxes();
    void switchStatusShowLight();

    void resetCamera();
    void cameraPreset1();
    void cameraPreset2();
    void cameraPreset3();
    void cameraPreset4();
    void cameraPreset5();

    void loadObject();
    void loadObject(const QString& file);

    void changeBackgroundColor();
    void loadTexture0();
    void loadTexture1();
    void loadTexture2();
    void loadTexture3();
    void showTextures();

    void setLightAmbient();
    void setLightDiffuse();
    void setLightSpecular();
    void setLightPositionWorld();
    void setLightPositionEye();
    void resetLightPosition();
    void switchLightRotate();

    void setMaterialAmbient();
    void setMaterialDiffuse();
    void setMaterialSpecular();

    void editUniform(int id);
    void uniformMult(bool up);

    QString executeTest();
    void compareTest();

 private:

    void loadTexture(int unit, QString filename=QString());
    void drawHelp();

    void reloadShaders();
    void checkForUpdates();
    void showMenu(const QPoint&);

    bool isPredefinedUniform(QString name);
    void uniformValueToString(int id, QString& value, QString& typeName);

    bool showHelp;

    bool testMode;
    vector<QString> testUniformIntNames;
    vector<QString> testUniformFloatNames;
    vector<QString> testUniformBoolNames;
    vector<QString> testUniformvec2Names;
    vector<int> testUniformIntValues;
    vector<float> testUniformFloatValues;
    vector<bool> testUniformBoolValues;
    vector<QVector2D> testUniformvec2Values;

    QString filename;
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* gs;
    QOpenGLShader* fs;

    bool enabled_vs;
    bool enabled_gs;
    bool enabled_fs;

    bool wireframe;
    bool showAxes;
    bool showLight;

    Vector backgroundColor;

    Vector lightAmbient;
    Vector lightDiffuse;
    Vector lightSpecular;
    QVector4D lightPosition;
    bool lightEncodedInEyeSpace;
    bool lightRotate;

    Vector materialAmbient;
    Vector materialDiffuse;
    Vector materialSpecular;
    float materialShininess;

    GLuint textureID[4];
    QString textureName[4];

    QDateTime lastModifiedVS;
    QDateTime lastModifiedGS;
    QDateTime lastModifiedFS;

    QElapsedTimer elapsedTimer;
    QTimer timer;

    vector<QString> predefinedUniforms;
    int activeUniform;

    bool grading;
    string gradeShader;

    bool doPopup;

    QOpenGLFramebufferObjectFormat fboFormat;
  };

#endif
