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
    QPushButton *pbInsertionSort;
    QPushButton *pbMergeSort;

    QTextEdit *teArray;
    QTextEdit *teInsertionArea;
    QTextEdit *teMergedArea;
    QLineEdit *leNumbers;

    std::vector<uint32_t> generateArray( uint32_t size, uint32_t low=0, uint32_t high=std::numeric_limits<uint32_t>::max() );
    QString intsToString(std::vector<uint32_t> array);

    std::vector<uint32_t> unsortedArray;
    //std::vector<uint32_t> array2;

    std::vector<uint32_t> insertionArray;
    std::vector<uint32_t> mergedArray;


    std::vector<uint32_t> insertionSort();
    std::vector<uint32_t> mergeSort(std::vector<uint32_t> A);
    std::vector<uint32_t> merge(std::vector<uint32_t> A, std::vector<uint32_t> B);
public slots:
    void onRunClicked();
    void onInsertionClicked();
    void onMergeClicked();
};

#endif // MAINWINDOW_H
