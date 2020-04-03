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

using namespace QtCharts;
class Lab3 : public QWidget
{
    Q_OBJECT
public:
    explicit Lab3(QWidget *parent = nullptr);
private:
    void selectedSeries(int selection);
    void calculateSeries(std::function<double(double)> foo);
    QVector<std::complex<double>> calculateDFT(QVector<double> x);
    double sFunction(double x);
    double xFunction(double x);
    double yFunction(double x);
    double zFunction(double x);
    double uFunction(double x);
    double vFunction(double x);
    double p1Function(double x);
    double p2Function(double x);
    double p3Function(double x);

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
    QCheckBox* DBscale;
    QCheckBox* shift;
    QCheckBox* normalize;
};
