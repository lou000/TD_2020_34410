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
#include <QPlainTextEdit>

#include "qchartview_with_zoom_and_drag.h"
#include "lab3/lab3.h"
#include "lab4/lab4.h"
#include "lab5/lab5_6.h"

struct LabSeries
{
    QVector<double> xVec;
    QVector<double> yVec;
    QString name;

    explicit LabSeries(QVector<double> x, QVector<double> y, const QString& n) : name(n)
    {
        Q_ASSERT_X(x.length()==y.length(), "LabSeries constructor", "Length of vectors is not equal");
        xVec = x;
        yVec = y;
    }
};

class Lab7 : public QWidget
{
    Q_OBJECT
public:
    explicit Lab7(QWidget *parent = nullptr);
    void displaySeries();
    void addSeriesToChart(QVector<LabSeries> series, double offset);

    LabSeries genCLK(double freq, double from, double to, int steps);

    LabSeries modTTL(LabSeries clock, QBitArray bits);
    LabSeries modManchester(LabSeries clock, QBitArray bits);
    LabSeries modNRZI(LabSeries clock, QBitArray bits);
    LabSeries modBAMI(LabSeries clock, QBitArray bits);

    QBitArray decTTL(int clockFreq, LabSeries mod);
    QBitArray decManchester(int clockFreq, LabSeries mod);
    QBitArray decNRZI(int clockFreq, LabSeries mod);
    QBitArray decBAMI(int clockFreq, LabSeries mod);

    QBitArray bitsFromString(QString s, Endian e);
    QString stringFromBits(QBitArray bits, Endian e);
    void reverseBitsInBytes(QBitArray &arr);

    QChartViewWithZoomAndDrag* chartView;

    QCheckBox* clk;
    QDoubleSpinBox* rangeFrom;
    QDoubleSpinBox* rangeTo;
    QSpinBox* clkFrq;
    QCheckBox* ttl;
    QCheckBox* man;
    QCheckBox* nrzi;
    QCheckBox* bami;
    QCheckBox* decode;

    QLineEdit* input;
    QSpinBox* steps;
    QSpinBox* bitLimit;
    QComboBox* endian;

    QPlainTextEdit* decodeOutput;
};

