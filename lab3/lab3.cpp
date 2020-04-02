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
    this->rangeTo->setValue(1.0);
    rangeLayout->addWidget(new QLabel("To:", this), 0, 2, Qt::AlignRight);
    rangeLayout->addWidget(rangeTo, 0, 3, Qt::AlignLeft);

    this->steps = new QSpinBox(this);
    this->steps->setAlignment(Qt::AlignRight);
    this->steps->setMaximumWidth(80);
    this->steps->setMaximum(999999);
    this->steps->setMinimum(1);
    this->steps->setValue(20);
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
    auto amplitudeLabel = new QLabel(QString::number(1),this);
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
    this->frequency->setValue(100);
    varsLayout->addWidget(new QLabel("f:", this), 1, 0, Qt::AlignLeft);
    auto frequencyLabel = new QLabel(QString::number(1),this);
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
    this->phaseShift->setValue(100);
    varsLayout->addWidget(new QLabel("S:", this), 2, 0, Qt::AlignLeft);
    auto phaseShiftLabel = new QLabel(QString::number(1),this);
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

    ssLayout->addWidget(spectrum,0,0,Qt::AlignLeft);
    ssLayout->addWidget(DBscale,0,1,Qt::AlignRight);
    leftBarLayout->addWidget(spectrumSettings, 4, 0, 1, 4, Qt::AlignHCenter);



    QObject::connect(rangeFrom, &QDoubleSpinBox::editingFinished, this, [=]{calculateSeries();});
    QObject::connect(rangeTo, &QDoubleSpinBox::editingFinished, this, [=]{calculateSeries();});
    QObject::connect(steps, &QDoubleSpinBox::editingFinished, this, [=]{calculateSeries();});

    QObject::connect(amplitude, &QSlider::sliderMoved, this, [=]{calculateSeries();});
    QObject::connect(frequency, &QSlider::sliderMoved, this, [=]{calculateSeries();});
    QObject::connect(phaseShift, &QSlider::sliderMoved, this, [=]{calculateSeries();});

    QObject::connect(spectrum, &QCheckBox::stateChanged, this, [=]{calculateSeries();});
    QObject::connect(DBscale, &QCheckBox::stateChanged, this, [=]{calculateSeries();});

    calculateSeries();
}

void Lab3::calculateSeries()
{
    double amp = static_cast<double>(amplitude->value())/100;
    double freq = static_cast<double>(frequency->value())/100;
    double pShift = static_cast<double>(phaseShift->value())/100;
    double rangeF = rangeFrom->value();
    double rangeT = rangeTo->value();
    double step = (rangeT-rangeF)/steps->value();

    if(rangeF>=rangeT || step<=0)
        return;
    if(chartView->chart()->series().contains(series))
        chartView->chart()->removeSeries(series);
    series->clear();
    if(spectrum->checkState()==2)
    {
        double fs = 1/step;
        QVector<double> temp;
        for(double x = rangeF; x<=rangeT; x+=step)
        {
            temp.append(amp*sin(2*M_PI*freq*x+pShift));
        }
        QVector<std::complex<double>> results = calculateDFT(temp);
        QVector<double> test;
        for(auto result : results)
        {
            test.append(std::abs(result));
        }
        int x = 0;
        for(int k = 1; k<=results.length(); k++)
        {
            double y = std::abs(results.at(k-1));
            if(DBscale->checkState()==2)
            {
                y = 10*log10(y);
            }
            series->append(x, std::abs(results.at(k-1)));
            x+=k*(fs/results.length());
            qDebug()<<"x:"<<x<<"y:"<<y;
        }
    }
    else
    {
        for(double x = rangeF; x<=rangeT; x+=step)
        {
            series->append(x,amp*sin(2*M_PI*freq*x+pShift));
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
