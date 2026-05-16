#include "ModelInfo.h"
#include "glwidget.h"

void ModelInfo::compute()
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

void ModelInfo::print()
{

    cout << "Objetos en escena: " << objs << endl;
    cout << "Número de polígonos: " << num_pl << endl;
    cout << "Número de vértices: " << num_vt << endl;
    cout << "Número de triángulos: " << num_tr << endl;

    cout << "Porcentaje de triángulos/Polígonos: " << (num_tr*100)/num_pl << "%" << endl;
}

void ModelInfo::onPluginLoad()
{
    compute();
}

void ModelInfo::preFrame()
{

}

void ModelInfo::postFrame()
{
    print();
}

void ModelInfo::onObjectAdd()
{

}

bool ModelInfo::drawScene()
{
    return false;
}

bool ModelInfo::drawObject(int)
{
    return false;
}

bool ModelInfo::paintGL()
{
    return false;
}

void ModelInfo::keyPressEvent(QKeyEvent *)
{

}

void ModelInfo::mouseMoveEvent(QMouseEvent *)
{

}
