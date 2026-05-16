#include "customdialog.h"

#include <qstringlist.h>
#include <qvalidator.h>
#include <qcolordialog.h>

using namespace std;

ColorButton::ColorButton(QColor _color, QWidget *parent) : QPushButton(parent)
{
  color = _color;
  this->setStyleSheet("background-color: " + color.name());
  this->setMaximumSize(20,20);
  QObject::connect(this, SIGNAL(clicked()), this, SLOT(pickColor()));
}

void ColorButton::setColor(QColor _color)
{
  color = _color;
  this->setStyleSheet("background-color: " + color.name());
}

QColor ColorButton::getColor()
{
  return (color);
}

void ColorButton::pickColor()
{
  QColor newColor = QColorDialog::getColor(color, this);
  if(newColor.isValid())
  {
    color = newColor;

    this->setStyleSheet("background-color: " + color.name());

    emit released();
  }
}

CustomDialog::CustomDialog(QString title, QWidget *parent, btnset btnSet)
  : QDialog(parent)
{
  setWindowTitle(title);

  QVBoxLayout *vboxLayoutMain = new QVBoxLayout(this);
  vboxLayoutMain->setSpacing(0);
  vboxLayoutMain->setContentsMargins(0, 0, 0, 0);

  vboxLayout = new QVBoxLayout();
  vboxLayout->setSpacing(5);
  vboxLayout->setContentsMargins(9, 6, 9, 9);
  layoutNextElement = vboxLayout;

  hbtnLayout = new QHBoxLayout();
  hbtnLayout->setSpacing(5);
  hbtnLayout->setContentsMargins(8, 8, 8, 8);

  if(btnSet == BS_CANCEL_OKAY)
  {
    addCustomButton("Cancel", BB_REJECT);
    addCustomButton("Okay",   BB_ACCEPT);
  }
  else if(btnSet == BS_OKAY_ONLY)
  {
    addCustomButton("Okay", BB_ACCEPT);
  }
  else if(btnSet == BS_NO_YES)
  {
    addCustomButton("No",  BB_REJECT);
    addCustomButton("Yes", BB_ACCEPT);
  }

  vboxLayoutMain->addLayout(vboxLayout);
  vboxLayoutMain->addLayout(hbtnLayout);

  this->setLayout(vboxLayoutMain);
}

bool CustomDialog::addCustomButton(QString buttonStr, btnbehav buttonBehav,
                                    QString tooltip)
{
  customBtn.push_back(new QPushButton(buttonStr, this));

  QPushButton *newButton = customBtn.back();

  switch (buttonBehav)
  {
    case (BB_ACCEPT):
      QObject::connect(newButton, SIGNAL(clicked()), this, SLOT(customBtnAccept()));
      break;
    case (BB_REJECT):
      QObject::connect(newButton, SIGNAL(clicked()), this, SLOT(customBtnReject()));
      break;
    case (BB_DISABLED):
      newButton->setEnabled(false);
      break;
    case (BB_POPUP):
      QObject::connect(newButton, SIGNAL(clicked()), this, SLOT(customBtnMessage()));
      break;
    case (BB_OPENURL):
      QObject::connect(newButton, SIGNAL(clicked()), this, SLOT(customBtnOpenUrl()));
      break;
  }

  if(!tooltip.isEmpty())
    newButton->setToolTip(tooltip);

  hbtnLayout->addWidget(newButton);

  return true;
}

DialogElement& CustomDialog::addNewElement(DlgType _type, QString caption,
                                            QString tooltip, bool makeLabel)
{
  DialogElement e;
  e.type = _type;
  e.extraChkAdded = false;

  if(makeLabel)
  {
    e.label = new QLabel(caption, this);
    if(!tooltip.isEmpty())
      e.label->setToolTip(tooltip);

  }

  e.layout = new QHBoxLayout();
  e.layout->setSpacing(0);
  e.layout->setContentsMargins(0, 0, 0, 0);

  elements.push_back(e);

  return (elements.back());
}

int CustomDialog::addLabel(QString caption, bool bold, QString tooltip)
{
  DialogElement &e = addNewElement(DLG_LABEL, caption, tooltip, true);

  setBold(e.label, bold);
  e.label->setTextFormat(Qt::PlainText);
  e.layout->addWidget(e.label);

  layoutNextElement->addLayout(e.layout);
  return elements.size();
}

int CustomDialog::addHtmlLabel(QString caption, QString tooltip)
{
  DialogElement &e = addNewElement(DLG_LABEL, caption, tooltip, true);

  e.label->setTextFormat(Qt::RichText);
  e.label->setOpenExternalLinks(true);
  e.layout->addWidget(e.label);

  layoutNextElement->addLayout(e.layout);
  return elements.size();
}

int CustomDialog::addCheckBox(QString caption, bool *checked, QString tooltip)
{
  DialogElement &e = addNewElement(DLG_CHECKBOX, caption, tooltip, false);

  e.returnBool = checked;
  e.chkBox = new QCheckBox(caption, this);
  e.chkBox->setChecked(*checked);
  if(!tooltip.isEmpty())
    e.chkBox->setToolTip(tooltip);

  e.layout->addWidget(e.chkBox);
  layoutNextElement->addLayout(e.layout);

  return elements.size();
}

int CustomDialog::addLineEdit(QString caption, string *stringValue, QString tooltip)
{
  DialogElement &e = addNewElement(DLG_LINEEDIT, caption, tooltip, true);

  e.returnString = stringValue;
  e.lineEdit = new QLineEdit(this);
  e.lineEdit->setText(stringValue->c_str());
  if(!tooltip.isEmpty())
    e.lineEdit->setToolTip(tooltip);

  e.layout->addWidget(e.label);
  e.layout->addWidget(e.lineEdit);
  layoutNextElement->addLayout(e.layout);
  return elements.size();
}

int CustomDialog::addReadOnlyLineEdit(QString caption, QString text, QString tooltip)
{
  DialogElement &e = addNewElement(DLG_LABEL, caption, tooltip, true);

  e.lineEdit = new QLineEdit(this);
  e.lineEdit->setText(text);
  e.lineEdit->setReadOnly(true);
  if(!tooltip.isEmpty())
    e.lineEdit->setToolTip(tooltip);

  e.layout->addWidget(e.label);
  e.layout->addWidget(e.lineEdit);
  layoutNextElement->addLayout(e.layout);
  return elements.size();
}

int CustomDialog::addLineEditF(QString caption, float min, float max, float *value,
                                float decimals, QString tooltip, QString unitsStr)
{
  DialogElement &e = addNewElement(DLG_FLOATEDIT, caption, tooltip, true);

  e.returnFloat = value;
  e.lineEdit = new QLineEdit(this);
  e.lineEdit->setText(QString::number(*value));
  e.lineEdit->setMaximumWidth(100);
  if(!tooltip.isEmpty())
    e.lineEdit->setToolTip(tooltip);
  e.lineEdit->setValidator(new QDoubleValidator(min, max,
                           decimals, e.lineEdit));

  QSpacerItem *sp = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
  e.layout->addWidget(e.label);
  e.layout->addItem(sp);
  e.layout->addWidget(e.lineEdit);

  if(!unitsStr.isEmpty())
  {
    e.label2 = new QLabel(unitsStr,this);
    e.layout->addWidget(e.label2);
  }

  layoutNextElement->addLayout(e.layout);
  return elements.size();
}

int CustomDialog::addSpinBox(QString caption, int min, int max, int *value, int step,
                              QString tooltip)
{
  DialogElement &e = addNewElement(DLG_SPINBOX, caption, tooltip, true);

  e.returnInt = value;
  e.spnBox = new QSpinBox(this);
  e.spnBox->setRange     (min, max);
  e.spnBox->setValue     (*value);
  e.spnBox->setSingleStep(step);
  if(!tooltip.isEmpty())
    e.spnBox->setToolTip(tooltip);

  QSpacerItem *sp = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
  e.layout->addWidget(e.label);
  e.layout->addItem(sp);
  e.layout->addWidget(e.spnBox);
  layoutNextElement->addLayout(e.layout);

  return elements.size();
}

int CustomDialog::addDblSpinBoxF(QString caption, float min, float max, float *value,
                                  int decimals, float step, QString tooltip)
{
  DialogElement &e = addNewElement(DLG_DBLSPINBOX, caption, tooltip, true);

  e.returnFloat = value;

  e.dblSpnBox = new QDoubleSpinBox(this);
  e.dblSpnBox->setRange(min, max);
  e.dblSpnBox->setValue     (*value);
  e.dblSpnBox->setSingleStep(step);
  e.dblSpnBox->setDecimals  (decimals);
  if(!tooltip.isEmpty())
    e.dblSpnBox->setToolTip(tooltip);

  QSpacerItem *sp = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
  e.layout->addWidget(e.label);
  e.layout->addItem(sp);
  e.layout->addWidget(e.dblSpnBox);
  layoutNextElement->addLayout(e.layout);
  return elements.size();
}

int CustomDialog::addComboBox(QString caption, QString barSepList, int *selIdx,
                               QString tooltip)
{
  DialogElement &e = addNewElement(DLG_COMBOBOX, caption, tooltip, true);

  e.returnInt = selIdx;
  e.cmbBox = new QComboBox(this);
  QStringList items = barSepList.split("|", Qt::SkipEmptyParts);

  e.cmbBox->addItems(items);
  if(*selIdx < (int)items.size())
    e.cmbBox->setCurrentIndex(*selIdx);
  if(!tooltip.isEmpty())
    e.cmbBox->setToolTip(tooltip);

  e.layout->addWidget(e.label);
  e.layout->addWidget(e.cmbBox);
  layoutNextElement->addLayout(e.layout);
  return elements.size();
}

int CustomDialog::addRadioGrp(QString caption, QString barSepList, int *selIdx,
                               QString tooltip, QString tooltipArr, bool checkable, bool *checked)
{
  DialogElement &e = addNewElement(DLG_RADIOGRP, caption, tooltip, false);

  e.returnInt = selIdx;
  e.grpBox = new QGroupBox(this);
  e.grpBox->setTitle(caption);
  if(checkable)
  {
    e.returnBool = checked;
    e.grpBox->setCheckable(*checked);
  }
  QButtonGroup *butGrp = new QButtonGroup(this);
  QVBoxLayout  *butLay = new QVBoxLayout(e.grpBox);
  butLay->setSpacing(2);
  butLay->setContentsMargins(5, 2, 5, 5);
  QStringList items = barSepList.split(
      "|",Qt::SkipEmptyParts);

  QStringList tooltips;
  if(!tooltipArr.isEmpty())
    tooltips = tooltipArr.split("|", Qt::SkipEmptyParts);

  for (int j=0; j<(int)items.size(); j++)
  {
    QRadioButton *newRadBtn = new QRadioButton(e.grpBox);
    butLay->addWidget(newRadBtn);
    butGrp->addButton(newRadBtn, j);
    newRadBtn->setText(items[j]);
    if(j == *selIdx)
      newRadBtn->setChecked(true);
    if(j<(int)tooltips.size())
      newRadBtn->setToolTip(tooltips[j]);
    e.radBtn.push_back(newRadBtn);
  }

  if(!tooltip.isEmpty())
    e.grpBox->setToolTip(tooltip);

  e.layout->addWidget(e.grpBox);
  layoutNextElement->addLayout(e.layout);
  return elements.size();
}

int CustomDialog::addColorSel(QString caption, QColor *color, QString tooltip)
{
  DialogElement &e = addNewElement(DLG_COLOR, caption, tooltip, true);

  e.returnColor = color;
  e.btnColor = new ColorButton(*color,this);
  if(!tooltip.isEmpty())
    e.btnColor->setToolTip(tooltip);

  QSpacerItem *sp = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
  e.layout->addWidget(e.label);
  e.layout->addItem(sp);
  e.layout->addWidget(e.btnColor);
  layoutNextElement->addLayout(e.layout);

  return elements.size();
}

int CustomDialog::addMinMaxSpinBoxPair(QString caption, QString middleCaption,
                                       int min, int max,
                                       int *minValue, int *maxValue, int step,
                                       QString tooltip)
{
  DialogElement &e = addNewElement(DLG_MINMAXSPIN, caption, tooltip, true);

  e.returnInt = minValue;
  e.spnBox = new QSpinBox(this);
  e.spnBox->setRange     (min, max);
  e.spnBox->setValue     (*minValue);
  e.spnBox->setSingleStep(step);

  e.returnInt2 = maxValue;
  e.spnBox2 = new QSpinBox(this);
  e.spnBox2->setRange     (min, max);
  e.spnBox2->setValue     (*maxValue);
  e.spnBox2->setSingleStep(step);

  e.label2 = new QLabel(middleCaption,this);

  if(!tooltip.isEmpty())
  {
    e.spnBox->setToolTip(tooltip);
    e.spnBox2->setToolTip(tooltip);
    e.label2->setToolTip(tooltip);
  }

  QSpacerItem *sp = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);

  e.layout->addWidget(e.label);
  e.layout->addItem(sp);
  e.layout->addWidget(e.spnBox);
  e.layout->addWidget(e.label2);
  e.layout->addWidget(e.spnBox2);
  layoutNextElement->addLayout(e.layout);

  return elements.size();
}

int CustomDialog::addTextEdit(string *text, bool richText, bool readOnly,
                               int minHeight, QString tooltip)
{
  DialogElement &e = addNewElement(DLG_TEXTEDIT, "", tooltip, false);

  e.returnString = text;
  e.textEdit = new QTextEdit(this);
  e.textEdit->setAcceptRichText(richText);
  if(richText)
    e.textEdit->setHtml(text->c_str());
  else
    e.textEdit->setPlainText(text->c_str());

  if(!tooltip.isEmpty())
    e.textEdit->setToolTip(tooltip);
  e.textEdit->setReadOnly(readOnly);
  e.textEdit->setMinimumHeight(minHeight);

  e.layout->addWidget(e.textEdit);
  layoutNextElement->addLayout(e.layout);
  return elements.size();
}

int CustomDialog::addReadOnlyTextEdit(QString text, bool richText,
                                       int minHeight, QString tooltip)
{
  DialogElement &e = addNewElement(DLG_TEXTEDIT, "", tooltip, false);

  e.textEdit = new QTextEdit(this);
  e.textEdit->setAcceptRichText(richText);
  if(richText)
    e.textEdit->setHtml(text);
  else
    e.textEdit->setPlainText(text);

  if(!tooltip.isEmpty())
    e.textEdit->setToolTip(tooltip);
  e.textEdit->setReadOnly(true);
  e.textEdit->setMinimumHeight(minHeight);

  e.layout->addWidget(e.textEdit);
  layoutNextElement->addLayout(e.layout);
  return elements.size();
}

int CustomDialog::addProgressBar(QString caption, int percent,
                                  int width, bool showValue, QString tooltip)
{
  DialogElement &e = addNewElement(DLG_LABEL, caption, tooltip, true);

  QProgressBar *progBar = new QProgressBar(this);
  progBar->setMinimum(0);
  progBar->setMaximum(100);
  progBar->setValue(percent);
  progBar->setFixedWidth(width);
  if(showValue)
    progBar->setStyleSheet("color: rgb(0,0,0);");
  if(!tooltip.isEmpty())
    progBar->setToolTip(tooltip);

  QSpacerItem *sp = new QSpacerItem(10,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
  e.layout->addWidget(e.label);
  e.layout->addItem(sp);
  e.layout->addWidget(progBar);
  layoutNextElement->addLayout(e.layout);
  return elements.size();
}

int CustomDialog::addPercentBar(QString caption, QString valueLabel, float fraction,
                                 int width, QColor colorBar, QString tooltip,
                                 QFrame::Shape shape, QFrame::Shadow shadow)
{
  DialogElement &e = addNewElement(DLG_LABEL, caption, tooltip, true);

  QSpacerItem *sp = new QSpacerItem(10,20,QSizePolicy::Expanding,QSizePolicy::Minimum);

  e.label2 = new QLabel(valueLabel,this);

  QSpacerItem *sp2 = new QSpacerItem(10,20,QSizePolicy::Minimum,QSizePolicy::Minimum);

  int widthLine1 = (int)(fraction * (float)width);
  int widthLine2 = width - widthLine1;

  QFrame *fraBar = new QFrame(this);
  fraBar->setFrameShape(shape);
  fraBar->setFrameShadow(shadow);

  QHBoxLayout *layLines = new QHBoxLayout();
  layLines->setSpacing(0);
  layLines->setContentsMargins(0, 0, 0, 0);
  fraBar->setLayout(layLines);

  QFrame *line1 = new QFrame(this);
  line1->setObjectName(QString::fromUtf8("line1"));
  line1->setFixedWidth(widthLine1);
  line1->setMinimumHeight(18);
  line1->setFrameShape(QFrame::HLine);
  line1->setFrameShadow(QFrame::Plain);
  line1->setLineWidth(15);
  line1->setStyleSheet("color: " + colorBar.name() + ";");
  layLines->addWidget(line1);

  QFrame *line2 = new QFrame(this);
  line2->setObjectName(QString::fromUtf8("line1"));
  line2->setFixedWidth(widthLine2);
  line2->setMinimumHeight(18);
  line2->setLineWidth(15);
  line2->setFrameShape(QFrame::HLine);
  line2->setFrameShadow(QFrame::Plain);
  line2->setStyleSheet("color: rgb(255,255,255,80);");
  layLines->addWidget(line2);

  if(!tooltip.isEmpty())
  {
    line1->setToolTip(tooltip);
    line2->setToolTip(tooltip);
  }

  e.layout->addWidget(e.label);
  e.layout->addItem(sp);
  e.layout->addWidget(e.label2);
  e.layout->addItem(sp2);

  e.layout->addWidget(fraBar);
  layoutNextElement->addLayout(e.layout);
  return elements.size();
}

int CustomDialog::addVSpacer(int minHeight)
{
  QSpacerItem *sp = new QSpacerItem(0, minHeight,
                                    QSizePolicy::Minimum, QSizePolicy::Expanding);

  layoutNextElement->addItem(sp);
  return elements.size();
}

int CustomDialog::beginGroupBox(QString caption, bool flat, QString tooltip,
                                bool checkable, bool *checked)
{
  DialogElement &e = addNewElement(DLG_GRPBOX, caption, tooltip, false);

  e.grpBox = new QGroupBox(this);
  e.grpBox->setTitle(caption);
  e.grpBox->setFlat(flat);
  if(checkable)
  {
    e.returnBool = checked;
    e.grpBox->setCheckable(*checked);
  }

  groupBoxLayout = new QVBoxLayout(e.grpBox);
  groupBoxLayout->setSpacing(2);
  groupBoxLayout->setContentsMargins(8, 12, 5, 5);
  if(!tooltip.isEmpty())
    e.grpBox->setToolTip(tooltip);

  e.layout->addWidget(e.grpBox);
  layoutNextElement->addLayout(e.layout);

  layoutNextElement = groupBoxLayout;

  return elements.size();
}

void CustomDialog::endGroupBox()
{
  layoutNextElement = vboxLayout;
}

int CustomDialog::addCheckPrev(QString caption, bool *checked,
                                chkbehav chkBehav, bool removeLabel, QString tooltip)
{
  DialogElement &e = elements.back();
  e.extraChkAdded = true;

  e.returnChkExtra = checked;
  e.chkExtra = new QCheckBox(caption, this);
  e.chkExtra->setChecked(*checked);
  if(!tooltip.isEmpty())
    e.chkExtra->setToolTip(tooltip);

  int insertPos = 1;
  if(!removeLabel && (e.type==DLG_SPINBOX  || e.type==DLG_DBLSPINBOX
                      || e.type==DLG_MINMAXSPIN || e.type==DLG_COLOR
                      || e.type==DLG_FLOATEDIT))
    insertPos = 2;
  if(e.type==DLG_RADIOGRP || e.type==DLG_GRPBOX)
    vboxLayout->insertWidget(vboxLayout->count()-1, e.chkExtra);
  else
    e.layout->insertWidget(insertPos, e.chkExtra);

  if(removeLabel && e.label)
  {
    e.layout->removeWidget(e.label);
    e.label->setParent(0);
  }

  QWidget *wid=0;

  switch(e.type)
  {
  case(DLG_LABEL):      wid = e.label;      break;
  case(DLG_CHECKBOX):   wid = e.chkBox;     break;
  case(DLG_LINEEDIT):   wid = e.lineEdit;   break;
  case(DLG_FLOATEDIT):  wid = e.lineEdit;   break;
  case(DLG_SPINBOX):    wid = e.spnBox;     break;
  case(DLG_DBLSPINBOX): wid = e.dblSpnBox;  break;
  case(DLG_COMBOBOX):   wid = e.cmbBox;     break;
  case(DLG_RADIOGRP):   wid = e.grpBox;     break;
  case(DLG_GRPBOX):     wid = e.grpBox;     break;
  case(DLG_COLOR):      wid = e.btnColor;   break;
  case(DLG_TEXTEDIT):   wid = e.textEdit;   break;
  default: ;
  }

  switch(chkBehav)
  {
  case(CB_NONE): break;
  case(CB_ENABLE):
    wid->setEnabled(*checked);
    e.chkExtra->connect(e.chkExtra, SIGNAL(clicked(bool)), wid, SLOT(setEnabled(bool)));
    break;
  case(CB_DISABLE):
    wid->setDisabled(*checked);
    e.chkExtra->connect(e.chkExtra, SIGNAL(clicked(bool)), wid, SLOT(setDisabled(bool)));
    break;
  case(CB_SHOW):
    wid->setVisible(*checked);
    e.chkExtra->connect(e.chkExtra, SIGNAL(clicked(bool)), wid, SLOT(setVisible(bool)));
    e.chkExtra->connect(this, SIGNAL(clicked(bool)), wid, SLOT(reize()));
    connect(e.chkExtra, SIGNAL(clicked()), this, SLOT(resizeMe()));
    break;
  case(CB_HIDE):
    wid->setHidden(*checked);
    e.chkExtra->connect(e.chkExtra, SIGNAL(clicked(bool)), wid, SLOT(setHidden(bool)));
    e.chkExtra->connect(this, SIGNAL(clicked(bool)), wid, SLOT(reize()));
    connect(e.chkExtra, SIGNAL(clicked()), this, SLOT(resizeMe()));
    break;
  }

  return elements.size();
}

int CustomDialog::addAutoCompletePrev(QStringList wordList, bool caseSensitive)
{
  DialogElement &e = elements.back();
  if (e.type != DLG_LINEEDIT)
  {
    cerr << "ERROR: addAutoCompletePrev() must proceed addLineEdit()" << endl;
    return 01;
  }

  QCompleter *completer = new QCompleter(wordList, this);
  if(caseSensitive)
    completer->setCaseSensitivity(Qt::CaseSensitive);
  else
    completer->setCaseSensitivity(Qt::CaseInsensitive);
  e.lineEdit->setCompleter(completer);

  return elements.size();
}

bool CustomDialog::setStyleElem(int idx, string styleStr, bool )
{
  if(idx >= int(elements.size()) || idx < 0)
    return false;

  DialogElement &e = elements[idx];
  QString styleQStr = (QString)styleStr.c_str();

  if(e.extraChkAdded)
    e.chkExtra->setStyleSheet(styleQStr);

  if(e.type == DLG_LABEL || e.type == DLG_LINEEDIT || e.type == DLG_FLOATEDIT
     || e.type == DLG_SPINBOX || e.type == DLG_DBLSPINBOX || e.type == DLG_COMBOBOX
     || e.type == DLG_COLOR)
    e.label->setStyleSheet(styleQStr);

  switch (e.type)
  {
    case(DLG_CHECKBOX  ):    e.chkBox->setStyleSheet(styleQStr);     break;
    case(DLG_LINEEDIT  ):
    case(DLG_FLOATEDIT ):    e.lineEdit->setStyleSheet(styleQStr);   break;
    case(DLG_SPINBOX   ):    e.spnBox->setStyleSheet(styleQStr);     break;
    case(DLG_DBLSPINBOX):    e.dblSpnBox->setStyleSheet(styleQStr);  break;
    case(DLG_COMBOBOX  ):    e.cmbBox->setStyleSheet(styleQStr);     break;
    case(DLG_RADIOGRP  ):
    {
      for(int i=0; i<(int)e.radBtn.size(); i++)
        e.radBtn[i]->setStyleSheet(styleQStr);
    } break;
    case(DLG_COLOR     ):    break;
    case(DLG_GRPBOX    ):    e.grpBox->setStyleSheet(styleQStr);     break;
    case(DLG_TEXTEDIT  ):    e.textEdit->setStyleSheet(styleQStr);     break;
  default: ;
  }

  return true;
}

void CustomDialog::setStylePrev(string styleStr, bool bold)
{
  setStyleElem(elements.size()-1, styleStr, bold);
}

bool CustomDialog::setEnabledElem(int idx, bool enabled)
{
  if(idx >= int(elements.size()) || idx < 0)
    return false;

  DialogElement &e = elements[idx];
  e.layout->setEnabled(enabled);
    return true;
}

void CustomDialog::setEnabledPrev(bool enabled)
{
  setEnabledElem(elements.size()-1, enabled);
}

void CustomDialog::setEnabledAll(bool enabled)
{
  for(int i=0; i<(int)elements.size(); i++)
    setEnabledElem(i, enabled);
}

void CustomDialog::resizeMe()
{
  this->resize(20,20);
  adjustSize();
}

void CustomDialog::customBtnAccept()
{
  updateBtnClicked(QObject::sender());

  for(int i = 0; i<(int)elements.size(); i++)
  {
    DialogElement &e = elements[i];

    if(e.extraChkAdded)
      *e.returnChkExtra = e.chkExtra->isChecked();

    switch (e.type)
    {
    case(DLG_LABEL): break;
    case(DLG_CHECKBOX):
      *e.returnBool = e.chkBox->isChecked();
      break;

    case(DLG_LINEEDIT):
      *e.returnString = e.lineEdit->text().toStdString();
      break;

    case(DLG_FLOATEDIT):
      *e.returnFloat = e.lineEdit->text().toFloat();
      break;

    case(DLG_SPINBOX):
      *e.returnInt = (int)e.spnBox->value();
      break;

    case(DLG_DBLSPINBOX):
      *e.returnFloat = (float)e.dblSpnBox->value();
      break;

    case(DLG_COMBOBOX):
      *e.returnInt = (double)e.cmbBox->currentIndex();
      break;

    case(DLG_RADIOGRP):
      {
        *e.returnInt = 0;
        for(int j=0; j<(int)e.radBtn.size(); j++)
          if(e.radBtn[j]->isChecked())
            *e.returnInt = j;
        if(e.grpBox->isCheckable())
          *e.returnInt = e.grpBox->isChecked();
      }
      break;

    case(DLG_COLOR):
      *e.returnColor = e.btnColor->color;
      break;

    case(DLG_MINMAXSPIN):
        *e.returnInt = (int)e.spnBox->value();
        *e.returnInt2 = (int)e.spnBox2->value();
        break;

    case(DLG_GRPBOX):
      if(e.grpBox->isCheckable())
        *e.returnInt = e.grpBox->isChecked();
      break;

    case(DLG_TEXTEDIT):
      if(e.textEdit->isReadOnly() == false)
        *e.returnString = e.textEdit->toPlainText().toStdString();
      break;

  default: ;
    }

  }

  QDialog::accept();
}

void CustomDialog::customBtnReject()
{
  updateBtnClicked(QObject::sender());
  QDialog::reject();
}

void CustomDialog::updateBtnClicked(QObject* btnClicked)
{
  customBtnClicked = -1;
  for(int i=0; i<(int)customBtn.size(); i++)
    if(btnClicked==customBtn[i])
      customBtnClicked = i;
}

void CustomDialog::customBtnMessage()
{
  for(int i=0; i<(int)customBtn.size(); i++)
    if(QObject::sender()==customBtn[i])
      MsgBox(customBtn[i], "...", customBtn[i]->toolTip());
}

void CustomDialog::customBtnOpenUrl()
{
  for(int i=0; i<(int)customBtn.size(); i++)
    if(QObject::sender()==customBtn[i])
      openUrl(customBtn[i]->toolTip());
}

int CustomDialog::exec()
{
  adjustSize();
  return QDialog::exec();
}

bool CustomDialog::wasCancelled()
{
  return (result() == QDialog::Rejected);
}

void MsgBox(string str)
{
  QMessageBox::information(0, "...", str.c_str());
}

void MsgBox(QWidget *parent, QString title, QString str)
{
  QMessageBox::information(parent, title, str);
}

bool MsgBoxYesNo(QWidget *parent, string str)
{
  int result = QMessageBox::information(parent, "...", str.c_str(),
                                        QMessageBox::Yes, QMessageBox::No);
  return (result == QMessageBox::Yes);
}

string InputBoxString(QWidget *parent, string title, string label, string defaultStr)
{
  return qStringToString(QInputDialog::getText(parent, title.c_str(), label.c_str(),
                                               QLineEdit::Normal, defaultStr.c_str()));
}
