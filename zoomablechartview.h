#pragma once
#include <QObject>
#include <QChartView>
#include <QDebug>

using namespace QtCharts;
class ZoomableChartView : public QChartView
{
    Q_OBJECT
public:
    using QChartView::QChartView;

protected:
    //NOTE: this was far easier then expected, zoomIn and zoomOut are still not equal!
    void wheelEvent(QWheelEvent *event) override{
        QPoint numDegrees = event->angleDelta() / 8;
        QPoint numSteps = numDegrees;
        QPointF mousePos = event->position();
        double zoomFactor = static_cast<double>(numSteps.y());
        QPointF center = QPointF(chart()->rect().width()/2,chart()->rect().height()/2);
        if(numSteps.y()>0)
            chart()->scroll(-(center.x()-mousePos.x())/(abs(zoomFactor)/2), (center.y()-mousePos.y())/(abs(zoomFactor)/2));
        else
            chart()->scroll((center.x()-mousePos.x())/(abs(zoomFactor)/2), -(center.y()-mousePos.y())/(abs(zoomFactor)/2));
        chart()->zoom(1+zoomFactor/100);
        event->accept();
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if(event->buttons().testFlag(Qt::LeftButton))
            chart()->scroll(-(event->x()-lastMousePos.x()), (event->y()-lastMousePos.y()));
        lastMousePos = event->pos();
    }

private:
    QPoint lastMousePos = QPoint(0,0);
};

