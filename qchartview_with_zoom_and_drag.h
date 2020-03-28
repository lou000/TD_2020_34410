#pragma once
#include <QObject>
#include <QChartView>
//THIS WAS ONLY TESTED ON QLineSeries and default QChart settings

using namespace QtCharts;
class QChartViewWithZoomAndDrag : public QChartView
{
    Q_OBJECT
public:
    using QChartView::QChartView;

protected:
    //ZOOM
    void wheelEvent(QWheelEvent *event) override{
        //This is imperfect, there is still slight drift when zooming and zoomIn amount != zoomOut amount

        //exclude area outside plot
        QRectF plotArea = chart()->plotArea();
        if(event->position().x()<plotArea.x() || event->position().y()<plotArea.y()
            || event->position().x()>plotArea.x()+plotArea.width() ||event->position().y()>plotArea.y()+plotArea.height())
            return;
        QPointF mousePos = event->position();
        mousePos.setX(mousePos.x()-plotArea.x());
        mousePos.setY(mousePos.y()-plotArea.y());

        //scroll and zoom
        qreal numDegrees = static_cast<qreal>(event->angleDelta().y())/8;
        QPointF center = QPointF(plotArea.width()/2,plotArea.height()/2);
        chart()->scroll((mousePos.x()-center.x())*(numDegrees/100), -(mousePos.y()-center.y())*(numDegrees/100));
        chart()->zoom(1+numDegrees/100);
        event->accept();
    }
    //DRAG
    void mouseMoveEvent(QMouseEvent *event) override
    {
        if(event->buttons().testFlag(Qt::LeftButton))
        {
            chart()->scroll(-(event->x()-lastMousePos.x()), (event->y()-lastMousePos.y()));
            event->accept();
        }
        lastMousePos = event->pos();
    }

private:
    QPoint lastMousePos = QPoint(0,0);
};
