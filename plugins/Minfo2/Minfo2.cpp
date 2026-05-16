#include "Minfo2.h"
#include "glwidget.h"

void Minfo2::compute()
{

    const vector<Object>& objetos = scene()->objects();
    objs = int(objetos.size());

    num_tr = 0;
    num_vt = 0;
    num_pl = 0;

    for (int i = 0; i < int(objetos.size()); ++i)
    {
        const vector<Face>& caras = objetos[i].faces();

        for (int j = 0; j < int(caras.size()); ++j)
        {
            int vert = caras[j].numVertices();
            num_vt += vert;
            if (vert == 3) ++num_tr;
            ++num_pl;
        }
    }
}

void Minfo2::print()
{

    QFont font;
    font.setPixelSize(24);

    painter.begin(glwidget());

    glwidget()->glDisable(GL_DEPTH_TEST);

    painter.setFont(font);
    painter.setPen(Qt::black);

    int x = 15;
    int y = 40;

    painter.drawText(x, y, QString("Objetos en escena: %1").arg(objs));
    y += 35;

    painter.drawText(x, y, QString("Número de polígonos: %1").arg(num_pl));
    y += 35;

    painter.drawText(x, y, QString("Número de vértices: %1").arg(num_vt));
    y += 35;

    painter.drawText(x, y, QString("Número de triángulos: %1").arg(num_tr));
    y += 35;

    painter.drawText(x, y, QString("Porcentaje de triángulos/Polígonos: %1%").arg((num_tr*100)/num_pl));

    painter.end();

    glwidget()->glEnable(GL_DEPTH_TEST);

    glwidget()->glBlendFunc(GL_ONE, GL_ZERO);
}

void Minfo2::onPluginLoad()
{
    compute();
}

void Minfo2::preFrame()
{

}

void Minfo2::postFrame()
{
    print();
}
