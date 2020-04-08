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

    leftBarLayout->addWidget(vars, 3, 0 , 1, 4, Qt::AlignHCenter);

    //////////////SIGNAL VARIABLES/////////////////////
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
    this->modAmplitude->setMinimum(-1000);
    this->modAmplitude->setValue(100);
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
    this->modFrequency->setMaximum(1000);
    this->modFrequency->setMinimum(-1000);
    this->modFrequency->setValue(200);
    varsModLayout->addWidget(new QLabel("f:", this), 1, 0, Qt::AlignLeft);
    auto frequencyModLabel = new QLabel(QString::number(modFrequency->value()/100),this);
    varsModLayout->addWidget(frequencyModLabel, 1, 2, Qt::AlignLeft);
    QObject::connect(modFrequency, &QSlider::sliderMoved, frequencyModLabel,
                     [=](int pos){frequencyModLabel->setText(QString::number(static_cast<double>(pos)/100));});
    varsModLayout->addWidget(modFrequency, 1, 1, Qt::AlignLeft);

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
    spectrumSettings->setMaximumHeight(150);

    this->spectrum = new QCheckBox("Enable DFT", this);
    this->reverse = new QCheckBox("Reverse DFT", this);
    reverse->setDisabled(true);
    this->logYScale = new QCheckBox("Decibal Scale", this);
    logYScale->setDisabled(true);
    this->shift = new QCheckBox("Shift", this);
    shift->setDisabled(true);
    this->normalize = new QCheckBox("Normalize", this);
    normalize->setDisabled(true);

    ssLayout->addWidget(spectrum,0,0,Qt::AlignLeft);
    ssLayout->addWidget(reverse,0,1,Qt::AlignLeft);
    ssLayout->addWidget(shift,1,0,Qt::AlignLeft);
    ssLayout->addWidget(logYScale,1,1,Qt::AlignLeft);
    ssLayout->addWidget(normalize,2,0,Qt::AlignLeft);
    leftBarLayout->addWidget(spectrumSettings, 6, 0, 1, 4, Qt::AlignHCenter);
}

QVector<double> Lab4::modulateAmplitude(QVector<double> x, double modFreq, double modAmp)
{
    return QVector<double>{};
}

QVector<double> Lab4::modulatePhase(QVector<double> x, double modFreq, double modAmp)
{
    return QVector<double>{};
}

void Lab4::selectedSeries(int selection)
{

}

void Lab4::calculateSeries(std::function<double (double)> foo)
{

}

double Lab4::sFunction(double x)
{
    return 0;
}
