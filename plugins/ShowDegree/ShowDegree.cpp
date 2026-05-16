#include "ShowDegree.h"
#include "glwidget.h"

void ShowDegree::onPluginLoad()
{
	media = averageDegree(scene() -> objects()[0]);
}

float ShowDegree::averageDegree(const Object & object)
{
	int n_v = object.vertices().size();
	int tot = 0;
	for (const Face & face : object.faces()) tot += face.numVertices();
	return double(tot)/ n_v;
}

void ShowDegree::print()
{

	QFont font;
	font.setPixelSize(24);

	painter.begin(glwidget());
	painter.setFont(font);

	int x = 15;
	int y = 40;

	painter.drawText(x, y, QString("Grado medio vértices: %1").arg(media));

	painter.end();
	glwidget()->glBlendFunc(GL_ONE, GL_ZERO);
}

void ShowDegree::preFrame()
{

}

void ShowDegree::postFrame()
{
	print();
}

void ShowDegree::onObjectAdd()
{

}

bool ShowDegree::drawScene()
{
	return false;
}

bool ShowDegree::drawObject(int)
{
	return false;
}

bool ShowDegree::paintGL()
{
	return false;
}

void ShowDegree::keyPressEvent(QKeyEvent *)
{

}

void ShowDegree::mouseMoveEvent(QMouseEvent *)
{

}
