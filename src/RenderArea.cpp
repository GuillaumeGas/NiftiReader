#include "RenderArea.hpp"

using namespace std;

RenderArea::RenderArea (vector<QPoint> * points, QWidget * parent) : _points (points), QWidget (parent) {
    setBackgroundRole (QPalette::Base);
    setAutoFillBackground (true);
}

void RenderArea::paintEvent (QPaintEvent *) {
    QPainter painter (this);
    painter.drawPoints (_points->data (), _points->size ());
}

void RenderArea::setPoints (vector<QPoint> * points) {
    _points = points;
    repaint ();
}
