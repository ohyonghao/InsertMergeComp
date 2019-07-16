#include "MainWindow.h"
#include <QRandomGenerator>
#include <QIntValidator>
#include <QHBoxLayout>

#include <cstdlib>
#include <iostream>

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

    leNumbers = new QLineEdit;
    leNumbers->setValidator(new QIntValidator(0,60000));
    leNumbers->setText("100");

    QHBoxLayout *hbButtons = new QHBoxLayout;

    pbRun = new QPushButton("Generate Arrays");
    pbInsertionSort = new QPushButton("Insertion Sort");
    pbMergeSort = new QPushButton("Merge Sort");

    hbButtons->addWidget(pbInsertionSort);
    hbButtons->addWidget(pbMergeSort);
    hbButtons->addWidget(pbRun);

    connect(pbRun, &QPushButton::released, this, &MainWindow::onRunClicked);
    connect(pbInsertionSort, &QPushButton::released, this, &MainWindow::onInsertionClicked);
    connect(pbMergeSort, &QPushButton::released, this, &MainWindow::onMergeClicked);


    mainLayout->addWidget(teArray);
    mainLayout->addWidget(teInsertionArea);
    mainLayout->addWidget(teMergedArea);
    mainLayout->addWidget(leNumbers);
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

vector<uint32_t> MainWindow::insertionSort( ){
    auto A = unsortedArray;
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

vector<uint32_t> MainWindow::mergeSort(vector<uint32_t> A){
    if(A.size() == 1 ) return A;

    uint32_t mid = A.size()/2;
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
    auto A = insertionSort();
    teInsertionArea->setText(intsToString(A));
}

void MainWindow::onMergeClicked(){
    auto A = mergeSort(unsortedArray);
    teMergedArea->setText(intsToString(A));
}
