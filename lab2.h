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

using namespace QtCharts;
class Lab2 : public QWidget
{
    Q_OBJECT
public:
    explicit Lab2(QWidget *parent = nullptr);
private:
    void calculateSeries();

    QLineSeries* series;
    QChartView* chartView;

    QDoubleSpinBox* rangeFrom;
    QDoubleSpinBox* rangeTo;
    QSpinBox* steps;

    //TODO: change QDoubleSpinBox to QSlider?
    QDoubleSpinBox* amplitude;
    QDoubleSpinBox* frequency;
    QDoubleSpinBox* phaseShift;

    QCheckBox* quantize;
    QLineEdit* quantizationResolution;

};