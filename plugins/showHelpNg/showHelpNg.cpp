#include "showHelpNg.h"
#include "glwidget.h"

void ShowHelpNg::postFrame()
{
  QFont font;
  font.setPixelSize(32);
  painter.begin(glwidget());
  painter.setFont(font);
  int x = 15;
  int y = 40;
  painter.drawText(x, y, QString("L - Load object"
				 "     A - Add plugin"));
  painter.end();
  glwidget()->glBlendFunc(GL_ONE, GL_ZERO);
}
