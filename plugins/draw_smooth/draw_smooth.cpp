#include "draw_smooth.h"
#include "glwidget.h"
#include <cassert>
#include <cmath>

Draw_smooth::~Draw_smooth()
{
    cleanUp();
}

void Draw_smooth::onSceneClear()
{
    cleanUp();
}

bool Draw_smooth::drawObject(int i)
{
    GLWidget &g = *glwidget();
    g.makeCurrent();
    g.glBindVertexArray(VAOs[i]);
    if (useIndices)
    {

        g.glDrawElements(GL_TRIANGLES, numElements[i], GL_UNSIGNED_INT, (GLvoid*)0);
    }
    else
    {
        g.glDrawArrays(GL_TRIANGLES, 0, numElements[i]);
    }
    g.glBindVertexArray(0);
    return true;
}

bool Draw_smooth::drawScene()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();
    for (unsigned int i=0; i < VAOs.size(); i++)
    {
        drawObject(i);
    }
    return true;
}

void Draw_smooth::onPluginLoad()
{
    for (unsigned int i=0; i<scene()->objects().size(); i++)
    {
        addVBO(i);
    }
}

void Draw_smooth::onObjectAdd()
{
    addVBO(scene()->objects().size() - 1);
}

void Draw_smooth::postFrame()
{
    QFont font;
    font.setPixelSize(32);
    painter.begin(glwidget());
    painter.setFont(font);
    int x = 15;
    int y = 40;
    painter.drawText(x, y, QString(useIndices ? "Drawing with indices" : "Drawing with duplicated vertices"));
    painter.end();
}

void Draw_smooth::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_E)
    {

        useIndices = !useIndices;
        cleanUp();
        onPluginLoad();
    }
}

void Draw_smooth::addVBO(unsigned int currentObject)
{

    const Object& obj = scene()->objects()[currentObject];
    vector<float> vertices;
    vector<float> normals;
    vector<float> colors;
    vector<float> texCoords;
    vector<unsigned int> indices;
    const vector<Vertex>& verts = obj.vertices();
    const vector<Vector>& Ns = obj.vertNormals();
    const vector<pair<float, float>>& texcords = obj.vertTexCoords();

    if (useIndices)
    {

        for (unsigned int i = 0; i < verts.size(); i++)
        {

            vertices.push_back(verts[i].coord().x());
            vertices.push_back(verts[i].coord().y());
            vertices.push_back(verts[i].coord().z());
            normals.push_back(Ns[i].x());
            normals.push_back(Ns[i].y());
            normals.push_back(Ns[i].z());
            texCoords.push_back(texcords[i].first);
            texCoords.push_back(texcords[i].second);
            colors.push_back(0.8f);
            colors.push_back(0.8f);
            colors.push_back(0.8f);
        }
        for (auto&& f: obj.faces())
        {

            for (int j = 0; j < f.numVertices(); j++)
            {
                indices.push_back(f.vertexIndex(j));
            }
        }
    }
    else
    {

        for (auto&& f: obj.faces())
        {

            auto pushVertex = [&](int vertexIdx, Vector normal_media, int tcIdx)
            {
                const Vertex v = verts[vertexIdx];
                const pair<float, float> TC = texcords[tcIdx];

                Point P = v.coord();
                vertices.push_back(P.x());
                vertices.push_back(P.y());
                vertices.push_back(P.z());

                normals.push_back(normal_media.x());
                normals.push_back(normal_media.y());
                normals.push_back(normal_media.z());

                colors.push_back(fabs(normal_media.x()));
                colors.push_back(fabs(normal_media.y()));
                colors.push_back(fabs(normal_media.z()));

                texCoords.push_back(TC.first);
                texCoords.push_back(TC.second);
            };
            Vector N_media = (Ns[f.normalIndex(0)] + Ns[f.normalIndex(1)] + Ns[f.normalIndex(2)])/3;
            pushVertex(f.vertexIndex(0), N_media, f.texcoordsIndex(0));
            pushVertex(f.vertexIndex(1), N_media, f.texcoordsIndex(1));
            pushVertex(f.vertexIndex(2), N_media, f.texcoordsIndex(2));
        }
    }
    numElements.push_back(obj.faces().size() * 3);

    GLWidget& g = *glwidget();
    GLuint VAO;
    g.glGenVertexArrays(1, &VAO);
    VAOs.push_back(VAO);

    GLuint coordBufferID;
    g.glGenBuffers(1, &coordBufferID);
    coordBuffers.push_back(coordBufferID);

    GLuint normalBufferID;
    g.glGenBuffers(1, &normalBufferID);
    normalBuffers.push_back(normalBufferID);

    GLuint stBufferID;
    g.glGenBuffers(1, &stBufferID);
    stBuffers.push_back(stBufferID);

    GLuint colorBufferID;
    g.glGenBuffers(1, &colorBufferID);
    colorBuffers.push_back(colorBufferID);

    GLuint indexBufferID;
    if (useIndices)
    {
        g.glGenBuffers(1, &indexBufferID);
        indexBuffers.push_back(indexBufferID);
    }

    g.glBindVertexArray(VAO);

    g.glBindBuffer(GL_ARRAY_BUFFER, coordBufferID);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(0);

    g.glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normals.size(), &normals[0], GL_STATIC_DRAW);
    g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(1);

    g.glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*colors.size(), &colors[0], GL_STATIC_DRAW);
    g.glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(2);

    g.glBindBuffer(GL_ARRAY_BUFFER, stBufferID);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
    g.glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(3);

    if (useIndices)
    {
        g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
        g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);
    }

    g.glBindBuffer(GL_ARRAY_BUFFER, 0);
    g.glBindVertexArray(0);
}

void Draw_smooth::cleanUp()
{
    GLWidget &g = *glwidget();
    if (coordBuffers.size() > 0) {
        g.glDeleteBuffers(coordBuffers.size(), &coordBuffers[0]);
    }
    if (normalBuffers.size() > 0) {
        g.glDeleteBuffers(normalBuffers.size(), &normalBuffers[0]);
    }
    if (stBuffers.size() > 0) {
        g.glDeleteBuffers(stBuffers.size(), &stBuffers[0]);
    }
    if (colorBuffers.size() > 0) {
        g.glDeleteBuffers(colorBuffers.size(), &colorBuffers[0]);
    }
    if (indexBuffers.size() > 0) {
        g.glDeleteBuffers(indexBuffers.size(), &indexBuffers[0]);
    }
    if (VAOs.size() > 0) {
        g.glDeleteVertexArrays(VAOs.size(), &VAOs[0]);
    }
    coordBuffers.clear();
    normalBuffers.clear();
    stBuffers.clear();
    colorBuffers.clear();
    indexBuffers.clear();
    VAOs.clear();
    numElements.clear();
}
