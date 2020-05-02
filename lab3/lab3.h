#pragma once
#include <QObject>
#include <QWidget>
#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QtMath>
#include <QLineEdit>
#include <QSlider>
#include "qchartview_with_zoom_and_drag.h"
#include <complex>
#include <QComboBox>
#include <qdebug.h>
#include <QRandomGenerator>
#include <QLogValueAxis>

using namespace QtCharts;
class Lab3 : public QWidget
{
    Q_OBJECT
public:
    explicit Lab3(QWidget *parent = nullptr);
    static QVector<std::complex<double>> calculateDFT(QVector<double> x);
    static QVector<std::complex<double>> calculateDFT(QList<QPointF> point);
    static QVector<double> reverseDFT(QVector<std::complex<double>> dft);
    static double xFunction(double x);
    static double yFunction(double x);
    static double zFunction(double x);
    static double uFunction(double x);
    static double vFunction(double x);
    static double p1Function(double x);
    static double p2Function(double x);
    static double p3Function(double x);

private:
    void selectedSeries(int selection);
    void calculateSeries(std::function<double(double)> foo);
    double sFunction(double x);

    QLineSeries* series;
    QChartViewWithZoomAndDrag* chartView;

    QComboBox* funcSelection;

    QDoubleSpinBox* rangeFrom;
    QDoubleSpinBox* rangeTo;
    QSpinBox* steps;

    QSlider* amplitude;
    QSlider* frequency;
    QSlider* phaseShift;

    QCheckBox* spectrum;
    QCheckBox* reverse;
    QCheckBox* DBscale;
    QCheckBox* shift;
    QCheckBox* normalize;
};
