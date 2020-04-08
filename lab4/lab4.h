#pragma once

#include <QObject>
#include <QWidget>
#include <QtMath>
#include <QRandomGenerator>

#include <QChart>
#include <QLineSeries>
#include <QLogValueAxis>

#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QSlider>
#include <QCheckBox>
#include <QLabel>
#include <QBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QComboBox>

#include "qchartview_with_zoom_and_drag.h"
#include "lab3/lab3.h"

class Lab4 : public QWidget
{
    Q_OBJECT
public:
    explicit Lab4(QWidget *parent = nullptr);
    static QVector<double> modulateAmplitude(QVector<double> x, double modFreq, double modAmp);
    static QVector<double> modulatePhase(QVector<double> x, double modFreq, double modAmp);

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

    QSlider* modAmplitude;
    QSlider* modFrequency;

    QCheckBox* modAmpl;
    QCheckBox* modPhase;

    QCheckBox* spectrum;
    QCheckBox* reverse;
    QCheckBox* logYScale;
    QCheckBox* shift;
    QCheckBox* normalize;
};

