#include "lab5.h"

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
    modSelection->setMinimumHeight(175);
    this->inputSeries = new QCheckBox("INPUT");
    msLayout->addWidget(inputSeries, 0, 0, Qt::AlignLeft);
    this->deltaT = new QDoubleSpinBox(this);
    this->deltaT->setAlignment(Qt::AlignRight);
    this->deltaT->setMaximumWidth(80);
    this->deltaT->setMaximum(2);
    this->deltaT->setMinimum(0);
    this->deltaT->setValue(0.5);
    msLayout->addWidget(new QLabel(" dT:", this), 0, 1, Qt::AlignRight);
    msLayout->addWidget(deltaT, 0, 2, Qt::AlignHCenter);
    this->ask = new QCheckBox("ASK");
    msLayout->addWidget(ask, 1, 0, Qt::AlignLeft);
    this->fsk = new QCheckBox("FSK");
    msLayout->addWidget(fsk, 1, 1, Qt::AlignLeft);
    this->psk = new QCheckBox("PSK");
    msLayout->addWidget(psk, 1, 2, Qt::AlignLeft);

    this->input = new QLineEdit("please end me",this);
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
    this->bitLimit->setValue(100);
    msLayout->addWidget(new QLabel("Bit Limit:", this), 4, 0, Qt::AlignLeft);
    msLayout->addWidget(bitLimit, 4, 1, 1, 5, Qt::AlignHCenter);

    this->endian = new QComboBox(this);
    this->endian->addItem("Little Endian");
    this->endian->addItem("Big Endian");
    msLayout->addWidget(new QLabel("Endian:", this), 5, 0, Qt::AlignLeft);
    msLayout->addWidget(endian, 5, 1, 1, 5, Qt::AlignHCenter);

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
    this->askAmp1->setValue(50);
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
    this->askAmp2->setValue(100);
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
    this->askTargetFreq->setMaximum(1000);
    this->askTargetFreq->setMinimum(0);
    this->askTargetFreq->setValue(200);
    askBoxLayout->addWidget(new QLabel("Tf:", this), 2, 0, Qt::AlignLeft);
    auto askTargetFreqLabel = new QLabel(QString::number(static_cast<double>(askTargetFreq->value())/100),this);
    askBoxLayout->addWidget(askTargetFreqLabel, 2, 2, Qt::AlignLeft);
    QObject::connect(askTargetFreq, &QSlider::sliderMoved, askTargetFreqLabel,
                     [=](int pos){askTargetFreqLabel->setText(QString::number(static_cast<double>(pos)/100));});
    askBoxLayout->addWidget(askTargetFreq, 2, 1, Qt::AlignHCenter);

    this->askShift = new QSlider(this);
    this->askShift->setOrientation(Qt::Horizontal);
    this->askShift->setMinimumWidth(105);
    this->askShift->setTickInterval(1);
    this->askShift->setMaximum(1000);
    this->askShift->setMinimum(0);
    this->askShift->setValue(0);
    askBoxLayout->addWidget(new QLabel("Shift:", this), 3, 0, Qt::AlignLeft);
    auto askShiftLabel = new QLabel(QString::number(static_cast<double>(askShift->value())/100),this);
    askBoxLayout->addWidget(askShiftLabel, 3, 2, Qt::AlignLeft);
    QObject::connect(askShift, &QSlider::sliderMoved, askShiftLabel,
                     [=](int pos){askShiftLabel->setText(QString::number(static_cast<double>(pos)/100));});
    askBoxLayout->addWidget(askShift, 3, 1, Qt::AlignHCenter);

    leftBarLayout->addWidget(askBox, 3, 0 , 1, 4, Qt::AlignHCenter);

    /////////////////////////FSK//////////////////////////
    auto fskBox = new QGroupBox("FSK Variables",this);
    auto fskBoxLayout = new QGridLayout();
    fskBox->setLayout(fskBoxLayout);
    fskBox->setMinimumWidth(200);
    fskBox->setMaximumHeight(150);

    this->fskAmp = new QSlider(this);
    this->fskAmp->setOrientation(Qt::Horizontal);
    this->fskAmp->setMinimumWidth(105);
    this->fskAmp->setTickInterval(1);
    this->fskAmp->setMaximum(200);
    this->fskAmp->setMinimum(0);
    this->fskAmp->setValue(50);
    fskBoxLayout->addWidget(new QLabel("A:", this), 0, 0, Qt::AlignLeft);
    auto fskAmpLabel = new QLabel(QString::number(static_cast<double>(fskAmp->value())/100),this);
    fskBoxLayout->addWidget(fskAmpLabel, 0, 2, Qt::AlignLeft);
    QObject::connect(fskAmp, &QSlider::sliderMoved, fskAmpLabel,
                     [=](int pos){fskAmpLabel->setText(QString::number(static_cast<double>(pos)/100));});
    fskBoxLayout->addWidget(fskAmp, 0, 1, Qt::AlignHCenter);

    this->fskTargetFreq1 = new QSlider(this);
    this->fskTargetFreq1->setOrientation(Qt::Horizontal);
    this->fskTargetFreq1->setMinimumWidth(105);
    this->fskTargetFreq1->setTickInterval(1);
    this->fskTargetFreq1->setMaximum(1000);
    this->fskTargetFreq1->setMinimum(0);
    this->fskTargetFreq1->setValue(100);
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
    this->fskTargetFreq2->setMaximum(1000);
    this->fskTargetFreq2->setMinimum(0);
    this->fskTargetFreq2->setValue(200);
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

    this->pskAmp = new QSlider(this);
    this->pskAmp->setOrientation(Qt::Horizontal);
    this->pskAmp->setMinimumWidth(105);
    this->pskAmp->setTickInterval(1);
    this->pskAmp->setMaximum(200);
    this->pskAmp->setMinimum(0);
    this->pskAmp->setValue(50);
    pskBoxLayout->addWidget(new QLabel("A:", this), 0, 0, Qt::AlignLeft);
    auto pskAmpLabel = new QLabel(QString::number(static_cast<double>(pskAmp->value())/100),this);
    pskBoxLayout->addWidget(pskAmpLabel, 0, 2, Qt::AlignLeft);
    QObject::connect(pskAmp, &QSlider::sliderMoved, pskAmpLabel,
                     [=](int pos){pskAmpLabel->setText(QString::number(static_cast<double>(pos)/100));});
    pskBoxLayout->addWidget(pskAmp, 0, 1, Qt::AlignHCenter);

    this->pskTargetFreq = new QSlider(this);
    this->pskTargetFreq->setOrientation(Qt::Horizontal);
    this->pskTargetFreq->setMinimumWidth(105);
    this->pskTargetFreq->setTickInterval(1);
    this->pskTargetFreq->setMaximum(1000);
    this->pskTargetFreq->setMinimum(0);
    this->pskTargetFreq->setValue(100);
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
    this->pskShift1->setValue(200);
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
    QObject::connect(ask, &QCheckBox::stateChanged, this, [=]{calculateSeries();});
    QObject::connect(fsk, &QCheckBox::stateChanged, this, [=]{calculateSeries();});
    QObject::connect(psk, &QCheckBox::stateChanged, this, [=]{calculateSeries();});

    QObject::connect(input, &QLineEdit::textEdited, this, [=]{calculateSeries();});
    QObject::connect(steps, &QSpinBox::textChanged, this, [=]{calculateSeries();});
    QObject::connect(bitLimit, &QSpinBox::textChanged, this, [=]{calculateSeries();});
    QObject::connect(endian, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=]{calculateSeries();});

    QObject::connect(askAmp1, &QSlider::valueChanged, this, [=]{calculateSeries();});
    QObject::connect(askAmp2, &QSlider::valueChanged, this, [=]{calculateSeries();});
    QObject::connect(askTargetFreq, &QSlider::valueChanged, this, [=]{calculateSeries();});
    QObject::connect(askShift, &QSlider::valueChanged, this, [=]{calculateSeries();});

    QObject::connect(fskAmp, &QSlider::valueChanged, this, [=]{calculateSeries();});
    QObject::connect(fskTargetFreq1, &QSlider::valueChanged, this, [=]{calculateSeries();});
    QObject::connect(fskTargetFreq2, &QSlider::valueChanged, this, [=]{calculateSeries();});
    QObject::connect(fskShift, &QSlider::valueChanged, this, [=]{calculateSeries();});

    QObject::connect(pskAmp, &QSlider::valueChanged, this, [=]{calculateSeries();});
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
    double askShift_l = static_cast<double>(askShift->value())/100;

    double fskAmp_l = static_cast<double>(fskAmp->value())/100;
    double fskTargetFreq1_l = static_cast<double>(fskTargetFreq1->value())/100;
    double fskTargetFreq2_l = static_cast<double>(fskTargetFreq2->value())/100;
    double fskShift_l = static_cast<double>(fskShift->value())/100;

    double pskAmp_l = static_cast<double>(pskAmp->value())/100;
    double pskTargetFreq_l = static_cast<double>(pskTargetFreq->value())/100;
    double pskShift1_l = static_cast<double>(pskShift1->value())/100;
    double pskShift2_l = static_cast<double>(pskShift2->value())/100;

    QBitArray bits = bitsFromString(input->text());
    double bitLim = (bitLimit->value()>bits.count()) ? bits.count() : bitLimit->value();
    double range = deltaT->value() * bitLim;
    double step = range/steps->value();

    for(int i=0; i<steps->value(); i++)
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
        for(int i=0; i<steps->value(); i++)
        {
            series->append(vecX.at(i), vecY.at(i));
        }
        chartView->chart()->addSeries(series);
    }
    if(ask->checkState()==2)
    {
        double y;
        QLineSeries* series = new QLineSeries(this);
        for(int i=0; i<steps->value(); i++)
        {
            if(vecY.at(i))
                y = (askAmp1_l)*(sin(2*M_PI*askTargetFreq_l*vecX.at(i)+askShift_l));
            else
                y = (askAmp2_l)*(sin(2*M_PI*askTargetFreq_l*vecX.at(i)+askShift_l));
            series->append(vecX.at(i), y);
        }
        chartView->chart()->addSeries(series);
    }
    if(fsk->checkState()==2)
    {
        double y;
        QLineSeries* series = new QLineSeries(this);
        for(int i=0; i<steps->value(); i++)
        {
            if(vecY.at(i))
                y = (fskAmp_l)*(sin(2*M_PI*fskTargetFreq1_l*vecX.at(i)+fskShift_l));
            else
                y = (fskAmp_l)*(sin(2*M_PI*fskTargetFreq2_l*vecX.at(i)+fskShift_l));
            series->append(vecX.at(i), y);
        }
        chartView->chart()->addSeries(series);
    }
    if(psk->checkState()==2)
    {
        double y;
        QLineSeries* series = new QLineSeries(this);
        for(int i=0; i<steps->value(); i++)
        {
            if(vecY.at(i))
                y = (pskAmp_l)*(sin(2*M_PI*pskTargetFreq_l*vecX.at(i)+pskShift1_l));
            else
                y = (pskAmp_l)*(sin(2*M_PI*pskTargetFreq_l*vecX.at(i)+pskShift2_l));
            series->append(vecX.at(i), y);
        }
        chartView->chart()->addSeries(series);
    }
    chartView->chart()->createDefaultAxes();
    if(chartView->chart()->axes(Qt::Vertical).length()>0)
    {
        QValueAxis* axisY = (QValueAxis*)chartView->chart()->axes(Qt::Vertical)[0];
        double addRange = (axisY->max() - axisY->min())*0.10;
        axisY->setMax(axisY->max()+addRange);
        axisY->setMin(axisY->min()-addRange);
    }
}

QBitArray Lab5::bitsFromString(QString s)
{
    QByteArray ba = s.toLocal8Bit();
    const char* c = ba.data();
    return QBitArray::fromBits(c,ba.size()*8);
}

