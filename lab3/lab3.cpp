#include "lab3.h"

Lab3::Lab3(QWidget *parent) : QWidget(parent)
{
    this->series = new QLineSeries(this);
    this->series->setColor(QColor("orchid"));
    this->series->setName("S(t)");

    auto mainLayout = new QGridLayout(this);
    auto leftBarLayout = new QGridLayout();
    auto leftBarWidget = new QWidget();
    leftBarWidget->setLayout(leftBarLayout);
    leftBarWidget->setMinimumWidth(220);
    leftBarWidget->setMaximumWidth(220);

    leftBarLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    leftBarLayout->setVerticalSpacing(5);

    mainLayout->addWidget(leftBarWidget,0,0,Qt::AlignLeft | Qt::AlignTop);

    auto chart = new QChart();
    chartView = new QChartViewWithZoomAndDrag(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setTheme(QChart::ChartThemeDark);
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
    this->rangeTo->setValue(114.0);
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
    this->amplitude->setMaximum(1000);
    this->amplitude->setMinimum(-1000);
    this->amplitude->setValue(100);
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
    this->frequency->setMinimum(-1000);
    this->frequency->setValue(200);
    varsLayout->addWidget(new QLabel("f:", this), 1, 0, Qt::AlignLeft);
    auto frequencyLabel = new QLabel(QString::number(frequency->value()/100),this);
    varsLayout->addWidget(frequencyLabel, 1, 2, Qt::AlignLeft);
    QObject::connect(frequency, &QSlider::sliderMoved, frequencyLabel,
                     [=](int pos){frequencyLabel->setText(QString::number(static_cast<double>(pos)/100));});
    varsLayout->addWidget(frequency, 1, 1, Qt::AlignLeft);

    this->phaseShift = new QSlider(this);
    this->phaseShift->setOrientation(Qt::Horizontal);
    this->phaseShift->setMinimumWidth(105);
    this->phaseShift->setTickInterval(1);
    this->phaseShift->setMaximum(1000);
    this->phaseShift->setMinimum(-1000);
    this->phaseShift->setValue(0);
    varsLayout->addWidget(new QLabel("S:", this), 2, 0, Qt::AlignLeft);
    auto phaseShiftLabel = new QLabel(QString::number(phaseShift->value()/100),this);
    varsLayout->addWidget(phaseShiftLabel, 2, 2, Qt::AlignLeft);
    QObject::connect(phaseShift, &QSlider::sliderMoved, phaseShiftLabel,
                     [=](int pos){phaseShiftLabel->setText(QString::number(static_cast<double>(pos)/100));});
    varsLayout->addWidget(phaseShift, 2, 1, Qt::AlignLeft);

    leftBarLayout->addWidget(vars, 3, 0 , 1, 4, Qt::AlignHCenter);

    //////////////SPECTRUM SETTINGS/////////////////////
    auto spectrumSettings = new QGroupBox("Spectrum Settings",this);
    auto ssLayout = new QGridLayout();
    spectrumSettings->setLayout(ssLayout);
    spectrumSettings->setMinimumWidth(200);
    spectrumSettings->setMaximumHeight(150);

    this->spectrum = new QCheckBox("Enable", this);
    this->DBscale = new QCheckBox("Decibal Scale", this);
    DBscale->setDisabled(true);
    this->shift = new QCheckBox("Shift", this);
    shift->setDisabled(true);
    this->normalize = new QCheckBox("Normalize", this);
    normalize->setDisabled(true);

    ssLayout->addWidget(spectrum,0,0,Qt::AlignLeft);
    ssLayout->addWidget(DBscale,0,1,Qt::AlignLeft);
    ssLayout->addWidget(shift,1,0,Qt::AlignLeft);
    ssLayout->addWidget(normalize,1,1,Qt::AlignLeft);

    leftBarLayout->addWidget(spectrumSettings, 4, 0, 1, 4, Qt::AlignHCenter);


    QObject::connect(funcSelection, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int v){selectedSeries(v);});
    QObject::connect(rangeFrom, &QDoubleSpinBox::editingFinished, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(rangeTo, &QDoubleSpinBox::editingFinished, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(steps, &QDoubleSpinBox::editingFinished, this, [=]{selectedSeries(funcSelection->currentIndex());});

    QObject::connect(amplitude, &QSlider::sliderMoved, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(frequency, &QSlider::sliderMoved, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(phaseShift, &QSlider::sliderMoved, this, [=]{selectedSeries(funcSelection->currentIndex());});

    QObject::connect(spectrum, &QCheckBox::stateChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(spectrum, &QCheckBox::stateChanged, this, [=](int state)
         {
            if(state==2)
            {
                DBscale->setDisabled(false);
                shift->setDisabled(false);
                normalize->setDisabled(false);
            }
            else
            {
                DBscale->setDisabled(true);
                shift->setDisabled(true);
                normalize->setDisabled(true);
            }
         });
    QObject::connect(DBscale, &QCheckBox::stateChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(shift, &QCheckBox::stateChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});
    QObject::connect(normalize, &QCheckBox::stateChanged, this, [=]{selectedSeries(funcSelection->currentIndex());});

    selectedSeries(0);
}

void Lab3::selectedSeries(int selection)
{
    switch(selection)
    {
    case 0:
        calculateSeries([this](double v)->double{return this->sFunction(v);});
        break;
    case 1:
        calculateSeries([this](double v)->double{return this->xFunction(v);});
        break;
    case 2:
        calculateSeries([this](double v)->double{return this->yFunction(v);});
        break;
    case 3:
        calculateSeries([this](double v)->double{return this->zFunction(v);});
        break;
    case 4:
        calculateSeries([this](double v)->double{return this->uFunction(v);});
        break;
    case 5:
        calculateSeries([this](double v)->double{return this->vFunction(v);});
        break;
    case 6:
        calculateSeries([this](double v)->double{return this->p1Function(v);});
        break;
    case 7:
        calculateSeries([this](double v)->double{return this->p2Function(v);});
        break;
    case 8:
        calculateSeries([this](double v)->double{return this->p3Function(v);});
        break;
    default:
        return;
    }
}

void Lab3::calculateSeries(std::function<double(double)> foo)
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
    if(spectrum->checkState()==2)
    {
        QVector<double> temp;
        for(double x = rangeF, ns = 0; x<=rangeT && ns<stepsVal; x+=step, ns++)
        {
            temp.append(foo(x));
        }
        QVector<std::complex<double>> results = calculateDFT(temp);
        if(shift->checkState()==2)
        {
            for(int i=0;i<=results.length()/2;i++)
            {
                auto temp = results.front();
                results.pop_front();
                results.append(temp);
            }
        }
        for(int k = 0; k<results.length(); k++)
        {
            double y = abs(results.at(k));
            if(DBscale->checkState()==2)
            {
                y = 10*log10(y);
            }
            if(normalize->checkState()==2)
            {
                y = y/(stepsVal/2);
            }
            double x=(k*(fs/stepsVal));
            if(shift->checkState()==2)
                x-=fs/2;
            series->append(x, y);
        }
    }
    else
    {
        for(double x = rangeF; x<=rangeT; x+=step)
        {
            series->append(x,foo(x));
        }
    }

    chartView->chart()->addSeries(series);
    chartView->chart()->createDefaultAxes();
}

QVector<std::complex<double>> Lab3::calculateDFT(QVector<double> signal)
{
    int steps = signal.length();
    QVector<std::complex<double>> temp;
    for(int k = 0; k<steps; k++)
    {
        std::complex<double> sum(0,0);
        for(int n = 0; n<steps; n++)
        {
            double real = cos((((2*M_PI)/steps)*k*n));
            double imag = -sin((((2*M_PI)/steps)*k*n));
            std::complex<double> w(real, imag);
            sum+=signal.at(n)*w;
        }
        temp.append(sum);
    }
    return temp;
}

double Lab3::sFunction(double x)
{
    double amp = static_cast<double>(amplitude->value())/100;
    double freq = static_cast<double>(frequency->value())/100;
    double pShift = static_cast<double>(phaseShift->value())/100;
    return amp*sin(2*M_PI*freq*x+pShift);
}

double Lab3::xFunction(double x)
{
    return 1*x*x+1*x+4;
}

double Lab3::yFunction(double x)
{
    return 2*(xFunction(x))*(xFunction(x))+12*qCos(x);
}

double Lab3::zFunction(double x)
{
    return qSin(2*M_PI*7*x)*xFunction(x) - 0.2*log10(abs(yFunction(x))+M_PI);
}

double Lab3::uFunction(double x)
{
    return sqrt(abs(yFunction(x)*yFunction(x)*zFunction(x)))
           - 1.8*sin(0.4*x*zFunction(x)*xFunction(x));
}

double Lab3::vFunction(double x)
{
    if(x<0.22)
        return (1-7*x)*qSin((2*M_PI*x*10)/(x+0.04));
    else if(x>=0.22 && x<=0.7)
        return 0.63*x*qSin(125*x);
    else
        return qPow(x, -0.662)+0.77*qSin(8*x);
}

double Lab3::p1Function(double x)
{
    double y=0;
    for(int number=1; number<=2; number++)
    {
        y += (qCos(12*x*number*number) + qCos(16*x*number))/(number*number);
    }
    return y;
}

double Lab3::p2Function(double x)
{
    double y=0;
    for(int number=1; number<=4; number++)
    {
        y += (qCos(12*x*number*number) + qCos(16*x*number))/(number*number);
    }
    return y;
}

double Lab3::p3Function(double x)
{
    double y=0;
    for(int number=1; number<=99; number++)
    {
        y += (qCos(12*x*number*number) + qCos(16*x*number))/(number*number);
    }
    return y;
}
