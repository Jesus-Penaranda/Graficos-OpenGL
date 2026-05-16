#include "navigatedefault.h"
#include "glwidget.h"
#include "mousePositionMethod.h"

NavigateDefault::NavigateDefault() : pmouseAction(NONE)
{}

void NavigateDefault::mousePressEvent( QMouseEvent *e)
{
  pxClick = QROUND(e->POS().x());
  pyClick = QROUND(e->POS().y());

    if (e->button() & Qt::LeftButton &&
        ! (e->modifiers()&(Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
    {
        pmouseAction = ROTATE;
    }
    else if (e->button() & Qt::LeftButton &&  e->modifiers() & Qt::ShiftModifier)
    {
        pmouseAction = ZOOM;
    }
    else if (e->button() & Qt::RightButton && ! (e->modifiers()&(Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
    {
        pmouseAction = PAN;
    }
}

void NavigateDefault::mouseReleaseEvent( QMouseEvent *)
{
    pmouseAction = NONE;
}

void NavigateDefault::mouseMoveEvent(QMouseEvent *e)
{
  float mouseDeltaX = QROUND(e->POS().x()) - pxClick;
  float mouseDeltaY = QROUND(e->POS().y()) - pyClick;

    Box box = glwidget()->boundingBoxIncludingAxes();

    float radius = box.radius();

    if (pmouseAction == ROTATE)
    {
        camera()->incrementAngleY(-mouseDeltaX);
        camera()->incrementAngleX(mouseDeltaY);
    }
    else if(pmouseAction == ZOOM)
    {
        camera()->incrementDistance(mouseDeltaY * 0.01 * radius);
    }
    else if (pmouseAction == PAN)
    {
      double r = camera()->getDist()/2.;
        double x = -0.02 * mouseDeltaX * r;
        double y =  0.02 * mouseDeltaY * r;

        QMatrix4x4 m = camera()->viewMatrix();
        Vector s(m(0,0), m(0,1), m(0,2));
        Vector u(m(1,0), m(1,1), m(1,2));
        camera()->pan(x * s + y * u);
    }

    camera()->updateClippingPlanes(box);

    pxClick = QROUND(e->POS().x());
    pyClick = QROUND(e->POS().y());

    glwidget()->update();
}
