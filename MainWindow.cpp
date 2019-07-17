#include "MainWindow.h"
#include <QRandomGenerator>
#include <QIntValidator>
#include <QHBoxLayout>
#include <QLabel>
#include <QElapsedTimer>
#include <QVector>

#include <cstdlib>
#include <iostream>

#include "qcustomplot/qcustomplot.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUI();

    this->setCentralWidget(new QWidget);
    centralWidget()->setLayout( mainLayout );
}


void MainWindow::setupUI(){
    mainLayout = new QVBoxLayout;

    teArray = new QTextEdit;
    teArray->setReadOnly(true);

    teInsertionArea = new QTextEdit;
    teMergedArea    = new QTextEdit;

    teInsertionArea->setReadOnly(true);
    teMergedArea->setReadOnly(true);

    QLabel *lNumbers = new QLabel("Size");
    QLabel *lIterations = new QLabel("Iterations");
    QLabel *lSteps = new QLabel("Steps");
    leNumbers = new QLineEdit;
    leNumbers->setValidator(new QIntValidator(0,60000));
    leNumbers->setText("100");

    leIterations = new QLineEdit;
    leIterations->setValidator(new QIntValidator(0,60000));
    leIterations->setText("10");

    leSteps = new QLineEdit;
    leSteps->setValidator(new QIntValidator(0,60000));
    leSteps->setText("100");

    QHBoxLayout *hbNums = new QHBoxLayout;
    hbNums->addWidget(lNumbers);    hbNums->addWidget(leNumbers);
    hbNums->addWidget(lIterations); hbNums->addWidget(leIterations);
    hbNums->addWidget(lSteps); hbNums->addWidget(leSteps);

    QHBoxLayout *hbButtons = new QHBoxLayout;

    pbRun = new QPushButton("Generate Arrays");
    pbInsertionSort = new QPushButton("Insertion Sort");
    pbMergeSort = new QPushButton("Merge Sort");
    pbGenerateGraphs = new QPushButton("Generate Graphs");

    hbButtons->addWidget(pbInsertionSort);
    hbButtons->addWidget(pbMergeSort);
    hbButtons->addWidget(pbRun);
    hbButtons->addWidget(pbGenerateGraphs);

    connect(pbRun, &QPushButton::released, this, &MainWindow::onRunClicked);
    connect(pbInsertionSort, &QPushButton::released, this, &MainWindow::onInsertionClicked);
    connect(pbMergeSort, &QPushButton::released, this, &MainWindow::onMergeClicked);
    connect(pbGenerateGraphs, &QPushButton::released, this, &MainWindow::onGenerateGraphsClicked);


    //plot = new QCustomPlot;

    mainLayout->addWidget(teArray);
    mainLayout->addWidget(teInsertionArea);
    mainLayout->addWidget(teMergedArea);
    //mainLayout->addWidget(plot);
    mainLayout->addLayout(hbNums);
    mainLayout->addLayout(hbButtons);
}

vector<uint32_t> MainWindow::generateArray( uint32_t size, uint32_t low, uint32_t high ){
    vector<uint32_t> array(size,0);

    QRandomGenerator::global()->generate(array.begin(), array.end());
    return array;
}

QString MainWindow::intsToString(vector<uint32_t> array){
    QString nums;
    for(auto it = array.begin(); it < array.end(); ++it){
        nums.append(QString::number(*it) + "\n");
    }
    return nums;
}
void MainWindow::onRunClicked(){
    cout << leNumbers->text().toInt() << endl;
    unsortedArray = generateArray( leNumbers->text().toInt() );
    teArray->setText(intsToString(unsortedArray));
}

vector<uint32_t> MainWindow::insertionSort( const vector<uint32_t>& array ){
    auto A = array;
    for( uint32_t j = 1; j < A.size() ; ++j ){
        auto key = A[j];
        auto i = j - 1;
        while( i < A.size() && A[i] > key ){
            A[i+1] = A[i];
            --i;
        }
        A[i+1] = key;
    }
    return A;
}

vector<uint32_t> MainWindow::mergeSort(const vector<uint32_t>& A){
    if(A.size() <= 1 ) return A;

    uint32_t mid = static_cast<uint32_t>(A.size()/2);
    auto B = mergeSort(vector<uint32_t>(A.begin(), A.begin()+mid));
    auto C = mergeSort(vector<uint32_t>(A.begin()+mid, A.end()));

    return merge(B,C);
}

std::vector<uint32_t> MainWindow::merge(std::vector<uint32_t> B, std::vector<uint32_t> C){
    std::vector<uint32_t> A;
    A.reserve(B.size()+C.size());

    uint32_t i = 0;
    uint32_t j = 0;

    while(i < B.size() && j < C.size()){
        if( B[i] <= C[j] ){
            A.push_back(B[i]);
            ++i;
        }else{
            A.push_back(C[j]);
            ++j;
        }
    }
    if( i == B.size()){
        A.insert(A.end(), C.begin()+j, C.end());
    }else{
        A.insert(A.end(), B.begin()+i, B.end());
    }
    return A;
}
void MainWindow::onInsertionClicked(){
    auto A = insertionSort(unsortedArray);
    teInsertionArea->setText(intsToString(A));
}

void MainWindow::onMergeClicked(){
    auto A = mergeSort(unsortedArray);
    teMergedArea->setText(intsToString(A));
}

void MainWindow::onGenerateGraphsClicked(){
    // Here we want to start generating our graphs.
    // We need to run it an x number of times
    uint32_t size = static_cast<uint32_t>(leNumbers->text().toInt());
    uint32_t iterations = static_cast<uint32_t>(leIterations->text().toInt());
    uint32_t steps = static_cast<uint32_t>(leSteps->text().toInt());

    QVector<double> xaxis;
    vector<vector<uint32_t>> lols;
    for( auto i = 0; i < iterations; ++i ){
        lols.push_back(generateArray(size + i*steps));
        xaxis.append(size+i*steps);
    }

    QVector<double> insertTime;
    insertTime.reserve(iterations);

    QElapsedTimer timer;
    for( auto i = 0; i < iterations; ++i ){
        timer.restart();
        insertionSort(lols[i]);
        insertTime.push_back(timer.nsecsElapsed());
    }

    QVector<double> mergeTime;
    mergeTime.reserve(iterations);

    for( auto i = 0; i < iterations; ++i ){
        timer.restart();
        mergeSort(lols[i]);
        mergeTime.push_back(timer.nsecsElapsed());
    }

    transform( lols.begin(), lols.end(), lols.begin(), [this](auto list){
        return insertionSort(list);
    });

    QVector<double> sInsertTime;
    sInsertTime.reserve(iterations);
    for( auto i = 0; i < iterations; ++i ){
        timer.restart();
        insertionSort(lols[i]);
        sInsertTime.push_back(timer.nsecsElapsed());
    }
    QVector<double> sMergeTime;
    sMergeTime.reserve(iterations);
    for( auto i = 0; i < iterations; ++i ){
        timer.restart();
        mergeSort(lols[i]);
        sMergeTime.push_back(timer.nsecsElapsed());
    }
    QCustomPlot *plot;
    plot = generateGraph(xaxis, insertTime, mergeTime);
    plot->saveJpg(QString("image_%1_%2.jpg").arg(iterations).arg(steps),
                  400, 200);
    plot = generateGraph(xaxis, sInsertTime, sMergeTime);
    plot->saveJpg(QString("image_%1_%2_sorted.jpg").arg(iterations).arg(steps),
                  400, 200);
}

QCustomPlot *MainWindow::generateGraph(const QVector<double>& xaxis, const QVector<double>& insertTime, const QVector<double>& mergeTime){

    // Now generate the graph
    QCustomPlot *plot = new QCustomPlot;
    plot->setAttribute(Qt::WA_DeleteOnClose);
    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::red));
    plot->graph(0)->setData(xaxis, insertTime, true);
    plot->graph(0)->setName("Insertion Sort");

    plot->addGraph();
    plot->graph(1)->setPen(QPen(Qt::green));
    plot->graph(1)->setData(xaxis, mergeTime, true);
    plot->graph(1)->setName("Merge Sort");

    plot->xAxis->rescale();
    plot->xAxis->setLabel("Size of Array");
    plot->yAxis->rescale();
    plot->yAxis->setLabel("Time to Sort (ns)");
    plot->legend->setVisible(true);
    plot->replot();
    return plot;
}
