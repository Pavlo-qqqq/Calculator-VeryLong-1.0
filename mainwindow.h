#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "verylong.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void on_addButton_clicked();
    void on_subtractButton_clicked();
    void on_multiplyButton_clicked();
    void on_divideButton_clicked();
    void on_calculateButton_clicked();

    Ui::MainWindow *ui;
    VeryLong num1;
    VeryLong num2;
    QString currentOperation;
    void calculate();
};

#endif // MAINWINDOW_H
