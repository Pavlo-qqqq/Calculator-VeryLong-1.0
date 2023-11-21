#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);
    connect(ui->subtractButton, &QPushButton::clicked, this, &MainWindow::on_subtractButton_clicked);
    connect(ui->multiplyButton, &QPushButton::clicked, this, &MainWindow::on_multiplyButton_clicked);
    connect(ui->divideButton, &QPushButton::clicked, this, &MainWindow::on_divideButton_clicked);
    connect(ui->calculateButton, &QPushButton::clicked, this, &MainWindow::on_calculateButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    currentOperation = "+";
    ui->operationButton->setText(currentOperation);
}

void MainWindow::on_subtractButton_clicked()
{
    currentOperation = "-";
    ui->operationButton->setText(currentOperation);
}

void MainWindow::on_multiplyButton_clicked()
{
    currentOperation = "*";
    ui->operationButton->setText(currentOperation);
}

void MainWindow::on_divideButton_clicked()
{
    currentOperation = "/";
    ui->operationButton->setText(currentOperation);
}

void MainWindow::on_calculateButton_clicked()
{
    calculate();
}

void MainWindow::calculate()
{
    QString num1Str = ui->lineEditNum1->text();
    QString num2Str = ui->lineEditNum2->text();

    num1.input_vl(num1Str.toStdString().c_str());
    num2.input_vl(num2Str.toStdString().c_str());

    VeryLong result;

    if (currentOperation == "+") {
        result = num1 + num2;
    } else if (currentOperation == "-") {
        result = num1 - num2;
    } else if (currentOperation == "*") {
        result = num1 * num2;
    } else if (currentOperation == "/") {
        result = num1 / num2;
    } else {
        ui->resultLabel->setText("Invalid operation.");
        return;
    }

    ui->resultLabel->setText(QString::fromStdString(result.putvl()));
}


