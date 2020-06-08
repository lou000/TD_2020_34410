#include "lab7_8_9.h"

Lab7_8_9::Lab7_8_9(QWidget *parent) : QWidget(parent)
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
    this->clkFrq->setMaximum(50000);
    this->clkFrq->setMinimum(1);
    this->clkFrq->setValue(3000);
    msLayout->addWidget(new QLabel(" Freq:", this), 0, 1, Qt::AlignRight);
    msLayout->addWidget(clkFrq, 0, 2, Qt::AlignLeft);
    this->ttl = new QCheckBox("TTL");
    msLayout->addWidget(ttl, 1, 0, Qt::AlignLeft);
    this->man = new QCheckBox("Manchester");
    this->man->setChecked(true);
    msLayout->addWidget(man, 1, 1, 1, 2, Qt::AlignLeft);
    this->nrzi = new QCheckBox("NRZI");
    this->nrzi->setChecked(true);
    msLayout->addWidget(nrzi, 2, 0, Qt::AlignLeft);
    this->bami = new QCheckBox("BAMI");
    this->bami->setChecked(true);
    msLayout->addWidget(bami, 2, 1, 1, 2, Qt::AlignLeft);
    this->decode = new QCheckBox("Decode");
    this->decode->setChecked(true);
    msLayout->addWidget(decode, 3, 0, 1, 2, Qt::AlignLeft);
    leftBarLayout->addWidget(modSelection, 0, 0 , 1, 4, Qt::AlignHCenter);


    ////////////////////INPUT SETTINGS//////////////////////
    auto inputSettings = new QGroupBox("Input settings:", this);
    auto inputLayout = new QGridLayout();
    inputSettings->setLayout(inputLayout);
    inputSettings->setMinimumWidth(200);

    this->input = new QLineEdit("TRANSMISJA DANYCH",this);
    inputLayout->addWidget(new QLabel("Input:", this), 0, 0, Qt::AlignLeft);
    inputLayout->addWidget(input, 0, 1, 1, 5, Qt::AlignHCenter);

    this->bitLimit = new QSpinBox(this);
    this->bitLimit->setAlignment(Qt::AlignRight);
    this->bitLimit->setMaximumWidth(80);
    this->bitLimit->setMaximum(999999);
    this->bitLimit->setMinimum(1);
    this->bitLimit->setValue(2000);
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
    this->rangeTo->setValue(0.1);
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

    /////////////HAMMING CODE//////////////////////
    auto hammingCode = new QGroupBox("Hamming Code:", this);
    auto hamLayout = new QGridLayout();
    hammingCode->setLayout(hamLayout);
    hammingCode->setMinimumWidth(200);
    hammingCode->setMaximumHeight(150);
    this->hamming = new QCheckBox("Enable");
    hamLayout->addWidget(hamming, 0, 0, 1, 2, Qt::AlignLeft);

    this->errors = new QSpinBox(this);
    this->errors->setAlignment(Qt::AlignRight);
    this->errors->setMaximumWidth(80);
    this->errors->setMaximum(7);
    this->errors->setMinimum(0);
    this->errors->setValue(1);
    hamLayout->addWidget(new QLabel("Errors:", this), 0, 2, Qt::AlignRight);
    hamLayout->addWidget(errors, 0, 3, Qt::AlignRight);

    leftBarLayout->addWidget(hammingCode, 3, 0, 1, 4, Qt::AlignHCenter);

    ///////////////////NOISE//////////////////
    auto noiseBox = new QGroupBox("Noise:", this);
    auto noiseBoxLayout = new QGridLayout();
    noiseBox->setLayout(noiseBoxLayout);
    noiseBox->setMinimumWidth(200);

    this->noise = new QCheckBox("Enable");
    noiseBoxLayout->addWidget(noise, 0, 0, 1, 2, Qt::AlignLeft);

    this->spectrum = new QCheckBox("Spectrum");
    noiseBoxLayout->addWidget(spectrum, 0, 1, 1, 2, Qt::AlignLeft);

    this->noiseAlpha = new QDoubleSpinBox(this);
    this->noiseAlpha->setAlignment(Qt::AlignRight);
    this->noiseAlpha->setMaximumWidth(50);
    this->noiseAlpha->setMaximum(1);
    this->noiseAlpha->setMinimum(0);
    this->noiseAlpha->setValue(0.0);
    noiseBoxLayout->addWidget(new QLabel("Alpha:", this), 1, 0, Qt::AlignRight);
    noiseBoxLayout->addWidget(noiseAlpha, 1, 1, Qt::AlignLeft);

    leftBarLayout->addWidget(noiseBox, 4, 0, 1, 4, Qt::AlignHCenter);

    /////////////DECODE OUTPUT////////////////
    auto dec = new QGroupBox("Decode output:", this);
    auto decLayout = new QGridLayout();
    dec->setLayout(decLayout);
    dec->setMinimumWidth(200);

    this->decodeOutput = new QPlainTextEdit(this);
    decodeOutput->setReadOnly(true);
    decodeOutput->setMinimumHeight(100);
    decLayout->addWidget(decodeOutput,0,0, Qt::AlignHCenter);

    leftBarLayout->addWidget(dec, 5, 0 , 1, 4, Qt::AlignHCenter);


    QObject::connect(clk, &QCheckBox::stateChanged, this, [=]{displaySeries();});
    QObject::connect(clkFrq, &QSpinBox::textChanged, this, [=]{displaySeries();});
    QObject::connect(ttl, &QCheckBox::stateChanged, this, [=]{displaySeries();});
    QObject::connect(man, &QCheckBox::stateChanged, this, [=]{displaySeries();});
    QObject::connect(nrzi, &QCheckBox::stateChanged, this, [=]{displaySeries();});
    QObject::connect(bami, &QCheckBox::stateChanged, this, [=]{displaySeries();});
    QObject::connect(decode, &QCheckBox::stateChanged, this, [=]{displaySeries();});

    QObject::connect(input, &QLineEdit::textEdited, this, [=]{displaySeries();});
    QObject::connect(bitLimit, &QSpinBox::textChanged, this, [=]{displaySeries();});
    QObject::connect(endian, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=]{displaySeries();});

    QObject::connect(hamming, &QCheckBox::stateChanged, this, [=]{displaySeries();});
    QObject::connect(errors, &QSpinBox::textChanged, this, [=]{displaySeries();});

    QObject::connect(rangeFrom, &QDoubleSpinBox::editingFinished, this, [=]{displaySeries();});
    QObject::connect(rangeTo, &QDoubleSpinBox::editingFinished, this, [=]{displaySeries();});
    QObject::connect(steps, &QSpinBox::textChanged, this, [=]{displaySeries();});

    QObject::connect(noise, &QCheckBox::stateChanged, this, [=]{displaySeries();});
    QObject::connect(spectrum, &QCheckBox::stateChanged, this, [=]{displaySeries();});
    QObject::connect(noiseAlpha, &QDoubleSpinBox::textChanged, this, [=]{displaySeries();});
    displaySeries();
}

void Lab7_8_9::displaySeries()
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

    if(hamming->checkState()==2)
        bits = encodeHamming_4bit(bits, errors->value());

    bits.resize(bitLimitVal);
    decodeOutput->clear();

    if(clk->checkState()==2)
        labSeries.append(clkSignal);
    if(ttl->checkState()==2)
    {
        auto mTTL = modTTL(clkSignal, bits);

        if(noise->checkState()==2)
            mTTL = addRandomNoise(mTTL, noiseAlpha->value());
        labSeries.append(mTTL);

        if(decode->checkState()==2)
        {
            if(hamming->checkState()==2)
                decodeOutput->appendPlainText("TTL :  "+stringFromBits(decHamming_4bit(decTTL(clkVal, mTTL)), endianVal)+"\n");
            else
                decodeOutput->appendPlainText("TTL :  "+stringFromBits(decTTL(clkVal, mTTL), endianVal)+"\n");

        }
    }
    if(man->checkState()==2)
    {
        auto mMan = modManchester(clkSignal, bits);

        if(noise->checkState()==2)
            mMan = addRandomNoise(mMan, noiseAlpha->value());
        labSeries.append(mMan);

        if(decode->checkState()==2)
        {
            if(hamming->checkState()==2)
                decodeOutput->appendPlainText("Manchester :  "+stringFromBits(decHamming_4bit(decManchester(clkVal, mMan)), endianVal)+"\n");
            else
                decodeOutput->appendPlainText("Manchester :  "+stringFromBits(decManchester(clkVal, mMan), endianVal)+"\n");
        }
    }
    if(nrzi->checkState()==2)
    {
        auto mNRZI = modNRZI(clkSignal, bits);

        if(noise->checkState()==2)
            mNRZI = addRandomNoise(mNRZI, noiseAlpha->value());
        labSeries.append(mNRZI);

        if(decode->checkState()==2)
        {
            if(hamming->checkState()==2)
                decodeOutput->appendPlainText("NRZI :  "+stringFromBits(decHamming_4bit(decNRZI(clkVal, mNRZI)), endianVal)+"\n");
            else
                decodeOutput->appendPlainText("NRZI :  "+stringFromBits(decNRZI(clkVal, mNRZI), endianVal)+"\n");
        }
    }
    if(bami->checkState()==2)
    {
        auto mBAMI = modBAMI(clkSignal, bits);

        if(noise->checkState()==2)
            mBAMI = addRandomNoise(mBAMI, noiseAlpha->value());
        labSeries.append(mBAMI);

        if(decode->checkState()==2)
        {
            if(hamming->checkState()==2)
                decodeOutput->appendPlainText("BAMI :  "+stringFromBits(decHamming_4bit(decBAMI(clkVal, mBAMI)), endianVal)+"\n");
            else
                decodeOutput->appendPlainText("BAMI :  "+stringFromBits(decBAMI(clkVal, mBAMI), endianVal)+"\n");
        }
    }
    if(spectrum->checkState()==2)
        for(int i=0; i<labSeries.length(); i++)
            labSeries[i] = calculateSpectrum(labSeries.at(i));
    chartView->chart()->removeAllSeries();
    addSeriesToChart(labSeries, 3);
}


void Lab7_8_9::addSeriesToChart(QVector<LabSeries> series, double offset)
{
    double total = 0;
    for(auto s : series)
    {
        auto temp = new QLineSeries();
        for(int i=0; i<s.xVec.length(); i++)
        {
            temp->append(s.xVec.at(i), s.yVec.at(i) + offset + total);
        }
        temp->setName(s.name);
        chartView->chart()->addSeries(temp);
        total+=offset;
    }

    chartView->chart()->createDefaultAxes();
    if(chartView->chart()->axes(Qt::Vertical).length()>0)
    {
        QValueAxis* axisY = (QValueAxis*)chartView->chart()->axes(Qt::Vertical)[0];
        double addRange = (axisY->max() - axisY->min())*0.10;
        axisY->setLabelFormat(" ");
        axisY->setTickType(QValueAxis::TicksDynamic);
        axisY->setTickAnchor(3);
        axisY->setTickInterval(offset);
        axisY->setMax(axisY->max()+addRange);
        axisY->setMin(axisY->min()-addRange);
    }
}

LabSeries Lab7_8_9::genCLK(double freq, double from, double to, int steps)
{
    QVector<double> x;
    QVector<double> y;
    double range = to-from;
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
    return LabSeries(x, y, "CLK");
}

LabSeries Lab7_8_9::modTTL(LabSeries clock, QBitArray bits)
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
    return LabSeries(x, y, "TTL");
}

LabSeries Lab7_8_9::modManchester(LabSeries clock, QBitArray bits)
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
    return LabSeries(x, y, "Manchester");
}

LabSeries Lab7_8_9::modNRZI(LabSeries clock, QBitArray bits)
{
    QVector<double> y;
    QVector<double> x;

    int prevClock = round(clock.yVec.first());
    int mod = 0;
    for(int i=0, bit=0; i<clock.yVec.length();i++)
    {
        int clk = round(clock.yVec.at(i));
        if(prevClock==1 && clk == 0 && bit<bits.count())
        {
            if(bits.at(bit))
                mod = (mod >= 0) ? -1 : 1;
            bit++;
        }
        prevClock = clk;
        y.append(mod);
        x.append(clock.xVec.at(i));
    }
    return LabSeries(x, y, "NRZI");
}

LabSeries Lab7_8_9::modBAMI(LabSeries clock, QBitArray bits)
{
    QVector<double> y;
    QVector<double> x;

    int prevClock = round(clock.yVec.first());
    int mod = 0;
    bool counter = 0;
    for(int i=0, bit=0; i<clock.yVec.length() && bit<bits.count()+1;i++)
    {
        int clk = round(clock.yVec.at(i));
        if(prevClock==1 && clk == 0 && bit<bits.count())
        {
            if(bits.at(bit))
            {
                if(counter)
                {
                    mod = -1;
                    counter = false;
                }
                else
                {
                    mod = 1;
                    counter = true;
                }
            }
            else
                mod = 0;
            bit++;
        }
        prevClock = clk;
        y.append(mod);
        x.append(clock.xVec.at(i));
    }
    return LabSeries(x, y, "BAMI");
}

QBitArray Lab7_8_9::decTTL(int clockFreq, LabSeries mod)
{
    QBitArray bits;
    double step = (1/static_cast<double>(clockFreq));
    double x = step/2;
    bits.fill(false, static_cast<int>((mod.xVec.last()-mod.xVec.first())/x));
    int bit = 0;
    for(int i=0; x<mod.xVec.last() && i<mod.xVec.length(); i++)
    {
        if(mod.xVec.at(i)>x)
        {
            x+=step;
            bits.setBit(bit, mod.yVec.at(i)>0.5);
            bit++;
        }
    }
    bits.resize(bit);
    return bits;
}

QBitArray Lab7_8_9::decManchester(int clockFreq, LabSeries mod)
{
    QBitArray bits;
    double step = (1/static_cast<double>(clockFreq))/2;
    double x = step/2;
    bits.fill(false, static_cast<int>((mod.xVec.last()-mod.xVec.first())/x));
    int bit = 0;
    bool cycle = false;
    int first = 0;
    int second = 0;
    for(int i=0; x<mod.xVec.last() && i<mod.xVec.length(); i++)
    {
        if(mod.xVec.at(i)>x)
        {
            if(cycle==false)
            {
                first = round(mod.yVec.at(i));
                cycle = true;
                x+=step;
            }
            else
            {
                second = round(mod.yVec.at(i));
                bool newBit = first >= 0 && second <= 0;
                bits.setBit(bit, newBit);
                bit++;
                cycle = false;
                x+=step;
            }
        }
    }
    bits.resize(bit);
    return bits;
}

QBitArray Lab7_8_9::decNRZI(int clockFreq, LabSeries mod)
{
    QBitArray bits;
    double step = (1/static_cast<double>(clockFreq));
    double x = step*0.75;
    bits.fill(false, static_cast<int>((mod.xVec.last()-mod.xVec.first())/x));
    int prevBit = 0;
    int bit = 0;
    for(int i=0; x<mod.xVec.last() && i<mod.xVec.length(); i++)
    {
        if(mod.xVec.at(i)>x)
        {
            x+=step;
            int newBit;
            if(mod.yVec.at(i) > 0.5)
                newBit = 1;
            else if(mod.yVec.at(i) < -0.5)
                newBit = -1;
            else
                newBit = 0;
            bits.setBit(bit, newBit!=prevBit);
            prevBit = newBit;
            bit++;
        }
    }
    qDebug()<<bits;
    bits.resize(bit);
    return bits;
}

QBitArray Lab7_8_9::decBAMI(int clockFreq, LabSeries mod)
{
    QBitArray bits;
    double step = (1/static_cast<double>(clockFreq));
    double x = step*0.75;
    bits.fill(false, static_cast<int>((mod.xVec.last()-mod.xVec.first())/x));
    int bit = 0;
    for(int i=0; x<mod.xVec.last() && i<mod.xVec.length(); i++)
    {
        if(mod.xVec.at(i)>x)
        {
            x+=step;
            bool newBit = mod.yVec.at(i) > 0.5 || mod.yVec.at(i) < -0.5;
            bits.setBit(bit, newBit);
            bit++;
        }
    }
    bits.resize(bit);
    return bits;
}

template <int N, int M, typename T>
QGenericMatrix<N, M, T> operator%(const QGenericMatrix<N, M, T>& matrix, T factor)
{
    const T* data = matrix.constData();
    T result[N*M];
    for (int i = 0; i < M * N; i++)
            result[i] = data[i] % factor;
    QGenericMatrix<N, M, T> resultMatrix(result);
    return resultMatrix;
}

QBitArray Lab7_8_9::encodeHamming_4bit(QBitArray bits, int error)
{
    //if the array of bits is not divisible by 4 we ignore the remainder
    //as it does not form proper byte anyway
    QBitArray encodedBits;
    encodedBits.fill(0, bits.count()*2);
    if(bits.count()<4)
        return encodedBits;
    for(int i=0; i<bits.count()-3; i=i+4)
    {
        int valD[] = {bits.at(i),
                     bits.at(i+1),
                     bits.at(i+2),
                     bits.at(i+3)
                    };
        QGenericMatrix<1, 4, int> d(valD);

        int valG[] = {1, 1, 0, 1,
                      1, 0, 1, 1,
                      1, 0, 0, 0,
                      0, 1, 1, 1,
                      0, 1, 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1
                     };
        QGenericMatrix<4, 7, int> G(valG);
        auto h = G * d;
        auto hT = h.transposed()%2;
        int p4 = 0;
        for(int j=0; j < 7; j++)
        {
            if(hT(0,j))
                encodedBits.setBit(j+i*2);
            p4+=hT(0,j);
        }
        encodedBits.setBit(7+i*2, p4 % 2);

        QVector<int> erroredBits;
        erroredBits <<0<<1<<2<<3<<4<<5<<6<<7;
        std::random_shuffle(erroredBits.begin(), erroredBits.end());
        for(int j=0; j<error; j++)
        {
            encodedBits.toggleBit(erroredBits.at(j)+i*2);
        }
    }
    qDebug()<<"Encoded Data with"<<error<<"error(s) per byte: "<<encodedBits<<"\n";
    return encodedBits;
}

QBitArray Lab7_8_9::decHamming_4bit(QBitArray bits)
{
    //if we introduce more than 2 errors this algorithm will not work
    qDebug()<<"Encoded Data: "<<bits<<"\n";
    QBitArray decodedBits;
    decodedBits.fill(0, bits.count()/2);
    if(bits.count()<8)
        return decodedBits;
    for(int i=0; i<bits.count()-7; i=i+8)
    {
        int valD[] = {bits.at(i),
                      bits.at(i+1),
                      bits.at(i+2),
                      bits.at(i+3),
                      bits.at(i+4),
                      bits.at(i+5),
                      bits.at(i+6),
                     };
        QGenericMatrix<1, 7, int> d(valD);

        int valH[] = {1, 0, 1, 0, 1, 0, 1,
                      0, 1, 1, 0, 0, 1, 1,
                      0, 0, 0, 1, 1, 1, 1
                     };

        QGenericMatrix<7, 3, int> H(valH);
        auto p = (H * d) % 2;
        bool discard = false;
        int n = p(0,0)*1 + p(1,0)*2 + p(2,0)*4;
        if(n)
        {
            valD[n-1] = valD[n-1]==0 ? 1 : 0;
            int p4 = (valD[0]+valD[1]+valD[2]+valD[3]+valD[4]
                      +valD[5]+valD[6])%2;
            if(static_cast<bool>(p4) != bits.at(i+7))
                discard = true;
        }
        //if there are more bad bits we discard the result and return 0000
        if(!discard)
        {
            int res[4] = {valD[2], valD[4], valD[5], valD[6]};
            for(int j=0; j<4; j++)
                if(res[j])
                    decodedBits.setBit(j+i/2);
        }
    }
    qDebug()<<"Decoded Data: "<<decodedBits<<"\n";
    return decodedBits;
}


QBitArray Lab7_8_9::bitsFromString(QString s, Endian e)
{
    QByteArray ba = s.toUtf8();
    const char* c = ba.data();
    QBitArray bitArr = QBitArray::fromBits(c,ba.size()*8);
    if(e == LittleEndian)
        reverseBitsInBytes(bitArr);
    qDebug()<<"INPUT: "<<bitArr<<"\n";
    return bitArr;
}

QString Lab7_8_9::stringFromBits(QBitArray bits, Endian e)
{
    if(e == LittleEndian)
        reverseBitsInBytes(bits);
    const char* c = bits.bits();
    return QString(c);
}

void Lab7_8_9::reverseBitsInBytes(QBitArray &arr)
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

LabSeries Lab7_8_9::addRandomNoise(LabSeries series, double alpha)
{
    for(int i=0; i<series.yVec.length(); i++)
    {
        double noise = QRandomGenerator::global()->generateDouble()-0.5;
        //(signal[n]*alfa)+(noise[nn]*(1.0-alfa))
        series.yVec[i] = series.yVec[i]*alpha + noise*(1-alpha);
    }
    return series;
}

LabSeries Lab7_8_9::calculateSpectrum(LabSeries series)
{
    QVector<std::complex<double>> results = Lab3::calculateDFT(series.yVec);
    QVector<double> xVec;
    QVector<double> yVec;
    int stepsVal = series.xVec.length();
    double range = series.xVec.last() - series.xVec.first();
    double step = range/stepsVal;
    double fs = 1/step;
    for(int i=0; i<results.length(); i++)
    {
        double y = abs(results.at(i));
        double x = (i*(fs/stepsVal));
        xVec.append(x);
        yVec.append(10*log10(y));
    }
    return LabSeries(xVec, yVec, "Spectrum " + series.name);
}

