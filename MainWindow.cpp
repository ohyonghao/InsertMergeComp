#include "MainWindow.h"
#include <QRandomGenerator>
#include <QIntValidator>

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

    teListArea = new QTextEdit;
    teListArea->setReadOnly(true);

    teInsertionArea = new QTextEdit;
    teMergedArea    = new QTextEdit;

    teInsertionArea->setReadOnly(true);
    teMergedArea->setReadOnly(true);

    leNumbers = new QLineEdit;
    leNumbers->setValidator(new QIntValidator(0,60000));
    leNumbers->setText("100");
    pbRun = new QPushButton("Run");

    connect(pbRun, &QPushButton::released, this, &MainWindow::onRunClicked);

    mainLayout->addWidget(teListArea);
    mainLayout->addWidget(teInsertionArea);
    mainLayout->addWidget(teMergedArea);
    mainLayout->addWidget(leNumbers);
    mainLayout->addWidget(pbRun);
}

vector<uint32_t> MainWindow::generateArray( uint32_t size, uint32_t low, uint32_t high ){
    vector<uint32_t> array(size,0);

    QRandomGenerator::global()->generate(array.begin(), array.end());
    return array;
}

QString MainWindow::intsToString(vector<uint32_t> array){
    QString nums;
    for(auto it = array.begin(); it < array.end(); ++it){
        nums.append(QString::number(*it) + " ");
    }
    return nums;
}
void MainWindow::onRunClicked(){
    cout << leNumbers->text().toInt() << endl;
    vector<uint32_t> array = generateArray( leNumbers->text().toInt() );
    teListArea->setText(intsToString(array));
}

void MainWindow::insertionSort( uint32_t size ){
    // Do Insertion Sort
    //teInsertionArea->setText();
}
