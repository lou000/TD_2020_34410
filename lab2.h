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
#include "zoomablechartview.h"

using namespace QtCharts;
class Lab2 : public QWidget
{
    Q_OBJECT
public:
    explicit Lab2(QWidget *parent = nullptr);
private:
    void calculateSeries();

    QLineSeries* series;
    ZoomableChartView* chartView;

    QDoubleSpinBox* rangeFrom;
    QDoubleSpinBox* rangeTo;
    QSpinBox* steps;

    QSlider* amplitude;
    QSlider* frequency;
    QSlider* phaseShift;

    QCheckBox* quantize;
    QLineEdit* quantizationResolution;

};
