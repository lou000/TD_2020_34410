#include "lab2.h"

Lab2::Lab2(QWidget *parent) : QWidget(parent)
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
    chartView = new QChartView(chart, this);
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
    this->steps->setValue(2000);
    rangeLayout->addWidget(new QLabel("Steps:", this), 1, 0, Qt::AlignLeft);
    rangeLayout->addWidget(steps, 1, 1, 1, 2, Qt::AlignLeft);

    leftBarLayout->addWidget(range, 2, 0 , 1, 4, Qt::AlignHCenter);

    //////////////SIGNAL VARIABLES/////////////////////
    auto vars = new QGroupBox("Signal Variables",this);
    auto varsLayout = new QGridLayout();
    vars->setLayout(varsLayout);
    vars->setMinimumWidth(200);
    vars->setMaximumHeight(150);

    this->amplitude = new QDoubleSpinBox(this);
    this->amplitude->setAlignment(Qt::AlignRight);
    this->amplitude->setMaximumWidth(70);
    this->amplitude->setMaximum(999);
    this->amplitude->setMinimum(-999);
    this->amplitude->setValue(1.0);
    varsLayout->addWidget(new QLabel("Amplitude:", this), 0, 0, Qt::AlignRight);
    varsLayout->addWidget(amplitude, 0, 1, Qt::AlignLeft);

    this->frequency = new QDoubleSpinBox(this);
    this->frequency->setAlignment(Qt::AlignRight);
    this->frequency->setMaximumWidth(70);
    this->frequency->setMaximum(999);
    this->frequency->setMinimum(-999);
    this->frequency->setValue(1.0);
    varsLayout->addWidget(new QLabel("Frequency:", this), 1, 0, Qt::AlignRight);
    varsLayout->addWidget(frequency, 1, 1, Qt::AlignLeft);

    this->phaseShift = new QDoubleSpinBox(this);
    this->phaseShift->setAlignment(Qt::AlignRight);
    this->phaseShift->setMaximumWidth(70);
    this->phaseShift->setMaximum(999);
    this->phaseShift->setMinimum(-999);
    this->phaseShift->setValue(4*M_PI);
    varsLayout->addWidget(new QLabel("Phase Shift:", this), 2, 0, Qt::AlignRight);
    varsLayout->addWidget(phaseShift, 2, 1, Qt::AlignLeft);

    leftBarLayout->addWidget(vars, 3, 0 , 1, 4, Qt::AlignHCenter);

    /////////////////QUANTIZATION//////////////////////
    auto quant = new QGroupBox("Quantization",this);
    auto quantLayout = new QGridLayout();
    quant->setLayout(quantLayout);
    quant->setMinimumWidth(200);
    quant->setMaximumHeight(150);

    this->quantize = new QCheckBox("Enable",this);
    quantLayout->addWidget(quantize,0,0,1,2,Qt::AlignHCenter);

    this->quantizationResolution = new QLineEdit("2^16",this);
    this->quantizationResolution->setAlignment(Qt::AlignRight);
    this->quantizationResolution->setValidator(new QRegExpValidator(QRegExp("[[0-9]\\^[0-9]{1,2}"), this));
    this->quantizationResolution->setMaximumWidth(80);
    quantLayout->addWidget(new QLabel("Quantization\nresolution:", this), 1, 0, Qt::AlignRight);
    quantLayout->addWidget(quantizationResolution, 1, 1, Qt::AlignLeft | Qt::AlignBottom);

    leftBarLayout->addWidget(quant, 4, 0 , 1, 4, Qt::AlignHCenter);

    QObject::connect(rangeFrom, &QDoubleSpinBox::editingFinished, this, [=]{calculateSeries();});
    QObject::connect(rangeTo, &QDoubleSpinBox::editingFinished, this, [=]{calculateSeries();});
    QObject::connect(steps, &QDoubleSpinBox::editingFinished, this, [=]{calculateSeries();});

    QObject::connect(amplitude, &QDoubleSpinBox::editingFinished, this, [=]{calculateSeries();});
    QObject::connect(frequency, &QDoubleSpinBox::editingFinished, this, [=]{calculateSeries();});
    QObject::connect(phaseShift, &QSpinBox::editingFinished, this, [=]{calculateSeries();});

    QObject::connect(quantize, &QCheckBox::stateChanged, this, [=]{calculateSeries();});
    QObject::connect(quantizationResolution, &QLineEdit::editingFinished, this, [=]{calculateSeries();});

    calculateSeries();
}

void Lab2::calculateSeries()
{
    double amp = amplitude->value();
    double freq = frequency->value();
    double pShift = phaseShift->value();
    double rangeF = rangeFrom->value();
    double rangeT = rangeTo->value();
    double step = (rangeT-rangeF)/steps->value();

    if(chartView->chart()->series().contains(series))
        chartView->chart()->removeSeries(series);
    series->clear();
    if(quantize->isChecked())
    {
        QStringList temp = quantizationResolution->text().split("^");
        Q_ASSERT(temp.length()==2);
        int quantRes = pow(temp[0].toInt(), temp[1].toInt());
        double resStep = 2*amp/quantRes;

        for(double x = rangeF; x<=rangeT; x+=step)
        {
            double y = amp*sin(2*M_PI*freq*x+pShift);
            y = qRound(y/resStep)*resStep;
            series->append(x,y);
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
