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
#include <QCategoryAxis>
#include <QBitArray>
#include <QByteArray>

#include "qchartview_with_zoom_and_drag.h"
#include "lab3/lab3.h"
#include "lab4/lab4.h"

enum Endian
{
    BigEndian,
    LittleEndian
};

class Lab5 : public QWidget
{
    Q_OBJECT
public:
    explicit Lab5(QWidget *parent = nullptr);
    void calculateSeries();
    QBitArray bitsFromString(QString s, Endian e);
    void reverseBitArray(QBitArray &arr);

    QChartViewWithZoomAndDrag* chartView;

    QCheckBox* inputSeries;
    QDoubleSpinBox* deltaT;
    QCheckBox* ask;
    QCheckBox* fsk;
    QCheckBox* psk;

    QCheckBox* dX;
    QCheckBox* dP;
    QCheckBox* dM;
    QDoubleSpinBox* dh;

    QLineEdit* input;
    QSpinBox* steps;
    QSpinBox* bitLimit;
    QComboBox* endian;

    QSlider* askAmp1;
    QSlider* askAmp2;
    QSlider* askTargetFreq;

    QSlider* fskTargetFreq1;
    QSlider* fskTargetFreq2;
    QSlider* fskShift;

    QSlider* pskTargetFreq;
    QSlider* pskShift1;
    QSlider* pskShift2;

    QCheckBox* spectrum;
    QCheckBox* logYScale;
    QCheckBox* dbScale;
    QCheckBox* shift;
    QCheckBox* normalize;
    QCheckBox* zeroHighestVal;
    QSlider* bandwidthFreq;
};

