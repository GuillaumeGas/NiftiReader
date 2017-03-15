#pragma once

#include <vector>

#include <QWidget>
#include <QSize>
#include <QPainter>
#include <QPoint>

#include "Image.hpp"
#include "Voxel.hpp"

class RenderArea : public QWidget {
    Q_OBJECT

public:
    RenderArea (std::vector<QPoint> * points, QWidget * parent = NULL);

    void setPoints (std::vector<QPoint> * points);

protected:
    void paintEvent (QPaintEvent * event);

private:
    std::vector<QPoint> * _points;
};
