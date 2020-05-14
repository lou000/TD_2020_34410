#include "lab5_6.h"

Lab5::Lab5(QWidget *parent) : QWidget(parent)
{
    auto chart = new QChart();
    this->chartView = new QChartViewWithZoomAndDrag(chart, this);
    this->chartView->setRenderHint(QPainter::Antialiasing);
    this->chartView->chart()->setTheme(QChart::ChartThemeDark);

    auto mainLayout = new QGridLayout(this);
    auto leftBarLayout = new QGridLayout();
    auto leftBarWidget = new QWidget();
    leftBarWidget->setLayout(leftBarLayout);
    leftBarWidget->setMinimumWidth(220);
    leftBarWidget->setMaximumWidth(220);

    leftBarLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    leftBarLayout->setVerticalSpacing(5);

    mainLayout->addWidget(leftBarWidget,0,0,Qt::AlignLeft | Qt::AlignTop);
    mainLayout->addWidget(chartView,0,2);
    this->setLayout(mainLayout);

    //////////////////MODULATION SELECTION////////////////
    auto modSelection = new QGroupBox("Modulation Select:", this);
    auto msLayout = new QGridLayout();
    modSelection->setLayout(msLayout);
    modSelection->setMinimumWidth(200);
    modSelection->setMinimumHeight(250);
    this->inputSeries = new QCheckBox("INPUT");
    msLayout->addWidget(inputSeries, 0, 0, Qt::AlignLeft);
    this->deltaT = new QDoubleSpinBox(this);
    this->deltaT->setAlignment(Qt::AlignRight);
    this->deltaT->setMaximumWidth(80);
    this->deltaT->setMaximum(2);
    this->deltaT->setMinimum(0);
    this->deltaT->setValue(0.1);
    msLayout->addWidget(new QLabel(" dT:", this), 0, 1, Qt::AlignRight);
    msLayout->addWidget(deltaT, 0, 2, Qt::AlignHCenter);
    this->ask = new QCheckBox("ASK");
    msLayout->addWidget(ask, 1, 0, Qt::AlignLeft);
    this->fsk = new QCheckBox("FSK");
    msLayout->addWidget(fsk, 1, 1, Qt::AlignLeft);
    this->psk = new QCheckBox("PSK");
    msLayout->addWidget(psk, 1, 2, Qt::AlignLeft);

    this->input = new QLineEdit("Lewicki Maciej",this);
    msLayout->addWidget(new QLabel("Input:", this), 2, 0, Qt::AlignLeft);
    msLayout->addWidget(input, 2, 1, 1, 5, Qt::AlignHCenter);

    this->steps = new QSpinBox(this);
    this->steps->setAlignment(Qt::AlignRight);
    this->steps->setMaximumWidth(80);
    this->steps->setMaximum(999999);
    this->steps->setMinimum(1);
    this->steps->setValue(1000);
    msLayout->addWidget(new QLabel("Steps:", this), 3, 0, Qt::AlignLeft);
    msLayout->addWidget(steps, 3, 1, 1, 5, Qt::AlignHCenter);

    this->bitLimit = new QSpinBox(this);
    this->bitLimit->setAlignment(Qt::AlignRight);
    this->bitLimit->setMaximumWidth(80);
    this->bitLimit->setMaximum(999999);
    this->bitLimit->setMinimum(1);
    this->bitLimit->setValue(10);
    msLayout->addWidget(new QLabel("Bit Limit:", this), 4, 0, Qt::AlignLeft);
    msLayout->addWidget(bitLimit, 4, 1, 1, 5, Qt::AlignHCenter);

    this->endian = new QComboBox(this);
    this->endian->addItem("Big Endian");
    this->endian->addItem("Little Endian");
    msLayout->addWidget(new QLabel("Endian:", this), 5, 0, Qt::AlignLeft);
    msLayout->addWidget(endian, 5, 1, 1, 5, Qt::AlignHCenter);

    msLayout->addWidget(new QLabel("Demodulate:", this), 6, 0, 1, 2, Qt::AlignLeft);
    this->dX = new QCheckBox("x(t)");
    msLayout->addWidget(dX, 7, 0, Qt::AlignLeft);
    this->dP = new QCheckBox("p(t)");
    msLayout->addWidget(dP, 7, 1, Qt::AlignLeft);
    this->dM = new QCheckBox("m(t)");
    msLayout->addWidget(dM, 7, 2, Qt::AlignLeft);

    this->dh = new QDoubleSpinBox(this);
    this->dh->setAlignment(Qt::AlignRight);
    this->dh->setMaximumWidth(80);
    this->dh->setMaximum(10);
    this->dh->setMinimum(-10);
    this->dh->setValue(0.8);
    msLayout->addWidget(new QLabel(" h:", this), 8, 0, Qt::AlignLeft);
    msLayout->addWidget(dh, 8, 1, 1, 5, Qt::AlignHCenter);

    leftBarLayout->addWidget(modSelection, 0, 0 , 1, 4, Qt::AlignHCenter);

    /////////////////////////ASK//////////////////////////
    auto askBox = new QGroupBox("ASK Variables",this);
    auto askBoxLayout = new QGridLayout();
    askBox->setLayout(askBoxLayout);
    askBox->setMinimumWidth(200);
    askBox->setMaximumHeight(150);

    this->askAmp1 = new QSlider(this);
    this->askAmp1->setOrientation(Qt::Horizontal);
    this->askAmp1->setMinimumWidth(105);
    this->askAmp1->setTickInterval(1);
    this->askAmp1->setMaximum(200);
    this->askAmp1->setMinimum(0);
    this->askAmp1->setValue(100);
    askBoxLayout->addWidget(new QLabel("A1:", this), 0, 0, Qt::AlignLeft);
    auto askAmp1Label = new QLabel(QString::number(static_cast<double>(askAmp1->value())/100),this);
    askBoxLayout->addWidget(askAmp1Label, 0, 2, Qt::AlignLeft);
    QObject::connect(askAmp1, &QSlider::sliderMoved, askAmp1Label,
                     [=](int pos){askAmp1Label->setText(QString::number(static_cast<double>(pos)/100));});
    askBoxLayout->addWidget(askAmp1, 0, 1, Qt::AlignHCenter);

    this->askAmp2 = new QSlider(this);
    this->askAmp2->setOrientation(Qt::Horizontal);
    this->askAmp2->setMinimumWidth(105);
    this->askAmp2->setTickInterval(1);
    this->askAmp2->setMaximum(200);
    this->askAmp2->setMinimum(0);
    this->askAmp2->setValue(0);
    askBoxLayout->addWidget(new QLabel("A2:", this), 1, 0, Qt::AlignLeft);
    auto askAmp2Label = new QLabel(QString::number(static_cast<double>(askAmp2->value())/100),this);
    askBoxLayout->addWidget(askAmp2Label, 1, 2, Qt::AlignLeft);
    QObject::connect(askAmp2, &QSlider::sliderMoved, askAmp2Label,
                     [=](int pos){askAmp2Label->setText(QString::number(static_cast<double>(pos)/100));});
    askBoxLayout->addWidget(askAmp2, 1, 1, Qt::AlignHCenter);

    this->askTargetFreq = new QSlider(this);
    this->askTargetFreq->setOrientation(Qt::Horizontal);
    this->askTargetFreq->setMinimumWidth(105);
    this->askTargetFreq->setTickInterval(1);
    this->askTargetFreq->setMaximum(3000);
    this->askTargetFreq->setMinimum(0);
    this->askTargetFreq->setValue(2000);
    askBoxLayout->addWidget(new QLabel("Tf:", this), 2, 0, Qt::AlignLeft);
    auto askTargetFreqLabel = new QLabel(QString::number(static_cast<double>(askTargetFreq->value())/100),this);
    askBoxLayout->addWidget(askTargetFreqLabel, 2, 2, Qt::AlignLeft);
    QObject::connect(askTargetFreq, &QSlider::sliderMoved, askTargetFreqLabel,
                     [=](int pos){askTargetFreqLabel->setText(QString::number(static_cast<double>(pos)/100));});
    askBoxLayout->addWidget(askTargetFreq, 2, 1, Qt::AlignHCenter);

    leftBarLayout->addWidget(askBox, 3, 0 , 1, 4, Qt::AlignHCenter);

    /////////////////////////FSK//////////////////////////
    auto fskBox = new QGroupBox("FSK Variables",this);
    auto fskBoxLayout = new QGridLayout();
    fskBox->setLayout(fskBoxLayout);
    fskBox->setMinimumWidth(200);
    fskBox->setMaximumHeight(150);

    this->fskTargetFreq1 = new QSlider(this);
    this->fskTargetFreq1->setOrientation(Qt::Horizontal);
    this->fskTargetFreq1->setMinimumWidth(105);
    this->fskTargetFreq1->setTickInterval(1);
    this->fskTargetFreq1->setMaximum(3000);
    this->fskTargetFreq1->setMinimum(0);
    this->fskTargetFreq1->setValue(2000);
    fskBoxLayout->addWidget(new QLabel("Tf1:", this), 1, 0, Qt::AlignLeft);
    auto fskTargetFreq1Label = new QLabel(QString::number(static_cast<double>(fskTargetFreq1->value())/100),this);
    fskBoxLayout->addWidget(fskTargetFreq1Label, 1, 2, Qt::AlignLeft);
    QObject::connect(fskTargetFreq1, &QSlider::sliderMoved, fskTargetFreq1Label,
                     [=](int pos){fskTargetFreq1Label->setText(QString::number(static_cast<double>(pos)/100));});
    fskBoxLayout->addWidget(fskTargetFreq1, 1, 1, Qt::AlignHCenter);

    this->fskTargetFreq2 = new QSlider(this);
    this->fskTargetFreq2->setOrientation(Qt::Horizontal);
    this->fskTargetFreq2->setMinimumWidth(105);
    this->fskTargetFreq2->setTickInterval(1);
    this->fskTargetFreq2->setMaximum(3000);
    this->fskTargetFreq2->setMinimum(0);
    this->fskTargetFreq2->setValue(3000);
    fskBoxLayout->addWidget(new QLabel("Tf2:", this), 2, 0, Qt::AlignLeft);
    auto fskTargetFreq2Label = new QLabel(QString::number(static_cast<double>(fskTargetFreq2->value())/100),this);
    fskBoxLayout->addWidget(fskTargetFreq2Label, 2, 2, Qt::AlignLeft);
    QObject::connect(fskTargetFreq2, &QSlider::sliderMoved, fskTargetFreq2Label,
                     [=](int pos){fskTargetFreq2Label->setText(QString::number(static_cast<double>(pos)/100));});
    fskBoxLayout->addWidget(fskTargetFreq2, 2, 1, Qt::AlignHCenter);

    this->fskShift = new QSlider(this);
    this->fskShift->setOrientation(Qt::Horizontal);
    this->fskShift->setMinimumWidth(105);
    this->fskShift->setTickInterval(1);
    this->fskShift->setMaximum(1000);
    this->fskShift->setMinimum(0);
    this->fskShift->setValue(0);
    fskBoxLayout->addWidget(new QLabel("Shift:", this), 3, 0, Qt::AlignLeft);
    auto fskShiftLabel = new QLabel(QString::number(static_cast<double>(fskShift->value())/100),this);
    fskBoxLayout->addWidget(fskShiftLabel, 3, 2, Qt::AlignLeft);
    QObject::connect(fskShift, &QSlider::sliderMoved, fskShiftLabel,
                     [=](int pos){fskShiftLabel->setText(QString::number(static_cast<double>(pos)/100));});
    fskBoxLayout->addWidget(fskShift, 3, 1, Qt::AlignHCenter);

    leftBarLayout->addWidget(fskBox, 4, 0 , 1, 4, Qt::AlignHCenter);

    /////////////////////////PSK//////////////////////////
    auto pskBox = new QGroupBox("PSK Variables",this);
    auto pskBoxLayout = new QGridLayout();
    pskBox->setLayout(pskBoxLayout);
    pskBox->setMinimumWidth(200);
    pskBox->setMaximumHeight(150);

    this->pskTargetFreq = new QSlider(this);
    this->pskTargetFreq->setOrientation(Qt::Horizontal);
    this->pskTargetFreq->setMinimumWidth(105);
    this->pskTargetFreq->setTickInterval(1);
    this->pskTargetFreq->setMaximum(3000);
    this->pskTargetFreq->setMinimum(0);
    this->pskTargetFreq->setValue(2000);
    pskBoxLayout->addWidget(new QLabel("Tf:", this), 1, 0, Qt::AlignLeft);
    auto pskTargetFreqLabel = new QLabel(QString::number(static_cast<double>(pskTargetFreq->value())/100),this);
    pskBoxLayout->addWidget(pskTargetFreqLabel, 1, 2, Qt::AlignLeft);
    QObject::connect(pskTargetFreq, &QSlider::sliderMoved, pskTargetFreqLabel,
                     [=](int pos){pskTargetFreqLabel->setText(QString::number(static_cast<double>(pos)/100));});
    pskBoxLayout->addWidget(pskTargetFreq, 1, 1, Qt::AlignHCenter);

    this->pskShift1 = new QSlider(this);
    this->pskShift1->setOrientation(Qt::Horizontal);
    this->pskShift1->setMinimumWidth(105);
    this->pskShift1->setTickInterval(1);
    this->pskShift1->setMaximum(1000);
    this->pskShift1->setMinimum(0);
    this->pskShift1->setValue(314);
    pskBoxLayout->addWidget(new QLabel("Shift1:", this), 2, 0, Qt::AlignLeft);
    auto pskShift1Label = new QLabel(QString::number(static_cast<double>(pskShift1->value())/100),this);
    pskBoxLayout->addWidget(pskShift1Label, 2, 2, Qt::AlignLeft);
    QObject::connect(pskShift1, &QSlider::sliderMoved, pskShift1Label,
                     [=](int pos){pskShift1Label->setText(QString::number(static_cast<double>(pos)/100));});
    pskBoxLayout->addWidget(pskShift1, 2, 1, Qt::AlignHCenter);

    this->pskShift2 = new QSlider(this);
    this->pskShift2->setOrientation(Qt::Horizontal);
    this->pskShift2->setMinimumWidth(105);
    this->pskShift2->setTickInterval(1);
    this->pskShift2->setMaximum(1000);
    this->pskShift2->setMinimum(0);
    this->pskShift2->setValue(0);
    pskBoxLayout->addWidget(new QLabel("Shift2:", this), 3, 0, Qt::AlignLeft);
    auto pskShift2Label = new QLabel(QString::number(static_cast<double>(pskShift2->value())/100),this);
    pskBoxLayout->addWidget(pskShift2Label, 3, 2, Qt::AlignLeft);
    QObject::connect(pskShift2, &QSlider::sliderMoved, pskShift2Label,
                     [=](int pos){pskShift2Label->setText(QString::number(static_cast<double>(pos)/100));});
    pskBoxLayout->addWidget(pskShift2, 3, 1, Qt::AlignHCenter);

    leftBarLayout->addWidget(pskBox, 5, 0 , 1, 4, Qt::AlignHCenter);

    //////////////SPECTRUM SETTINGS/////////////////////
    auto spectrumSettings = new QGroupBox("Spectrum Settings",this);
    auto ssLayout = new QGridLayout();
    spectrumSettings->setLayout(ssLayout);
    spectrumSettings->setMinimumWidth(200);
    spectrumSettings->setMaximumHeight(200);

    this->spectrum = new QCheckBox("Enable DFT", this);
    this->logYScale = new QCheckBox("Log YAxis", this);
    logYScale->setDisabled(true);
    this->dbScale = new QCheckBox("Db Scale", this);
    dbScale->setDisabled(true);
    this->shift = new QCheckBox("Shift", this);
    shift->setDisabled(true);
    this->normalize = new QCheckBox("Normalize", this);
    normalize->setDisabled(true);
    this->zeroHighestVal = new QCheckBox("Zero Y Axis", this);
    zeroHighestVal->setDisabled(true);

    this->bandwidthFreq = new QSlider(this);
    this->bandwidthFreq->setOrientation(Qt::Horizontal);
    this->bandwidthFreq->setMinimumWidth(105);
    this->bandwidthFreq->setTickInterval(1);
    this->bandwidthFreq->setMaximum(0);
    this->bandwidthFreq->setMinimum(-5000);
    this->bandwidthFreq->setValue(-300);
    ssLayout->addWidget(new QLabel("Bandwidth Freq:", this), 4, 0,1,2, Qt::AlignLeft);
    auto bFreqLabel = new QLabel(QString::number(static_cast<double>(bandwidthFreq->value())/100),this);
    ssLayout->addWidget(bFreqLabel, 5, 1, 1, 2, Qt::AlignRight);
    QObject::connect(bandwidthFreq, &QSlider::sliderMoved, bFreqLabel,
                     [=](int pos){bFreqLabel->setText(QString::number(static_cast<double>(pos)/100));});
    ssLayout->addWidget(bandwidthFreq, 5, 0, 1, 2, Qt::AlignLeft);

    ssLayout->addWidget(spectrum,0,0,Qt::AlignLeft);
    ssLayout->addWidget(shift,1,0,Qt::AlignLeft);
    ssLayout->addWidget(logYScale,0,1,Qt::AlignLeft);
    ssLayout->addWidget(dbScale,1,1,Qt::AlignLeft);
    ssLayout->addWidget(normalize,2,0,Qt::AlignLeft);
    ssLayout->addWidget(zeroHighestVal,2,1,Qt::AlignLeft);
    leftBarLayout->addWidget(spectrumSettings, 6, 0, 1, 4, Qt::AlignHCenter);

    QObject::connect(inputSeries, &QCheckBox::stateChanged, this, [=]{calculateSeries();});
    QObject::connect(deltaT, &QDoubleSpinBox::textChanged, this, [=]{calculateSeries();});
    QObject::connect(ask, &QCheckBox::stateChanged, this, [=]{calculateSeries();});
    QObject::connect(fsk, &QCheckBox::stateChanged, this, [=]{calculateSeries();});
    QObject::connect(psk, &QCheckBox::stateChanged, this, [=]{calculateSeries();});

    QObject::connect(dX, &QCheckBox::stateChanged, this, [=](int state)
    {
        if(state==2)
        {
            dP->setDisabled(true);
            dM->setDisabled(true);
        }
        else
        {
            dP->setDisabled(false);
            dM->setDisabled(false);
        }
        calculateSeries();
    });
    QObject::connect(dP, &QCheckBox::stateChanged, this, [=](int state)
    {
        if(state==2)
        {
            dX->setDisabled(true);
            dM->setDisabled(true);
        }
        else
        {
            dX->setDisabled(false);
            dM->setDisabled(false);
        }
        calculateSeries();
    });
    QObject::connect(dM, &QCheckBox::stateChanged, this, [=](int state)
    {
        if(state==2)
        {
            dX->setDisabled(true);
            dP->setDisabled(true);
        }
        else
        {
            dX->setDisabled(false);
            dP->setDisabled(false);
        }
        calculateSeries();
    });
    QObject::connect(dh, &QDoubleSpinBox::textChanged, this, [=]{calculateSeries();});

    QObject::connect(input, &QLineEdit::textEdited, this, [=]{calculateSeries();});
    QObject::connect(steps, &QSpinBox::textChanged, this, [=]{calculateSeries();});
    QObject::connect(bitLimit, &QSpinBox::textChanged, this, [=]{calculateSeries();});
    QObject::connect(endian, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=]{calculateSeries();});

    QObject::connect(askAmp1, &QSlider::valueChanged, this, [=]{calculateSeries();});
    QObject::connect(askAmp2, &QSlider::valueChanged, this, [=]{calculateSeries();});
    QObject::connect(askTargetFreq, &QSlider::valueChanged, this, [=]{calculateSeries();});

    QObject::connect(fskTargetFreq1, &QSlider::valueChanged, this, [=]{calculateSeries();});
    QObject::connect(fskTargetFreq2, &QSlider::valueChanged, this, [=]{calculateSeries();});
    QObject::connect(fskShift, &QSlider::valueChanged, this, [=]{calculateSeries();});

    QObject::connect(pskTargetFreq, &QSlider::valueChanged, this, [=]{calculateSeries();});
    QObject::connect(pskShift1, &QSlider::valueChanged, this, [=]{calculateSeries();});
    QObject::connect(pskShift2, &QSlider::valueChanged, this, [=]{calculateSeries();});

    QObject::connect(spectrum, &QCheckBox::stateChanged, this, [=]{calculateSeries();});
    QObject::connect(spectrum, &QCheckBox::stateChanged, this, [=](int state)
                     {
                         if(state==2)
                         {
                             logYScale->setDisabled(false);
                             dbScale->setDisabled(false);
                             shift->setDisabled(false);
                             normalize->setDisabled(false);
                             zeroHighestVal->setDisabled(false);
                         }
                         else
                         {
                             logYScale->setDisabled(true);
                             dbScale->setDisabled(true);
                             shift->setDisabled(true);
                             normalize->setDisabled(true);
                             zeroHighestVal->setDisabled(true);
                         }
                     });
    QObject::connect(logYScale, &QCheckBox::stateChanged, this, [=]{calculateSeries();});
    QObject::connect(logYScale, &QCheckBox::stateChanged, this, [=](int state)
                     {
                         if(state==2)
                         {
                             dbScale->setDisabled(true);
                             zeroHighestVal->setDisabled(true);
                         }
                         else
                         {
                             dbScale->setDisabled(false);
                             zeroHighestVal->setDisabled(false);
                         }
                     });
    QObject::connect(dbScale, &QCheckBox::stateChanged, this, [=]{calculateSeries();});
    QObject::connect(dbScale, &QCheckBox::stateChanged, this, [=](int state)
                     {
                         if(state==2)
                         {
                             logYScale->setDisabled(true);
                         }
                         else
                         {
                             logYScale->setDisabled(false);
                         }
                     });
    QObject::connect(shift, &QCheckBox::stateChanged, this, [=]{calculateSeries();});
    QObject::connect(normalize, &QCheckBox::stateChanged, this, [=]{calculateSeries();});
    QObject::connect(bandwidthFreq, &QSlider::valueChanged, this, [=]{calculateSeries();});
    QObject::connect(zeroHighestVal, &QCheckBox::stateChanged, this, [=]{calculateSeries();});
    calculateSeries();
}

void Lab5::calculateSeries()
{
    chartView->chart()->removeAllSeries();
    QVector<double> vecX;
    QVector<double> vecY;
    double askAmp1_l = static_cast<double>(askAmp1->value())/100;
    double askAmp2_l = static_cast<double>(askAmp2->value())/100;
    double askTargetFreq_l = static_cast<double>(askTargetFreq->value())/100;
    double askShift_l = 0;

    double fskAmp_l = 0.5;
    double fskTargetFreq1_l = static_cast<double>(fskTargetFreq1->value())/100;
    double fskTargetFreq2_l = static_cast<double>(fskTargetFreq2->value())/100;
    double fskShift_l = static_cast<double>(fskShift->value())/100;

    double pskAmp_l = 0.5;
    double pskTargetFreq_l = static_cast<double>(pskTargetFreq->value())/100;
    double pskShift1_l = static_cast<double>(pskShift1->value())/100;
    double pskShift2_l = static_cast<double>(pskShift2->value())/100;

    Endian end = (endian->currentIndex()>0) ? LittleEndian : BigEndian;
    QBitArray bits = bitsFromString(input->text(), end);
    double bitLim = (bitLimit->value()>bits.count()) ? bits.count() : bitLimit->value();
    double range = deltaT->value() * bitLim;
    int stepsVal = steps->value();
    double step = range/stepsVal;
    double fs = 1/step;


    for(int i=0; i<stepsVal; i++)
    {
        vecX.append(i*step);
        int bitNr = static_cast<int>(step*i/deltaT->value());
        if(bits.at(bitNr))
            vecY.append(1);
        else
            vecY.append(0);
    }
    if(inputSeries->checkState()==2)
    {
        QLineSeries* series = new QLineSeries(this);
        for(int i=0; i<stepsVal; i++)
        {
            series->append(vecX.at(i), vecY.at(i));
        }
        chartView->chart()->addSeries(series);
    }
    if(ask->checkState()==2)
    {
        //im wyzsza A2 tym większe musi być h żeby otrzymac poprawny wynik
        QVector<double> tempY;
        QLineSeries* series = new QLineSeries(this);
        for(int i=0; i<stepsVal; i++)
        {
            if(vecY.at(i))
                tempY.append((askAmp1_l)*(sin(2*M_PI*askTargetFreq_l*vecX.at(i)+askShift_l)));
            else
                tempY.append((askAmp2_l)*(sin(2*M_PI*askTargetFreq_l*vecX.at(i)+askShift_l)));
        }
        if(dX->checkState()==2 || dP->checkState()==2 || dM->checkState()==2)
        {
            for(int i=0; i<tempY.length(); i++)
                tempY[i] *= (askAmp1_l)*(sin(2*M_PI*askTargetFreq_l*vecX.at(i)+askShift_l));
        }
        if(dP->checkState()==2 || dM->checkState()==2)
        {
            for(int b=0; b<bitLim; b++)
            {
                int bitLength = stepsVal/bitLim;
                int bitStartStep = b*bitLength;
                int bitEndStep = (b+1)*bitLength;
                double integral = 0;
                for(int i=bitStartStep; i<bitEndStep-1; i++)
                {
                    integral += (tempY.at(i)+tempY.at(i+1))/2*(vecX.at(i+1)-vecX.at(i));
                    //               (a     +     b)       /2*           h
                    //wartosci na przykladowych wykresach z jakiegos powodu zostały przemnożone
                    //przez 1000 wiec robie to samo
                    tempY[i] = integral*1000;
                }
            }
        }
        if(dM->checkState()==2)
        {
            for(int i=0; i<tempY.length(); i++)
                if(tempY.at(i)>dh->value())
                    tempY[i] = 1;
                else
                    tempY[i] = 0;
        }
        for(int i=0; i<vecX.length() && i<tempY.length(); i++)
            series->append(vecX.at(i), tempY.at(i));
        chartView->chart()->addSeries(series);
    }
    if(fsk->checkState()==2)
    {
        QVector<double> tempY;
        QVector<double> tempY2;
        QVector<double> tempY3;
        QLineSeries* series = new QLineSeries(this);
        for(int i=0; i<stepsVal; i++)
        {
            if(vecY.at(i))
                tempY.append((fskAmp_l)*(sin(2*M_PI*fskTargetFreq1_l*vecX.at(i)+fskShift_l)));
            else
                tempY.append((fskAmp_l)*(sin(2*M_PI*fskTargetFreq2_l*vecX.at(i)+fskShift_l)));
        }
        if(dX->checkState()==2 || dP->checkState()==2 || dM->checkState()==2)
        {
            for(int i=0; i<tempY.length(); i++)
                tempY2.append(tempY.at(i)*(fskAmp_l)*(sin(2*M_PI*fskTargetFreq2_l*vecX.at(i)+fskShift_l)));
            for(int i=0; i<tempY.length(); i++)
                tempY[i] *= (fskAmp_l)*(sin(2*M_PI*fskTargetFreq1_l*vecX.at(i)+fskShift_l));
        }
        if(dP->checkState()==2 || dM->checkState()==2)
        {
            for(int b=0; b<bitLim; b++)
            {
                int bitLength = stepsVal/bitLim;
                int bitStartStep = b*bitLength;
                int bitEndStep = (b+1)*bitLength;
                double integral = 0;
                double integral2 = 0;
                for(int i=bitStartStep; i<bitEndStep-1; i++)
                {
                    integral += (tempY.at(i)+tempY.at(i+1))/2*(vecX.at(i+1)-vecX.at(i));
                    //               (a     +     b)       /2*           h
                    //wartosci na przykladowych wykresach z jakiegos powodu zostały przemnożone
                    //przez 1000 wiec robie to samo
                    tempY[i] = integral*1000;

                    integral2 += (tempY2.at(i)+tempY2.at(i+1))/2*(vecX.at(i+1)-vecX.at(i));
                    tempY2[i] = integral2*1000;
                    tempY3.append(integral*1000-integral2*1000);
                }
            }
        }
        if(dM->checkState()==2)
        {
            for(int i=0; i<tempY3.length() && i<tempY.length(); i++)
                if(tempY3.at(i)>dh->value())
                    tempY[i] = 1;
                else
                    tempY[i] = 0;
        }
        for(int i=0; i<vecX.length() && i<tempY.length(); i++)
            series->append(vecX.at(i), tempY.at(i));
        chartView->chart()->addSeries(series);
        if(dX->checkState()==2)
        {
            QLineSeries* series2 = new QLineSeries(this);
            for(int i=0; i<vecX.length() && i<tempY2.length(); i++)
                series2->append(vecX.at(i), tempY2.at(i));
            chartView->chart()->addSeries(series2);
        }
        if(dP->checkState()==2)
        {
            QLineSeries* series2 = new QLineSeries(this);
            QLineSeries* series3 = new QLineSeries(this);
            for(int i=0; i<vecX.length() && i<tempY2.length() && i<tempY3.length(); i++)
            {
                series2->append(vecX.at(i), tempY2.at(i));
                series3->append(vecX.at(i), tempY3.at(i));
            }
            chartView->chart()->addSeries(series2);
            chartView->chart()->addSeries(series3);
        }
    }
    if(psk->checkState()==2)
    {
        QVector<double> tempY;
        QLineSeries* series = new QLineSeries(this);
        for(int i=0; i<stepsVal; i++)
        {
            if(vecY.at(i))
                tempY.append((pskAmp_l)*(sin(2*M_PI*pskTargetFreq_l*vecX.at(i)+pskShift1_l)));
            else
                tempY.append((pskAmp_l)*(sin(2*M_PI*pskTargetFreq_l*vecX.at(i)+pskShift2_l)));
        }
        if(dX->checkState()==2 || dP->checkState()==2 || dM->checkState()==2)
        {
            for(int i=0; i<tempY.length(); i++)
                tempY[i] *= (pskAmp_l)*(sin(2*M_PI*pskTargetFreq_l*vecX.at(i)+pskShift1_l));
        }
        if(dP->checkState()==2 || dM->checkState()==2)
        {
            for(int b=0; b<bitLim; b++)
            {
                int bitLength = stepsVal/bitLim;
                int bitStartStep = b*bitLength;
                int bitEndStep = (b+1)*bitLength;
                double integral = 0;
                for(int i=bitStartStep; i<bitEndStep-1; i++)
                {
                    integral += (tempY.at(i)+tempY.at(i+1))/2*(vecX.at(i+1)-vecX.at(i));
                    //               (a     +     b)       /2*           h
                    //wartosci na przykladowych wykresach z jakiegos powodu zostały przemnożone
                    //przez 1000 wiec robie to samo
                    tempY[i] = integral*1000;
                }
            }
        }
        if(dM->checkState()==2)
        {
            for(int i=0; i<tempY.length(); i++)
                if(tempY.at(i)>dh->value())
                    tempY[i] = 1;
                else
                    tempY[i] = 0;
        }
        for(int i=0; i<vecX.length() && i<tempY.length(); i++)
            series->append(vecX.at(i), tempY.at(i));
        chartView->chart()->addSeries(series);
    }
    if(spectrum->checkState()==2)
    {
        auto series = chartView->chart()->series();
        for(QAbstractSeries* s : series)
        {
            QLineSeries* s1 = (QLineSeries*) s;
            QVector<QPointF> tempPoints;
            double max = -INFINITY;
            QVector<std::complex<double>> results = Lab3::calculateDFT(s1->points());
            if(shift->checkState()==2)
                for(int i=0;i<=results.length()/2;i++)
                {
                    auto temp = results.front();
                    results.pop_front();
                    results.append(temp);
                }
            for(int k = 0; k<results.length(); k++)
            {
                double y = abs(results.at(k));
                double x = (k*(fs/stepsVal));

                if(normalize->checkState()==2)
                    y = y/(stepsVal/2);
                if(shift->checkState()==2)
                    x-=fs/2;
                if(dbScale->checkState()==2)
                    y = 10*log10(y);
                tempPoints.append(QPointF(x,y));
                if(y>max)
                    max=y;
            }
            if(zeroHighestVal->checkState()==2)
                for(int i=0; i<tempPoints.length();i++)
                    tempPoints.replace(i,QPointF(tempPoints.at(i).x(),tempPoints.at(i).y()-max));
            s1->replace(tempPoints);
            chartView->chart()->removeSeries(s);
            chartView->chart()->addSeries(s1);
        }
    }

    chartView->chart()->createDefaultAxes();
    if(chartView->chart()->axes(Qt::Vertical).length()>0)
    {
        QValueAxis* axisY = (QValueAxis*)chartView->chart()->axes(Qt::Vertical)[0];
        double addRange = (axisY->max() - axisY->min())*0.10;
        axisY->setMax(axisY->max()+addRange);
        axisY->setMin(axisY->min()-addRange);
    }
    if(dbScale->checkState()==2)
    {
        auto series = chartView->chart()->series();
        for(QAbstractSeries* s : series)
        {
            QLineSeries* s1 = (QLineSeries*) s;
            QPair<double,double> minMax = Lab4::calculateBandwidth(s1->pointsVector(), static_cast<double>(bandwidthFreq->value())/100);
            QCategoryAxis* axis = new QCategoryAxis(this);
            axis->setMin(s1->pointsVector().first().x());
            axis->setMax(s1->pointsVector().last().x());
            axis->setStartValue(minMax.first);
            QPen pen;
            pen.setColor("indianred");
            pen.setWidth(2);
            axis->setGridLinePen(pen);
            axis->append("Bandwidth: "+QString::number(minMax.second-minMax.first,'f',2), minMax.second);
            chartView->chart()->addAxis(axis, Qt::AlignBottom);
        }
        auto temp = (QValueAxis*)chartView->chart()->axes(Qt::Vertical).at(0);
        QValueAxis* help = new QValueAxis(this);
        help->setRange(temp->min(), temp->max());
        help->setLabelFormat(" ");
        chartView->chart()->addAxis(help, Qt::AlignRight);
    }
}

QBitArray Lab5::bitsFromString(QString s, Endian e)
{
    QByteArray ba = s.toLocal8Bit();
    const char* c = ba.data();
    QBitArray bitArr = QBitArray::fromBits(c,ba.size()*8);
    if(e == LittleEndian)
        reverseBitArray(bitArr);
    return bitArr;
}
void Lab5::reverseBitArray(QBitArray &arr)
{
    for(int i=0; i<arr.count()/2;i++)
    {
        bool bit = arr.at(i);
        arr.setBit(i,arr.at(arr.count()-1-i));
        arr.setBit(arr.count()-1-i, bit);
    }
}

