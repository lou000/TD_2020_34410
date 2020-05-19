#include "lab7.h"

Lab7::Lab7(QWidget *parent) : QWidget(parent)
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
    auto modSelection = new QGroupBox("Display:", this);
    auto msLayout = new QGridLayout();
    modSelection->setLayout(msLayout);
    modSelection->setMinimumWidth(200);
    this->clk = new QCheckBox("CLK");
    msLayout->addWidget(clk, 0, 0, Qt::AlignLeft);
    this->clkFrq = new QSpinBox(this);
    this->clkFrq->setAlignment(Qt::AlignRight);
    this->clkFrq->setMaximumWidth(80);
    this->clkFrq->setMaximum(200);
    this->clkFrq->setMinimum(1);
    this->clkFrq->setValue(16);
    msLayout->addWidget(new QLabel(" Freq:", this), 0, 1, Qt::AlignRight);
    msLayout->addWidget(clkFrq, 0, 2, Qt::AlignLeft);
    this->ttl = new QCheckBox("TTL");
    msLayout->addWidget(ttl, 1, 0, Qt::AlignLeft);
    this->man = new QCheckBox("Manchester");
    msLayout->addWidget(man, 1, 1, 1, 2, Qt::AlignLeft);
    this->nrzi = new QCheckBox("NRZI");
    msLayout->addWidget(nrzi, 2, 0, Qt::AlignLeft);
    this->bami = new QCheckBox("BAMI");
    msLayout->addWidget(bami, 2, 1, 1, 2, Qt::AlignLeft);
    this->decode = new QCheckBox("Decode");
    msLayout->addWidget(decode, 3, 0, 1, 2, Qt::AlignLeft);
    leftBarLayout->addWidget(modSelection, 0, 0 , 1, 4, Qt::AlignHCenter);


    ////////////////////INPUT SETTINGS//////////////////////
    auto inputSettings = new QGroupBox("Input settings:", this);
    auto inputLayout = new QGridLayout();
    inputSettings->setLayout(inputLayout);
    inputSettings->setMinimumWidth(200);

    this->input = new QLineEdit("51",this);
    inputLayout->addWidget(new QLabel("Input:", this), 0, 0, Qt::AlignLeft);
    inputLayout->addWidget(input, 0, 1, 1, 5, Qt::AlignHCenter);

    this->bitLimit = new QSpinBox(this);
    this->bitLimit->setAlignment(Qt::AlignRight);
    this->bitLimit->setMaximumWidth(80);
    this->bitLimit->setMaximum(999999);
    this->bitLimit->setMinimum(1);
    this->bitLimit->setValue(16);
    inputLayout->addWidget(new QLabel("Bit Limit:", this), 1, 0, Qt::AlignLeft);
    inputLayout->addWidget(bitLimit, 1, 1, 1, 5, Qt::AlignHCenter);

    this->endian = new QComboBox(this);
    this->endian->addItem("Big Endian");
    this->endian->addItem("Little Endian");
    inputLayout->addWidget(new QLabel("Endian:", this), 2, 0, Qt::AlignLeft);
    inputLayout->addWidget(endian, 2, 1, 1, 5, Qt::AlignHCenter);
    leftBarLayout->addWidget(inputSettings, 1, 0 , 1, 4, Qt::AlignHCenter);


    /////////////RANGE SELECTION GROUP/////////////
    auto range = new QGroupBox("Range:", this);
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
    this->steps->setValue(1000);
    rangeLayout->addWidget(new QLabel("Steps:", this), 1, 0, Qt::AlignLeft);
    rangeLayout->addWidget(steps, 1, 1, 1, 2, Qt::AlignLeft);

    leftBarLayout->addWidget(range, 2, 0 , 1, 4, Qt::AlignHCenter);


    /////////////DECODE OUTPUT////////////////
    auto dec = new QGroupBox("Decode output:", this);
    auto decLayout = new QGridLayout();
    dec->setLayout(decLayout);
    dec->setMinimumWidth(200);

    this->decodeOutput = new QPlainTextEdit(this);
    decodeOutput->setReadOnly(true);
    decodeOutput->setMinimumHeight(100);
    decLayout->addWidget(decodeOutput,0,0, Qt::AlignHCenter);

    leftBarLayout->addWidget(dec, 3, 0 , 1, 4, Qt::AlignHCenter);


    QObject::connect(clk, &QCheckBox::stateChanged, this, [=]{displaySeries();});
    QObject::connect(clkFrq, &QSpinBox::textChanged, this, [=]{displaySeries();});
    QObject::connect(ttl, &QCheckBox::stateChanged, this, [=]{displaySeries();});
    QObject::connect(man, &QCheckBox::stateChanged, this, [=]{displaySeries();});
    QObject::connect(nrzi, &QCheckBox::stateChanged, this, [=]{displaySeries();});
    QObject::connect(decode, &QCheckBox::stateChanged, this, [=]{displaySeries();});

    QObject::connect(input, &QLineEdit::textEdited, this, [=]{displaySeries();});
    QObject::connect(bitLimit, &QSpinBox::textChanged, this, [=]{displaySeries();});
    QObject::connect(endian, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=]{displaySeries();});

    QObject::connect(rangeFrom, &QDoubleSpinBox::editingFinished, this, [=]{displaySeries();});
    QObject::connect(rangeTo, &QDoubleSpinBox::editingFinished, this, [=]{displaySeries();});
    QObject::connect(steps, &QSpinBox::textChanged, this, [=]{displaySeries();});
    displaySeries();
}

void Lab7::displaySeries()
{
    QVector<LabSeries> labSeries;
    double rangeF = rangeFrom->value();
    double rangeT = rangeTo->value();
    int clkVal = clkFrq->value();
    QString inputVal = input->text();
    int stepsVal = steps->value();
    int bitLimitVal = bitLimit->value();
    Endian endianVal = (endian->currentIndex()>0) ? LittleEndian : BigEndian;

    LabSeries clkSignal = genCLK(clkVal, rangeF, rangeT, stepsVal);
    QBitArray bits = bitsFromString(inputVal, endianVal);
    bits.resize(bitLimitVal);
    decodeOutput->clear();

    if(clk->checkState()==2)
        labSeries.append(clkSignal);
    if(ttl->checkState()==2)
    {
        auto mTTL = modTTL(clkSignal, bits);
        labSeries.append(mTTL);
        if(decode->checkState()==2)
            decodeOutput->appendPlainText("TTL :  "+stringFromBits(decTTL(clkVal, mTTL), endianVal)+"\n");
    }
    if(man->checkState()==2)
    {
        auto mMan = modManchester(clkSignal, bits);
        labSeries.append(mMan);
//        if(decode->checkState()==2)
//            decodeOutput->appendPlainText("Manchester: "+stringFromBits(decManchester(clkSignal, mMan), endianVal)+"\n");
    }
//    if(nrzi->checkState()==0)
//    {
//        auto mNRZI = modNRZI(clkSignal, bits);
//        labSeries.append(mNRZI);
//        if(decode->checkState()==2)
//            decodeOutput->appendPlainText("NRZI: "+stringFromBits(decNRZI(clkSignal, mNRZI), endianVal)+"\n");
//    }
//    if(bami->checkState()==0)
//    {
//        auto mBAMI = modBAMI(clkSignal, bits);
//        labSeries.append(mBAMI);
//        if(decode->checkState()==2)
//            decodeOutput->appendPlainText("BAMI: "+stringFromBits(decBAMI(clkSignal, mBAMI), endianVal)+"\n");
//    }
    chartView->chart()->removeAllSeries();
    addSeriesToChart(labSeries);
    chartView->chart()->createDefaultAxes();
    if(chartView->chart()->axes(Qt::Vertical).length()>0)
    {
        QValueAxis* axisY = (QValueAxis*)chartView->chart()->axes(Qt::Vertical)[0];
        double addRange = (axisY->max() - axisY->min())*2;
        axisY->setMax(axisY->max()+addRange);
        axisY->setMin(axisY->min()-addRange);
    }
}


void Lab7::addSeriesToChart(QVector<LabSeries> series)
{
    for(auto s : series)
    {
        auto temp = new QLineSeries();
        for(int i=0; i<s.xVec.length(); i++)
        {
            temp->append(s.xVec.at(i), s.yVec.at(i));
        }
        chartView->chart()->addSeries(temp);
    }
}

LabSeries Lab7::genCLK(double freq, double from, double to, int steps)
{
    QVector<double> x;
    QVector<double> y;
    double range = from-to;
    if(range<0)
        range = 1;
    double step = range/steps;
    double bitStep = (1/freq)/2;
    for(int i=0; i<steps; i++)
    {
        x.append(i*step);
        if((static_cast<int>(i*step/bitStep))%2)
            y.append(0);
        else
            y.append(1);
    }
    return LabSeries(x, y);
}

LabSeries Lab7::modTTL(LabSeries clock, QBitArray bits)
{
    QVector<double> y;
    QVector<double> x;
    bool high = true;
    for(int i=0, bit=0; i<clock.yVec.length();i++)
    {
        if(clock.yVec.at(i) == 1 && high == false)
        {
            high = true;
            bit++;
        }
        if(clock.yVec.at(i) == 0 && high == true)
        {
            high = false;
        }
        if(bit>=bits.count())
            y.append(0);
        else
            y.append(bits.at(bit));
        x.append(clock.xVec.at(i));
    }
    return LabSeries(x, y);
}

LabSeries Lab7::modManchester(LabSeries clock, QBitArray bits)
{
    QVector<double> y;
    QVector<double> x;

    bool falling = false;
    bool rising = false;
    int prevClock = round(clock.yVec.first());
    int mod = 0;
    for(int i=0, bit=0; i<clock.yVec.length();i++)
    {
        int clk = round(clock.yVec.at(i));
        if(prevClock==0 && clk == 1)
            rising = true;
        if(prevClock==1 && clk == 0)
            falling = true;
        if(prevClock==0 && clk == 1)
            bit++;
        if(bit<bits.count())
        {
            if(falling && bits.at(bit))
                mod = -1;
            if(falling && !bits.at(bit))
                mod = 1;
            if(bit>0)
                if(rising && (bits.at(bit)==bits.at(bit-1)))
                    mod = (mod == 1) ? -1 : 1;
        }
        else
            mod=0;

        prevClock = clk;
        rising = false;
        falling = false;
        y.append(mod);
        x.append(clock.xVec.at(i));
    }
    return LabSeries(x, y);
}

//LabSeries Lab7::modNRZI(LabSeries clock, QBitArray bits)
//{

//}

//LabSeries Lab7::modBAMI(LabSeries clock, QBitArray bits)
//{

//}

QBitArray Lab7::decTTL(int clockFreq, LabSeries mod)
{
    QBitArray bits;
    double x = (1/static_cast<double>(clockFreq))/2;
    bits.fill(false, static_cast<int>((mod.xVec.last()-mod.xVec.first())/x));
    int bit = 0;
    for(int i=0; x<mod.xVec.last(); i++)
    {
        if(mod.xVec.at(i)>x)
        {
            x+=1/static_cast<double>(clockFreq);
            bits.setBit(bit, mod.yVec.at(i)==1 ? true : false);
            bit++;
        }
    }
    bits.resize(bit);
    return bits;
}

QBitArray Lab7::decManchester(int clockFreq, LabSeries mod)
{
    QBitArray bits;
    double x = 0;
    bits.fill(false, static_cast<int>((mod.xVec.last()-mod.xVec.first())/x));
    int bit = 0;
    for(int i=0; x<mod.xVec.last(); i++)
    {
        if(mod.xVec.at(i)>x)
        {
            x+=1/static_cast<double>(clockFreq);
            bits.setBit(bit, mod.yVec.at(i)==1 ? true : false);
            bit++;
        }
    }
    bits.resize(bit);
    return bits;
}

//QBitArray Lab7::decNRZI(LabSeries clock, LabSeries mod)
//{

//}

//QBitArray Lab7::decBAMI(LabSeries clock, LabSeries mod)
//{

//}

QBitArray Lab7::bitsFromString(QString s, Endian e)
{
    QByteArray ba = s.toUtf8();
    const char* c = ba.data();
    QBitArray bitArr = QBitArray::fromBits(c,ba.size()*8);
    if(e == LittleEndian)
        reverseBitsInBytes(bitArr);
    return bitArr;
}

QString Lab7::stringFromBits(QBitArray bits, Endian e)
{
    if(e == LittleEndian)
        reverseBitsInBytes(bits);
    const char* c = bits.bits();
    qDebug()<<c<<QString(c);
    return QString(c);
}

void Lab7::reverseBitsInBytes(QBitArray &arr)
{
    //if byte is incomplete we dont reverse it
    for(int j = 1; j<=arr.count()/8; j++)
        for(int i=0; i<8;i++)
        {
            bool bit = arr.at(i*j);
            arr.setBit(i*j,arr.at(j*8 - i*j - 1));
            arr.setBit(j*8 - i*j-1, bit);
        }
}

