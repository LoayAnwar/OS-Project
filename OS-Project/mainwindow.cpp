#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->setPlaceholderText("Choose your Process");
    ui->comboBox->addItem("FCFS");
    ui->comboBox->addItem("SJF (Preemptive)");
    ui->comboBox->addItem("SJF (Non Preemptive)");
    ui->comboBox->addItem("Priority (Preemptive)");
    ui->comboBox->addItem("Priority (Non Preemptive)");
    ui->comboBox->addItem("Round Robin");
    ui->tableWidget->hide();
    ui->lineEdit_2->hide();
    ui->label_2->hide();
    ui->submit->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->comboBox->currentIndex()==-1 || (ui->lineEdit->text() == "")){
        QMessageBox::warning(this, "Wrong Input", "Please choose process or enter value");
        ui->tableWidget->hide();
        ui->submit->hide();
    }
    else {
        ui->lineEdit_2->hide();
        ui->label_2->hide();
        ui->tableWidget->show();
        ui->submit->show();
        ui->tableWidget->setColumnCount(2);
        QString string = ui->lineEdit->text();
        ui->tableWidget->setRowCount(string.toInt());
        QStringList labels;
        labels << "Arrival Time" << "Burst Time";
        QStringList labels_2;
        for (int i = 0; i < string.toInt(); i++) {
            labels_2 << "P" + QString::number(i);
        }
        ui->tableWidget->setVerticalHeaderLabels(labels_2);

        if (ui->comboBox->currentIndex() == 3 || ui->comboBox->currentIndex() == 4){
            labels << "Priority";
            ui->tableWidget->insertColumn(1);
        }
        else if (ui->comboBox->currentIndex() == 5) {
            ui->lineEdit_2->show();
            ui->label_2->show();
        }
        ui->tableWidget->setHorizontalHeaderLabels(labels);
    }
}

void MainWindow::on_submit_clicked()
{
    QString process =  ui->comboBox->currentText();
    if(process == "FCFS")
    {

    }
    else if (process == "SJF (Preemptive)")
    {

    }
    else if (process == "SJF (Non Preemptive)")
    {

    }
    else if (process == "Priority (Non Preemptive)")
    {

    }
    else if (process == "Priority (Preemptive)")
    {

    }
    else if(process == "Round Robin")
    {

    }
}

