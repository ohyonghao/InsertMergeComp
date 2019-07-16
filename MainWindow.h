#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>

#include <vector>
#include <limits>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void setupUI();

    QVBoxLayout *mainLayout;
    QPushButton *pbRun;
    QTextEdit *teListArea;
    QTextEdit *teInsertionArea;
    QTextEdit *teMergedArea;
    QLineEdit *leNumbers;

    std::vector<uint32_t> generateArray( uint32_t size, uint32_t low=0, uint32_t high=std::numeric_limits<uint32_t>::max() );
    QString intsToString(std::vector<uint32_t> array);

    std::vector<uint32_t> array1;
    std::vector<uint32_t> array2;

    std::vector<uint32_t> insertionArray;
    std::vector<uint32_t> mergedArray;


    void insertionSort( uint32_t size );
    void mergeSort( uint32_t size );
public slots:
    void onRunClicked();
};

#endif // MAINWINDOW_H
