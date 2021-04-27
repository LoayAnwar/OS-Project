#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Process {
    int pid;
    float arrival_time;
    float burst_time;
    int priority;
    float waiting_time;
    float start_time;
    float finish_time;
};
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
    else if (process == "SJF (Preemptive)")//
    {
    }
    else if (process == "SJF (Non Preemptive)") //
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


void  MainWindow::sj_permiavtive()
{
    QString string = ui->lineEdit->text();
    int x = string.toInt();
    float* arrival_time= new float(x) ;
    float* arrival_time_sorted = new float(x) ;
    float* duration_time=new float(x) ;
    for (int i = 0; i < x; i++)
      {
          QString string_1 = ui->tableWidget->item(i, 0)->text();
          arrival_time[i] = string_1.toDouble();
          arrival_time_sorted[i]=string_1.toDouble();
          QString string_2 = ui->tableWidget->item(i, 1)->text();
          duration_time[i] = string_2.toInt();
      }

    sort(arrival_time_sorted, arrival_time_sorted + 5);
    vector <int> process;
    vector <float> duration;
    vector <int> arrived;

    float time = 0;
    int sj_index = 0;
    int ind = 0;


    for (int arr = 0; arr < 5; arr++)
    {
        if (arrival_time_sorted[arr] == arrival_time_sorted[arr + 1])
        {
            arr++;
        }
        for (int i = 0; i < 5; i++)
        {
            if (arrival_time[i] <= arrival_time_sorted[arr] && duration_time[i] > 0)
            {
                arrived.push_back(i);
            }
        }
        if (arr < 5 - 1) {
            while (time < arrival_time_sorted[arr + 1]) {
                if (arrived.size() == 0)
                {
                    process.push_back(-1);
                    duration.push_back(arrival_time_sorted[arr + 1] - time);
                    time = arrival_time_sorted[arr + 1];
                    break;
                }
                sj_index = arrived[0];
                ind = 0;
                for (int p = 0; p < arrived.size(); p++)
                {
                    if (duration_time[arrived[p]] < duration_time[sj_index] && duration[sj_index] >0)
                    {
                        sj_index = arrived[p];
                        ind = p;
                    }
                }
                arrived.erase(arrived.begin() + ind);
                if (duration_time[sj_index] + time <= arrival_time_sorted[arr + 1])
                {
                    process.push_back(sj_index);
                    duration.push_back(duration_time[sj_index]);
                    time += duration_time[sj_index];
                    duration_time[sj_index] = 0;
                }
                else
                {
                    process.push_back(sj_index);
                    duration.push_back(arrival_time_sorted[arr + 1] - time);
                    duration_time[sj_index] -= arrival_time_sorted[arr + 1] - time;
                    time = arrival_time_sorted[arr + 1];

                }
            }
            arrived.clear();
        }
        else
        {

            while (arrived.size() != 0)
            {
                sj_index = arrived[0];
                ind = 0;
                for (int p = 0; p < arrived.size(); p++)
                {
                    if (duration_time[arrived[p]] < duration_time[sj_index] && duration[sj_index] >0)
                    {
                        sj_index = arrived[p];
                        ind = p;
                    }
                }
                arrived.erase(arrived.begin() + ind);
                process.push_back(sj_index);
                duration.push_back(duration_time[sj_index]);
                time += duration_time[sj_index];
                duration_time[sj_index] = 0;

            }

        }

    }


    for (int i = 0; i < process.size(); i++)
    {
        qDebug() << process[i] << "  ";

    }
    for (int i = 0; i < process.size(); i++)
    {
        qDebug() << duration[i] << "  ";
    }
}

void MainWindow::sj_non()
{
    QString string = ui->lineEdit->text();
    int x = string.toInt();
    vector<struct Process> process(x);
    vector<float> duration(x);
    vector<float> pid(x);
    vector<float> start_time(x);
    vector<float> finish_time(x);
    for (int i = 0; i < x; i++)
      {
          QString string_1 = ui->tableWidget->item(i, 0)->text();
          process[i].arrival_time = string_1.toDouble();
          QString string_2 = ui->tableWidget->item(i, 1)->text();
          process[i].burst_time = string_2.toInt();
      }

    float current_time = 0;
        int completed_process = 0;
        vector<bool> is_completed(x);
        bool first_process = true;
        while (completed_process != x) {
            int index = -1;
            int min = 100000;
            for (int i = 0; i < x; i++) {
                if (process[i].arrival_time <= current_time && !is_completed[i]) {
                    if (process[i].burst_time < min) {
                        min = process[i].burst_time;
                        index = i;
                    }
                    if (process[i].burst_time == min) {
                        if (process[i].arrival_time < process[index].arrival_time) {
                            min = process[i].burst_time;
                            index = i;
                        }
                    }
                }
            }
            if (index != -1) {
                if (first_process) {
                    process[index].start_time = process[index].arrival_time;
                    first_process = false;
                }
                else
                    process[index].start_time = current_time;
                process[index].finish_time = process[index].start_time + process[index].burst_time;
                float waitint_time = process[index].finish_time - process[index].arrival_time -
                                     process[index].burst_time;
                process[index].waiting_time = waitint_time;
                is_completed[index] = true;
                completed_process++;
                current_time = process[index].finish_time;

            }
            else
                current_time++;
        }

        //for sorting
        int min_index;
        for (int i = 0; i < x - 1; i++) {
            min_index = i;
            for (int j = i + 1; j < x; j++)
                if (process[j].start_time < process[min_index].start_time)
                    min_index = j;
            swap(process[min_index].start_time, process[i].start_time);
            swap(process[min_index].finish_time, process[i].finish_time);
            swap(process[min_index].pid, process[i].pid);
            swap(process[min_index].arrival_time, process[i].arrival_time);
            swap(process[min_index].burst_time, process[i].burst_time);
            swap(process[min_index].waiting_time, process[i].waiting_time);
        }
        for (int i = 0; i < x; i++) {
            pid[i] = process[i].pid;
            duration[i] = process[i].finish_time - process[i].start_time;
            finish_time[i] = process[i].finish_time;
            start_time[i] = process[i].start_time;
        }
}



void MainWindow::round_robin()
{
    float temp1;
    int temp2, temp3;
    QString string = ui->lineEdit->text();
    QVector<float> arrival(string.toInt());
    QVector<int> burst_time(string.toInt());
    QVector<int> process(string.toInt());
    QVector<int> queue(string.toInt());
    QVector<int> duration(string.toInt());

            for (int i = 0; i < string.toInt(); i++)
            {
                QString string_1 = ui->tableWidget->item(i,0)->text();
                arrival[i] = string_1.toFloat();
                QString string_2 = ui->tableWidget->item(i,1)->text();
                burst_time[i] = string_2.toInt();
                process[i] = i;
            }
            for (int i = 0; i < string.toInt(); i++)
            {
                for (int j = i+1; j < string.toInt(); j++)
                {
                    if(arrival[j] < arrival[i])
                    {
                        temp1 = arrival[i];
                        arrival[i] = arrival[j];
                        arrival[j] = temp1;
                        temp2 = burst_time[i];
                        burst_time[i] = burst_time[j];
                        burst_time[j] = temp2;
                        temp3 = process[i];
                        process[i] = process[j];
                        process[j] = temp3;
                    }
                }
            }
            for(int i=0; i<string.toInt(); i++)
            {
                queue[i] = process[i];
                duration[i] = burst_time[i];
            }

                int n = string.toInt();
                int quantum = (ui->lineEdit_2->text()).toInt();
                std::vector<struct Process> p;
                std::vector<int> process_id;
                std::vector<float> process_duration;

                struct Process temp;

                for (int i =0 ; i<n ;i++)
                {
                    temp.pid = queue[i] ;
                    temp.arrival_time =arrival[i];
                    temp.burst_time =duration[i];
                    p.push_back(temp);
                }
//                p[0].pid = 1;
//                p[0].arrival_time = 0;
//                p[0].burst_time = 4;
//                p[1].pid = 2;
//                p[1].arrival_time = 1;
//                p[1].burst_time = 5;
//                p[2].pid = 3;
//                p[2].arrival_time = 2;
//                p[2].burst_time = 2;
//                p[3].pid = 4;
//                p[3].arrival_time = 3;
//                p[3].burst_time = 1;
//                p[4].pid = 5;
//                p[4].arrival_time = 4;
//                p[4].burst_time = 6;
//                p[5].pid = 6;
//                p[5].arrival_time = 6;
//                p[5].burst_time = 3;

                std::queue<struct Process> q;
                std::queue <struct Process> ready_q;


                for (int i = 0; i < n; i++) {
                    q.push(p[i]);
                }

                int size;
                float time = 0;
                bool flag = true;
                bool finished = true;
                while (flag) {
                    flag = false;
                    size = (q.size());
                    for (int i = 0; i < size; i++) {
                        flag = true;
                        if ((q.front()).arrival_time <= time) {
                            ready_q.push(q.front());
                            q.pop();
                        }
                    }
                    if (!finished) {
                        ready_q.push(temp);
                    }
                    if (!ready_q.empty()) {
                        flag = true;
                        if ((ready_q.front()).burst_time > quantum) {
                            (ready_q.front()).burst_time = ((ready_q.front()).burst_time) - quantum;
                            time += quantum;
                            temp = (ready_q.front());
                            process_id.push_back((ready_q.front()).pid);
                            process_duration.push_back(quantum);
                            ready_q.pop();
                            finished = false;

                        }
                        else {
                            time += (ready_q.front()).burst_time;
                            process_id.push_back((ready_q.front()).pid);
                            process_duration.push_back((ready_q.front()).burst_time);
                            (ready_q.front()).burst_time = 0;
                            finished = true;
                            ready_q.pop();
                        }

                    }
                    else if (!q.empty()) {
                        time = (q.front()).arrival_time;
                    }
                }



}

void  MainWindow::priority_premative()
{
    QString string = ui->lineEdit->text();
    int x = string.toInt();
    float* arrival_time= new float(x) ;
    float* arrival_time_sorted = new float(x) ;
    float* duration_time=new float(x) ;
    float* priority=new float(x) ;

    for (int i = 0; i < x; i++)
      {
          QString string_1 = ui->tableWidget->item(i, 0)->text();
          arrival_time[i] = string_1.toDouble();
          arrival_time_sorted[i]=string_1.toDouble();
          QString string_2 = ui->tableWidget->item(i, 1)->text();
          duration_time[i] = string_2.toInt();
          QString string_3 = ui->tableWidget->item(i, 2)->text();
          priority[i] = string_3.toInt();

      }

    sort(arrival_time_sorted, arrival_time_sorted + 5);
    vector <int> process;
    vector <float> duration;
    vector <int> arrived;
    float time = 0;
    int sj_index = 0;
    int ind = 0;

    for (int arr = 0; arr < 3; arr++)
    {
        if (arrival_time_sorted[arr] == arrival_time_sorted[arr + 1])
        {
            arr++;
        }
        for (int i = 0; i < 3; i++)
        {
            if (arrival_time[i] <= arrival_time_sorted[arr] && duration_time[i] > 0)
            {
                arrived.push_back(i);
            }
        }
        if (arr < 3 - 1) {
            while (time < arrival_time_sorted[arr + 1]) {
                if (arrived.size() == 0)
                {
                    process.push_back(-1);
                    duration.push_back(arrival_time_sorted[arr + 1] - time);
                    time = arrival_time_sorted[arr + 1];
                    break;
                }
                sj_index = arrived[0];
                ind = 0;
                for (int p = 0; p < arrived.size(); p++)
                {
                    if (priority[arrived[p]] < priority[sj_index] && duration[sj_index] >0)
                    {
                        sj_index = arrived[p]; //p1 /02
                        ind = p;
                    }
                }// [p1 ,p4 p3]  , [2,3,5]
                arrived.erase(arrived.begin() + ind);
                if (duration_time[sj_index] + time <= arrival_time_sorted[arr + 1])
                {
                    process.push_back(sj_index);
                    duration.push_back(duration_time[sj_index]);
                    time += duration_time[sj_index];
                    duration_time[sj_index] = 0;
                }
                else
                {
                    process.push_back(sj_index);
                    duration.push_back(arrival_time_sorted[arr + 1] - time);
                    duration_time[sj_index] -= arrival_time_sorted[arr + 1] - time;
                    time = arrival_time_sorted[arr + 1];

                }
            }
            arrived.clear();
        }
        else
        {

            while (arrived.size() != 0)
            {
                sj_index = arrived[0];
                ind = 0;
                for (int p = 0; p < arrived.size(); p++)
                {
                    if (priority[arrived[p]] < priority[sj_index] && duration[sj_index] >0)
                    {
                        sj_index = arrived[p];
                        ind = p;
                    }
                }
                arrived.erase(arrived.begin() + ind);
                process.push_back(sj_index);
                duration.push_back(duration_time[sj_index]);
                time += duration_time[sj_index];
                duration_time[sj_index] = 0;

            }

        }

    }
    for (int i = 0; i < process.size(); i++)
    {
        qDebug() << process[i] << "  ";
    }
    for (int i = 0; i < process.size(); i++)
    {
        qDebug() << duration[i] << "  ";
    }

}

void  MainWindow::fcfs()
{
    float temp1;
            int temp2, temp3;
            QString string = ui->lineEdit->text();
            QVector<float> arrival(string.toInt());
            QVector<int> burst_time(string.toInt());
            QVector<int> process(string.toInt());
            QVector<int> queue(string.toInt());
            QVector<int> duration(string.toInt());

            for (int i = 0; i < string.toInt(); i++)
            {
                QString string_1 = ui->tableWidget->item(i,0)->text();
                arrival[i] = string_1.toFloat();
                QString string_2 = ui->tableWidget->item(i,1)->text();
                burst_time[i] = string_2.toInt();
                process[i] = i;
            }
            for (int i = 0; i < string.toInt(); i++)
            {
                for (int j = i+1; j < string.toInt(); j++)
                {
                    if(arrival[j] < arrival[i])
                    {
                        temp1 = arrival[i];
                        arrival[i] = arrival[j];
                        arrival[j] = temp1;
                        temp2 = burst_time[i];
                        burst_time[i] = burst_time[j];
                        burst_time[j] = temp2;
                        temp3 = process[i];
                        process[i] = process[j];
                        process[j] = temp3;
                    }
                }
            }
            for(int i=0; i<string.toInt(); i++)
            {
                queue[i] = process[i];
                duration[i] = burst_time[i];
            }
}

void MainWindow::priority_non()
{
    QString string = ui->lineEdit->text();
    int x = string.toInt();
    vector<float> duration(x);
    vector<float> pid(x);
    vector<float> start_time(x);
    vector<float> finish_time(x);
    vector<struct Process> process(x);
    for (int i = 0; i < x; i++)
      {
          QString string_1 = ui->tableWidget->item(i, 0)->text();
          process[i].arrival_time = string_1.toDouble();
          QString string_2 = ui->tableWidget->item(i, 1)->text();
          process[i].burst_time = string_2.toInt();
          QString string_3 = ui->tableWidget->item(i, 2)->text();
          process[i].priority = string_3.toInt();

      }
    float current_time = 0;
        int completed_process = 0;
        vector<bool> is_completed(x);
        bool first_process = true;
        while (completed_process != x) {
            int index = -1;
            int min = 100000;
            for (int i = 0; i < x; i++) {
                if (process[i].arrival_time <= current_time && !is_completed[i]) {
                    if (process[i].priority < min) {
                        min = process[i].priority;
                        index = i;
                    }
                    if (process[i].priority == min) {
                        if (process[i].arrival_time < process[index].arrival_time) {
                            min = process[i].priority;
                            index = i;
                        }
                    }
                }
            }
            if (index != -1) {
                if (first_process) {
                    process[index].start_time = process[index].arrival_time;
                    first_process = false;
                }
                else
                    process[index].start_time = current_time;
                process[index].finish_time = process[index].start_time + process[index].burst_time;
                float waitint_time = process[index].finish_time - process[index].arrival_time -
                                     process[index].burst_time;
                process[index].waiting_time = waitint_time;
                is_completed[index] = true;
                completed_process++;
                current_time = process[index].finish_time;

            }
            else
                current_time++;
        }
        // for sorting
        int min_index;
        for (int i = 0; i < x - 1; i++) {
                min_index = i;
                for (int j = i + 1; j < x; j++)
                    if (process[j].start_time < process[min_index].start_time)
                        min_index = j;
                swap(process[min_index].start_time, process[i].start_time);
                swap(process[min_index].finish_time, process[i].finish_time);
                swap(process[min_index].pid, process[i].pid);
                swap(process[min_index].arrival_time, process[i].arrival_time);
                swap(process[min_index].burst_time, process[i].burst_time);
                swap(process[min_index].waiting_time, process[i].waiting_time);
                swap(process[min_index].priority, process[i].priority);
            }
            for (int i = 0; i < x; i++) {
                pid[i] = process[i].pid;
                duration[i] = process[i].finish_time - process[i].start_time;
                finish_time[i] = process[i].finish_time;
                start_time[i] = process[i].start_time;
            }
}
