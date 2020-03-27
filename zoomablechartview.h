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

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event) override{
        QPoint numDegrees = event->angleDelta() / 8;
        QPoint numSteps = numDegrees;
        QPointF mousePos = event->position();
        QPointF center = QPointF(chart()->rect().width()/2,chart()->rect().height()/2);
        if(numSteps.y()>0)
            chart()->scroll(-(center.x()-mousePos.x())/6, (center.y()-mousePos.y())/6);
        else
            chart()->scroll((center.x()-mousePos.x())/6, -(center.y()-mousePos.y())/6);
        qDebug()<<center.x()<<"-"<<mousePos.x();
        chart()->zoom(1+static_cast<double>(numSteps.y())/100);
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

