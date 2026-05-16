#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include <qdialog.h>
#include <qobject.h>
#include <qvariant.h>
#include <qaction.h>
#include <qapplication.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qdialog.h>
#include <qspinbox.h>
#include <qlayout.h>
#include <qgroupbox.h>
#include <qtextedit.h>
#include <qprogressbar.h>
#include <qtooltip.h>
#include <qstringlist.h>
#include <qmessagebox.h>
#include <qinputdialog.h>
#include <qcompleter.h>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

#include <QDesktopServices>
#include <QDir>
#include <QUrl>

enum DlgType { DLG_LABEL, DLG_CHECKBOX, DLG_LINEEDIT, DLG_FLOATEDIT,
  DLG_SPINBOX, DLG_DBLSPINBOX, DLG_MINMAXSPIN,
  DLG_COMBOBOX, DLG_RADIOGRP, DLG_GRPBOX, DLG_COLOR, DLG_TEXTEDIT, DGL_ALL };

enum chkbehav { CB_NONE, CB_DISABLE, CB_ENABLE, CB_HIDE, CB_SHOW };

enum btnset   { BS_CANCEL_OKAY, BS_OKAY_ONLY, BS_NO_YES, BS_CUSTOM };

enum btnbehav { BB_ACCEPT, BB_REJECT, BB_DISABLED, BB_POPUP, BB_OPENURL };

class ColorButton : public QPushButton
{
  Q_OBJECT

public:
  QColor color;
  ColorButton(QColor _color, QWidget *parent=0);
  void setColor(QColor _color);
  QColor getColor();
  public slots:
  void pickColor();

};

struct DialogElement
{
  DlgType type;
  bool    extraChkAdded =false;

  string  *returnString = 0;
  int     *returnInt    = 0;
  int     *returnInt2   = 0;
  bool    *returnBool   = 0;
  float   *returnFloat  = 0;
  QColor  *returnColor  = 0;
  bool    *returnChkExtra = 0;

  bool readOnly  = false;

  QWidget        *wid        = 0;
  QHBoxLayout    *layout     = 0;

  QLabel         *label      = 0;
  QLabel         *label2     = 0;
  QCheckBox      *chkBox     = 0;
  QLineEdit      *lineEdit   = 0;
  QSpinBox       *spnBox     = 0;
  QSpinBox       *spnBox2    = 0;
  QDoubleSpinBox *dblSpnBox  = 0;
  QComboBox      *cmbBox     = 0;
  ColorButton    *btnColor   = 0;
  vector<QRadioButton*> radBtn;
  QGroupBox      *grpBox     = 0;
  QTextEdit      *textEdit   = 0;

  QCheckBox      *chkExtra   = 0;
};

class CustomDialog : public QDialog
{
  Q_OBJECT

public:

  CustomDialog(QString title, QWidget *parent = 0, btnset=BS_CANCEL_OKAY);
  ~CustomDialog() {};
  bool setDialogElements();
  bool wasCancelled();

  bool addCustomButton(QString buttonStr, btnbehav buttonBehav=BB_ACCEPT, QString tooltip="");

  DialogElement& addNewElement(DlgType _type, QString caption, QString tooltip, bool makeLabel);
  int addLabel(QString caption, bool bold=false, QString tooltip="");
  int addHtmlLabel(QString caption, QString tooltip="");
  int addCheckBox(QString caption, bool *checked, QString tooltip="");
  int addLineEdit(QString caption, string *stringValue, QString tooltip="");
  int addReadOnlyLineEdit(QString caption, QString text, QString tooltip="");
  int addLineEditF(QString caption, float min, float max, float *value, float decimals,  QString tooltip="", QString unitsStr="");
  int addSpinBox(QString caption, int min, int max, int *value, int step, QString tooltip="");
  int addDblSpinBoxF(QString caption, float min, float max, float *value, int decimals, float step=0.1, QString tooltip="");
  int addComboBox(QString caption, QString barSepList, int *selIdx, QString tooltip="");
  int addRadioGrp(QString caption, QString barSepList, int *selIdx, QString tooltip="", QString tooltipArr="", bool checkable=false, bool *checked=0);
  int addColorSel(QString caption, QColor *color, QString tooltip="");
  int addMinMaxSpinBoxPair(QString caption, QString middleCaption, int min, int max, int *minValue, int *maxValue, int step=1, QString tooltip="");
  int addTextEdit(string *text, bool richText, bool readOnly, int minHeight=90, QString tooltip="");
  int addReadOnlyTextEdit(QString text, bool richText, int minHeight=90, QString tooltip="");
  int addProgressBar(QString caption, int percent, int width, bool showValue, QString tooltip="");
  int addPercentBar(QString caption, QString valueLabel, float percent, int width, QColor colorBar, QString tooltip="", QFrame::Shape shape = QFrame::StyledPanel, QFrame::Shadow shadow = QFrame::Sunken);
  int addVSpacer(int minHeight=0);

  int beginGroupBox(QString caption, bool flat=false, QString tooltip="", bool checkable=false, bool *checked=0);
  void endGroupBox();

  int addCheckPrev(QString caption, bool *checked, chkbehav chkBeh, bool removeLabel, QString tooltip="");
  int addAutoCompletePrev(QStringList wordList, bool caseSensitive=false);
  bool setStyleElem(int idx, string styleStr, bool bold=false);
  void setStylePrev(string styleStr, bool bold=false);

  bool setEnabledElem(int idx, bool enabled);
  void setEnabledPrev(bool enabled);
  void setEnabledAll(bool enabled);

public:

  vector<DialogElement> elements;

  int customBtnClicked;

private:

  vector<QPushButton*> customBtn;
  QVBoxLayout *vboxLayout;
  QHBoxLayout *hbtnLayout;

  bool addToGroupBox;
  QVBoxLayout *groupBoxLayout;
  QVBoxLayout *layoutNextElement;

public slots:

  void customBtnAccept();
  void customBtnReject();
  void customBtnMessage();
  void customBtnOpenUrl();
  void updateBtnClicked(QObject *btnClicked);
  void resizeMe();
  int exec();
};

void MsgBox(string str);
void MsgBox(QWidget *parent, QString title, QString str);
bool MsgBoxYesNo(QWidget *parent, string str);
string InputBoxString(QWidget *parent, string title, string label, string defaultStr);

inline QString QStr(int number  );
inline QString QStr(long number );
inline QString QStr(float number);
inline QString QStr(double number);
inline string qStringToString(QString qstr);
inline QString nbsp(int numSpaces);
inline void setBold(QWidget *wid, bool bold);
inline void setTextColor(QWidget *wid, int r, int g, int b);
inline void setDefaultColorAndFont(QWidget *wid);
inline void openUrl(QString urlString, bool addFilePrefix=false);

inline QString QStr(int number)     {  return QString::number(number);  }
inline QString QStr(long number)    {  return QString::number(number);  }
inline QString QStr(float number)   {  return QString::number(number);  }
inline QString QStr(double number)  {  return QString::number(number);  }

inline string qStringToString(QString qstr)
{
  string str = "";
  for(int i=0; i<qstr.length(); i++)
    str +=  qstr.at(i).toLatin1();
  return str;
}

inline QString nbsp(int numSpaces)
{
  QString str = "";
  for(int i=0; i<numSpaces; i++)
    str +=  "&nbsp;";
  return str;
}

inline void setBold(QWidget *wid, bool bold)
{
  QFont font;
  font.setBold(bold);
  wid->setFont(font);
}

inline void setTextColor(QWidget *wid, int r, int g, int b)
{
  wid->setStyleSheet("color: rgb(" + QStr(r) + "," + QStr(g) + "," + QStr(b) + ");");
}

inline void setDefaultColorAndFont(QWidget *wid)
{
  wid->setFont(QFont());
  wid->setStyleSheet("color: rgb(0, 0, 0); background-color: rgba(255, 255, 255, 0);");
}

inline void openUrl(QString urlString, bool addFilePrefix)
{
  if(addFilePrefix)
    urlString = "file://" + urlString;
  QDesktopServices::openUrl(QUrl(urlString));
}

#endif
