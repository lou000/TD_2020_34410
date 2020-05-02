#include "lab4.h"

Lab4::Lab4(QWidget *parent) : QWidget(parent)
{
    this->series = new QLineSeries(this);
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

    /////////////FUNCTION SELECTION////////////////
    this->funcSelection = new QComboBox(this);
    funcSelection->addItem("S(t)");
    funcSelection->addItem("X(t)");
    funcSelection->addItem("Y(t)");
    funcSelection->addItem("Z(t)");
    funcSelection->addItem("U(t)");
    funcSelection->addItem("V(t)");
    funcSelection->addItem("P1(t)");
    funcSelection->addItem("P2(t)");
    funcSelection->addItem("P3(t)");
    funcSelection->setMinimumWidth(150);
    leftBarLayout->addWidget(funcSelection, 0, 0, 1, 4, Qt::AlignHCenter);

    /////////////RANGE SELECTION GROUP/////////////
    auto range = new QGroupBox("Range", this);
    auto rangeLayout = new QGridLayout();
    range->setLayout(rangeLayout);
    range->setMinimumWidth(200);
    range->setMaximumHeight(150);

    this->rangeFrom = new QDoubleSpinBox(this);
    this->rangeFrom->setAlignment(Qt::AlignRight);
    this->rangeFrom->setMaximumWidth(50);
    this->rangeFrom->setMaximum(999);
    this->rangeFrom->setMinimum(-999);
    this->rangeFrom->setValue(0.0);
    rangeLayout->addWidget(new QLabel("From:", this), 0, 0, Qt::AlignRight);
    rangeLayout->addWidget(rangeFrom, 0, 1, Qt::AlignLeft);

    this->rangeTo = new QDoubleSpinBox(this);
    this->rangeTo->setAlignment(Qt::AlignRight);
    this->rangeTo->setMaximumWidth(50);
    this->rangeTo->setMaximum(999);
    this->rangeTo->setMinimum(-999);
    this->rangeTo->setValue(3.0);
    rangeLayout->addWidget(new QLabel("To:", this), 0, 2, Qt::AlignRight);
    rangeLayout->addWidget(rangeTo, 0, 3, Qt::AlignLeft);

    this->steps = new QSpinBox(this);
    this->steps->setAlignment(Qt::AlignRight);
    this->steps->setMaximumWidth(80);
    this->steps->setMaximum(999999);
    this->steps->setMinimum(1);
    this->steps->setValue(1000);
    rangeLayout->addWidget(new QLabel("Steps:", this), 1, 0, Qt::AlignLeft);
    rangeLayout->addWidget(steps, 1, 1, 1, 2, Qt::AlignLeft);

    leftBarLayout->addWidget(range, 2, 0 , 1, 4, Qt::AlignHCenter);

    //////////////SIGNAL VARIABLES/////////////////////
    auto vars = new QGroupBox("Signal Variables",this);
    auto varsLayout = new QGridLayout();
    vars->setLayout(varsLayout);
    vars->setMinimumWidth(200);
    vars->setMaximumHeight(150);

    this->amplitude = new QSlider(this);
    this->amplitude->setOrientation(Qt::Horizontal);
    this->amplitude->setMinimumWidth(105);
    this->amplitude->setTickInterval(1);
    this->amplitude->setMaximum(200);
    this->amplitude->setMinimum(0);
    this->amplitude->setValue(50);
    varsLayout->addWidget(new QLabel("A:", this), 0, 0, Qt::AlignLeft);
    auto amplitudeLabel = new QLabel(QString::number(static_cast<double>(amplitude->value())/100),this);
    varsLayout->addWidget(amplitudeLabel, 0, 2, Qt::AlignLeft);
    QObject::connect(amplitude, &QSlider::sliderMoved, amplitudeLabel,
                     [=](int pos){amplitudeLabel->setText(QString::number(static_cast<double>(pos)/100));});
    varsLayout->addWidget(amplitude, 0, 1, Qt::AlignLeft);

    this->frequency = new QSlider(this);
    this->frequency->setOrientation(Qt::Horizontal);
    this->frequency->setMinimumWidth(105);
    this->frequency->setTickInterval(1);
    this->frequency->setMaximum(1000);
    this->frequency->setMinimum(0);
    this->frequency->setValue(50);
    varsLayout->addWidget(new QLabel("f:", this), 1, 0, Qt::AlignLeft);
    auto frequencyLabel = new QLabel(QString::number(frequency->value()/100),this);
    varsLayout->addWidget(frequencyLabel, 1, 2, Qt::AlignLeft);
    QObject::connect(frequency, &QSlider::sliderMoved, frequencyLabel,
                     [=](int pos){frequencyLabel->setText(QString::number(static_cast<double>(pos)/100));});
    varsLayout->addWidget(frequency, 1, 1, Qt::AlignLeft);

    leftBarLayout->addWidget(vars, 3, 0 , 1, 4, Qt::AlignHCenter);

    //////////////MODULATION VARIABLES/////////////////////
    auto varsMod = new QGroupBox("Modulation Variables",this);
    auto varsModLayout = new QGridLayout();
    varsMod->setLayout(varsModLayout);
    varsMod->setMinimumWidth(200);
    varsMod->setMaximumHeight(150);

    this->modAmplitude = new QSlider(this);
    this->modAmplitude->setOrientation(Qt::Horizontal);
    this->modAmplitude->setMinimumWidth(105);
    this->modAmplitude->setTickInterval(1);
    this->modAmplitude->setMaximum(1000);
    this->modAmplitude->setMinimum(0);
    this->modAmplitude->setValue(400);
    varsModLayout->addWidget(new QLabel("A:", this), 0, 0, Qt::AlignLeft);
    auto amplitudeModLabel = new QLabel(QString::number(static_cast<double>(amplitude->value())/100),this);
    varsModLayout->addWidget(amplitudeModLabel, 0, 2, Qt::AlignLeft);
    QObject::connect(modAmplitude, &QSlider::sliderMoved, amplitudeModLabel,
                     [=](int pos){amplitudeModLabel->setText(QString::number(static_cast<double>(pos)/100));});
    varsModLayout->addWidget(modAmplitude, 0, 1, Qt::AlignLeft);

    this->modFrequency = new QSlider(this);
    this->modFrequency->setOrientation(Qt::Horizontal);
    this->modFrequency->setMinimumWidth(105);
    this->modFrequency->setTickInterval(1);
    this->modFrequency->setMaximum(10000);
    this->modFrequency->setMinimum(0);
    this->modFrequency->setValue(5000);
    varsModLayout->addWidget(new QLabel("f:", this), 1, 0, Qt::AlignLeft);
    auto frequencyModLabel = new QLabel(QString::number(static_cast<double>(modFrequency->value())/100),this);
    varsModLayout->addWidget(frequencyModLabel, 1, 2, Qt::AlignLeft);
    QObject::connect(modFrequency, &QSlider::sliderMoved, frequencyModLabel,
                     [=](int pos){frequencyModLabel->setText(QString::number(static_cast<double>(pos)/100));});
    varsModLayout->addWidget(modFrequency, 1, 1, Qt::AlignLeft);

    this->modKa = new QSlider(this);
    this->modKa->setOrientation(Qt::Horizontal);
    this->modKa->setMinimumWidth(105);
    this->modKa->setTickInterval(1);
    this->modKa->setMaximum(5000);
    this->modKa->setMinimum(0);
    this->modKa->setValue(50);
    varsModLayout->addWidget(new QLabel("kA:", this), 2, 0, Qt::AlignLeft);
    auto kALabel = new QLabel(QString::number(static_cast<double>(modKa->value())/100),this);
    varsModLayout->addWidget(kALabel, 2, 2, Qt::AlignLeft);
    QObject::connect(modKa, &QSlider::sliderMoved, kALabel,
                     [=](int pos){kALabel->setText(QString::number(static_cast<double>(pos)/100));});
    varsModLayout->addWidget(modKa, 2, 1, Qt::AlignLeft);

    this->modKp = new QSlider(this);
    this->modKp->setOrientation(Qt::Horizontal);
    this->modKp->setMinimumWidth(105);
    this->modKp->setTickInterval(1);
    this->modKp->setMaximum(5000);
    this->modKp->setMinimum(0);
    this->modKp->setValue(100);
    varsModLayout->addWidget(new QLabel("kP:", this), 3, 0, Qt::AlignLeft);
    auto kPLabel = new QLabel(QString::number(static_cast<double>(modKp->value())/100),this);
    varsModLayout->addWidget(kPLabel, 3, 2, Qt::AlignLeft);
    QObject::connect(modKp, &QSlider::sliderMoved, kPLabel,
                     [=](int pos){kPLabel->setText(QString::number(static_cast<double>(pos)/100));});
    varsModLayout->addWidget(modKp, 3, 1, Qt::AlignLeft);

    leftBarLayout->addWidget(varsMod, 4, 0 , 1, 4, Qt::AlignHCenter);

    //////////////MODULATION SETTINGS/////////////////////
    auto modSettings = new QGroupBox("Spectrum Settings",this);
    auto modLayout = new QGridLayout();
    modSettings->setLayout(modLayout);
    modSettings->setMinimumWidth(200);
    modSettings->setMaximumHeight(150);

    this->modAmpl = new QCheckBox("AM", this);
    this->modPhase = new QCheckBox("PM", this);

    modLayout->addWidget(modAmpl,0,0,Qt::AlignLeft);
    modLayout->addWidget(modPhase,0,1,Qt::AlignLeft);
    leftBarLayout->addWidget(modSettings, 5, 0, 1, 4, Qt::AlignHCenter);

    //////////////SPECTRUM SETTINGS/////////////////////
    auto spectrumSettings = new QGroupBox("Spectrum Settings",this);
    auto ssLayout = new QGridLayout();
    spectrumSettings->setLayout(ssLayout);
    spectrumSettings->setMinimumWidth(200);
    spectrumSettings->setMaximumHeight(200);

    this->spectrum = new QCheckBox("Enable DFT", this);
    this->reverse = new QCheckBox("Reverse DFT", this);
    reverse->setDisabled(true);
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
    ssLayout->addWidget(reverse,0,1,Qt::AlignLeft);
    ssLayout->addWidget(shift,1,0,Qt::AlignLeft);
    ssLayout->addWidget(logYScale,1,1,Qt::AlignLeft);
    ssLayout->addWidget(dbScale,2,1,Qt::AlignLeft);
    ssLayout->addWidget(normalize,2,0,Qt::AlignLeft);
    ssLayout->addWidget(zeroHighestVal,3,0,Qt::AlignLeft);
    leftBarLayout->addWidget(spectrumSettings, 6, 0, 1, 4, Qt::AlignHCenter);

    QObject::connect(funcSelection, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int v){selectedSeries(v);});
    QObject::connect(rangeFrom, &QDoubleSpinBox::editingFinished, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(rangeTo, &QDoubleSpinBox::editingFinished, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(steps, &QDoubleSpinBox::editingFinished, this, [=]{selectedSeries(funcSelection->currentIndex());});

    QObject::connect(amplitude, &QSlider::valueChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(frequency, &QSlider::valueChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});

    QObject::connect(modAmplitude, &QSlider::valueChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(modFrequency, &QSlider::valueChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(modKa, &QSlider::valueChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(modKp, &QSlider::valueChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});

    QObject::connect(modAmpl, &QCheckBox::stateChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(modAmpl, &QCheckBox::stateChanged, this, [=](int state)
                     {
                         if(state==2)
                         {
                             modPhase->setDisabled(true);
                         }
                         else
                         {
                             modPhase->setDisabled(false);
                         }
                     });
    QObject::connect(modPhase, &QCheckBox::stateChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(modPhase, &QCheckBox::stateChanged, this, [=](int state)
                     {
                         if(state==2)
                         {
                             modAmpl->setDisabled(true);
                         }
                         else
                         {
                             modAmpl->setDisabled(false);
                         }
                     });

    QObject::connect(spectrum, &QCheckBox::stateChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(spectrum, &QCheckBox::stateChanged, this, [=](int state)
                     {
                         if(state==2)
                         {
                             if(reverse->checkState()==2)
                                 reverse->setDisabled(false);
                             else
                             {
                                 logYScale->setDisabled(false);
                                 dbScale->setDisabled(false);
                                 shift->setDisabled(false);
                                 normalize->setDisabled(false);
                                 reverse->setDisabled(false);
                                 zeroHighestVal->setDisabled(false);
                             }
                         }
                         else
                         {
                             logYScale->setDisabled(true);
                             dbScale->setDisabled(true);
                             shift->setDisabled(true);
                             normalize->setDisabled(true);
                             reverse->setDisabled(true);
                             zeroHighestVal->setDisabled(true);
                         }
                     });
    QObject::connect(reverse, &QCheckBox::stateChanged, this, [=](int state)
                     {
                         if(state==2)
                         {
                             logYScale->setDisabled(true);
                             dbScale->setDisabled(true);
                             shift->setDisabled(true);
                             normalize->setDisabled(true);
                             zeroHighestVal->setDisabled(true);
                         }
                         else
                         {
                             logYScale->setDisabled(false);
                             dbScale->setDisabled(false);
                             shift->setDisabled(false);
                             normalize->setDisabled(false);
                             zeroHighestVal->setDisabled(false);
                         }
                     });
    QObject::connect(logYScale, &QCheckBox::stateChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});
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
    QObject::connect(dbScale, &QCheckBox::stateChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});
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
    QObject::connect(shift, &QCheckBox::stateChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(normalize, &QCheckBox::stateChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(reverse, &QCheckBox::stateChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(bandwidthFreq, &QSlider::valueChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(zeroHighestVal, &QCheckBox::stateChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});

    selectedSeries(0);
}

double Lab4::modulateAmplitude(std::function<double(double)> foo, double x, double modFreq, double kA)
{
    return (1+kA*foo(x))*cos(2*M_PI*modFreq*x);
}

double Lab4::modulatePhase(std::function<double(double)> foo, double x, double modFreq, double kP)
{
    return cos(2*M_PI*modFreq*x+kP*foo(x));
}

void Lab4::selectedSeries(int selection)
{
    switch(selection)
    {
    case 0:
        calculateSeries([this](double v)->double{return this->sFunction(v);});
        break;
    case 1:
        calculateSeries([](double v)->double{return Lab3::xFunction(v);});
        break;
    case 2:
        calculateSeries([](double v)->double{return Lab3::yFunction(v);});
        break;
    case 3:
        calculateSeries([](double v)->double{return Lab3::zFunction(v);});
        break;
    case 4:
        calculateSeries([](double v)->double{return Lab3::uFunction(v);});
        break;
    case 5:
        calculateSeries([](double v)->double{return Lab3::vFunction(v);});
        break;
    case 6:
        calculateSeries([](double v)->double{return Lab3::p1Function(v);});
        break;
    case 7:
        calculateSeries([](double v)->double{return Lab3::p2Function(v);});
        break;
    case 8:
        calculateSeries([](double v)->double{return Lab3::p3Function(v);});
        break;
    default:
        return;
    }
}

void Lab4::calculateSeries(std::function<double (double)> foo)
{
    double rangeF = rangeFrom->value();
    double rangeT = rangeTo->value();
    int stepsVal = steps->value();
    double step = (rangeT-rangeF)/stepsVal; // deltaT
    double fs = 1/step;

    if(rangeF>=rangeT || step<=0)
        return;
    if(chartView->chart()->series().contains(series))
        chartView->chart()->removeSeries(series);
    if(series->name()!=funcSelection->currentText())
    {
        series->setName(funcSelection->currentText());
        series->setColor(QColor::fromRgb(QRandomGenerator::global()->generate()));
    }
    series->clear();

    QVector<double> xVec;
    QVector<double> yVec;
    for(double x = rangeF, ns = 0; x<=rangeT && ns<stepsVal; x+=step, ns++)
    {
        if(modAmpl->checkState()==2)
        {
            yVec.append(modulateAmplitude(foo, x,
                                          static_cast<double>(modFrequency->value())/100,
                                          static_cast<double>(modKa->value())/100));
        }
        else if(modPhase->checkState()==2)
        {
            yVec.append(modulatePhase(foo, x,
                                      static_cast<double>(modFrequency->value())/100,
                                      static_cast<double>(modKp->value())/100));
        }
        else
        {
            yVec.append(foo(x));
        }
        xVec.append(x);
    }
    if(spectrum->checkState()==2)
    {
        double max = -INFINITY;
        QVector<std::complex<double>> results = Lab3::calculateDFT(yVec);
        if(shift->checkState()==2)
            for(int i=0;i<=results.length()/2;i++)
            {
                auto temp = results.front();
                results.pop_front();
                results.append(temp);
            }

        if(reverse->checkState()==2)
        {
            yVec = Lab3::reverseDFT(results);
        }
        else
        {
            yVec.clear();
            xVec.clear();
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
                yVec.append(y);
                xVec.append(x);
                if(y>max)
                    max=y;
            }
        }
        if(zeroHighestVal->checkState()==2)
        {
            for(auto& y : yVec)
                y-=max;
        }
    }

    for(int i=0; i<xVec.length() && i<yVec.length(); i++)
        series->append(xVec.at(i), yVec.at(i));

    chartView->chart()->addSeries(series);
    chartView->chart()->createDefaultAxes();

    if(logYScale->checkState()==2)
    {
        QLogValueAxis* axis = new QLogValueAxis(this);
        axis->setBase(10);
        auto temp = chartView->chart()->axes(Qt::Vertical);
        for(auto a : temp)
        {
            chartView->chart()->removeAxis(a);
            a->deleteLater();
        }
        chartView->chart()->addAxis(axis, Qt::AlignLeft);
        series->attachAxis(axis);
    }
    if(dbScale->checkState()==2)
    {
        QPair<double,double> minMax = calculateBandwidth(yVec, xVec, static_cast<double>(bandwidthFreq->value())/100);
        QCategoryAxis* axis = new QCategoryAxis(this);
        axis->setMin(xVec.first());
        axis->setMax(xVec.last());
        axis->setStartValue(minMax.first);
        QPen pen;
        pen.setColor("indianred");
        pen.setWidth(2);
        axis->setGridLinePen(pen);
        axis->append("Bandwidth: "+QString::number(minMax.second-minMax.first,'f',2), minMax.second);
        chartView->chart()->addAxis(axis, Qt::AlignBottom);
        auto temp = (QValueAxis*)chartView->chart()->axes(Qt::Vertical).at(0);
        QValueAxis* help = new QValueAxis(this);
        help->setRange(temp->min(), temp->max());
        help->setLabelFormat(" ");
        chartView->chart()->addAxis(help, Qt::AlignRight);
    }
}
QPair<double, double> Lab4::calculateBandwidth(QVector<double> yVal, QVector<double>xVal, double dec)
{
    double min = 0;
    double max = 0;
    bool gotMin = false;
    for(int i=0; i<xVal.length()/2; i++)
    {
        if(yVal.at(i)>dec)
        {
            if(gotMin)
                max = xVal.at(i);
            else
            {
                min = xVal.at(i);
                gotMin = true;
            }
        }
    }
    if(min==0)
        max=0;
    if(max==0)
        min=0;
    return QPair<double, double>(min, max);
}

QPair<double, double> Lab4::calculateBandwidth(QVector<QPointF> vec, double dec)
{
    double min = 0;
    double max = 0;
    bool gotMin = false;
    for(int i=0; i<vec.length()/2; i++)
    {
        if(vec.at(i).y()>dec)
        {
            if(gotMin)
                max = vec.at(i).x();
            else
            {
                min = vec.at(i).x();
                gotMin = true;
            }
        }
    }
    if(min==0)
        max=0;
    if(max==0)
        min=0;
    return QPair<double, double>(min, max);
}

double Lab4::sFunction(double x)
{
    double amp = static_cast<double>(amplitude->value())/100;
    double freq = static_cast<double>(frequency->value())/100;
    return amp*sin(2*M_PI*freq*x);
}
