#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <QElapsedTimer>
#include<QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>
using namespace std;
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
    scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene_2=new QGraphicsScene(this);
    ui->graphicsView_2->setScene(scene_2);
    ui->graphicsView->hide();
    ui->label_4->hide();
    ui->label_3->hide();
    ui->graphicsView_2->hide();


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
        ui->graphicsView->show();
        ui->graphicsView_2->show();
        ui->tableWidget->setColumnCount(2);
        QString string = ui->lineEdit->text();
        ui->tableWidget->setRowCount(string.toInt());
        QStringList labels;
        labels << "Arrival Time" << "Burst Time";
        QStringList labels_2;
        for (int i = 0; i < string.toInt(); i++) {
            labels_2 << "P" + QString::number(i + 1);
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

void MainWindow::draw(vector<struct Process> process) {
    for (int i = 0; i < (process.size()); i++) {
        int pid = process[i].pid - 1;
        QBrush color_brush(QColor(process[i].color));
        QPen blackpen(Qt::black);
        blackpen.setWidth(1);
        QElapsedTimer t;
        if (i != 0) {
            if (process[i].start_time != process[i - 1].finish_time){
                QBrush color_brush(QColor("black"));
                rectangle=scene->addRect(-200+Rectangle_Width*process[i - 1].finish_time,0,Rectangle_Width*(process[i].start_time-process[i-1].finish_time),Rectangle_Height,blackpen, color_brush);
                QString start = QString::number(process[i-1].finish_time);
                QGraphicsTextItem *txtitem = new QGraphicsTextItem(start);
                txtitem->setPos(QPointF(-200+Rectangle_Width*process[i-1].finish_time, 100));
                scene->addItem(txtitem);
                t.start();
                while(t.elapsed() < 1000)
                {
                    QCoreApplication::processEvents();
                }
                QBrush color_brush_2(QColor(process[i].color));
                rectangle=scene->addRect(-200+Rectangle_Width*process[i].start_time,0,Rectangle_Width*process[i].burst_time,Rectangle_Height,blackpen, color_brush_2);
            }
            else
                rectangle=scene->addRect(-200+Rectangle_Width*process[i - 1].finish_time,0,Rectangle_Width*process[i].burst_time,Rectangle_Height,blackpen,color_brush);
        }
        if (i == 0)
            rectangle=scene->addRect(-200+Rectangle_Width*process[i].start_time,0,Rectangle_Width*process[i].burst_time,Rectangle_Height,blackpen,color_brush);
        QString start = QString::number(process[i].start_time);
        QGraphicsTextItem *txtitem = new QGraphicsTextItem(start);
        if (i == 0)
            txtitem->setPos(QPointF(-200+Rectangle_Width*process[i].start_time, 100));
        else
            txtitem->setPos(QPointF(-200+Rectangle_Width*process[i].start_time, 100));
        scene->addItem(txtitem);
        t.start();
        if (i == (process.size()) - 1) {
            QString start = QString::number(process[process.size() - 1].finish_time);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(start);
            txtitem->setPos(QPointF(-200+Rectangle_Width*process[process.size() - 1].finish_time, 100));
            scene->addItem(txtitem);
        }
        while(t.elapsed() < 1000)
        {
            QCoreApplication::processEvents();
        }
    }
}

void MainWindow::draw_color_process(vector<struct Process> process) {
    for (int i = 0; i < process.size(); i++){
        QBrush color_brush(QColor(colors[i]));
        QPen blackpen(Qt::black);
        blackpen.setWidth(1);
        QGraphicsTextItem *txtitem = new QGraphicsTextItem("P" + QString::number(i + 1));
        txtitem->setScale(1.5);
        txtitem->setPos(QPointF(20,-15 + 30*i));
        rectangle=scene_2->addRect(0,0 + 30*i,15,15,blackpen, color_brush);
        scene_2->addItem(txtitem);
    }
}

void MainWindow::on_submit_clicked()
{
    QString process =  ui->comboBox->currentText();
    ui->label_4->show();
    ui->label_3->show();
    if(process == "FCFS")
    {
        fcfs();
    }
    else if (process == "SJF (Preemptive)")
    {
        sj_permiavtive();
    }
    else if (process == "SJF (Non Preemptive)")
    {
        sj_non();
    }
    else if (process == "Priority (Non Preemptive)")
    {
        priority_non();
    }
    else if (process == "Priority (Preemptive)")
    {
        priority_premative();
    }
    else if(process == "Round Robin")
    {
        round_robin();
    }
}


void  MainWindow::sj_permiavtive()
{
    QString string = ui->lineEdit->text();
    int x = string.toInt();
    vector<float> arrival_time;
    vector<float> arrival_time_sorted ;
    vector<float>duration_time;
    vector<int>priority;
    vector<struct Process> actual_process(x);
    for (int i = 0; i < x; i++)
      {
          QString string_1 = ui->tableWidget->item(i, 0)->text();
          arrival_time.push_back(string_1.toDouble());
          arrival_time_sorted.push_back(string_1.toDouble());
          QString string_2 = ui->tableWidget->item(i, 1)->text();
          duration_time.push_back(string_2.toInt());
          actual_process[i].arrival_time = string_1.toDouble();
          actual_process[i].pid = i + 1;
          actual_process[i].burst_time = string_2.toInt();
      }

    sort(arrival_time_sorted.begin(), arrival_time_sorted.end());
    vector <int> process;
    vector <float> duration;
    vector <int> arrived;

    float time =arrival_time_sorted[0];
    int sj_index = 0;
    int ind = 0;


    for (int arr = 0; arr < x; arr++)
    {
        if (arr <x-1)
        {
            if(arrival_time_sorted[arr] == arrival_time_sorted[arr + 1])continue;
        }
        for (int i = 0; i < x; i++)
        {
            if (arrival_time[i] <= arrival_time_sorted[arr] && duration_time[i] > 0)
            {
                arrived.push_back(i);
            }
        }
        if (arr < x - 1) {
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
                    duration_time[sj_index] -= (arrival_time_sorted[arr + 1] - time);
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


    vector <struct Process> p(process.size());
        float time_2 =arrival_time_sorted[0];

        for(int i=0 ;i<process.size();i++)
        {
            if(process[i] !=-1){
                p[i].pid =  process[i]+1;
                p[i].color = colors[process[i]];
                p[i].start_time= time_2;
                time_2 = time_2 +duration[i];
                p[i].finish_time=time_2;
                p[i].burst_time = duration[i];
            }
            else
            {
                time_2 = time_2 +duration[i];
                p.erase(p.begin() + i);
                process.erase(process.begin() + i);
                duration.erase(duration.begin() + i);
                i-=1;
            }
        }
        for(int i = 0 ;i < p.size() - 1; i++)
        {
            while (p[i].pid == p[i + 1].pid)
            {
                p[i].finish_time=p[i + 1].finish_time;
                p[i].burst_time+=p[i + 1].burst_time;
                p.erase(p.begin()+i + 1);
            }
        }
        vector<bool> first_time(x);
        for (int i =0; i < actual_process.size(); i++) {
            for (int j = 0; j < p.size(); j++) {
                if (actual_process[i].pid == p[j].pid) {
                    if (!first_time[i]) {
                        actual_process[i].start_time = p[j].start_time;
                        first_time[i] = true;
                    }
                    if (p[j].finish_time > actual_process[i].finish_time)
                        actual_process[i].finish_time = p[j].finish_time;
                }
            }
        }
            float waiting_t = waiting_time(actual_process, x);
            ui->label_4->setText(QString::number(waiting_t));
    draw_color_process(actual_process);
    draw(p);
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
          process[i].pid = i + 1;
          process[i].color = colors[i];
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
            swap(process[min_index], process[i]);
        }
        for (int i = 0; i < x; i++) {
            pid[i] = process[i].pid;
            duration[i] = process[i].finish_time - process[i].start_time;
            finish_time[i] = process[i].finish_time;
            start_time[i] = process[i].start_time;
        }
        float waiting_t = waiting_time(process, x);
        ui->label_4->setText(QString::number(waiting_t));
        draw_color_process(process);
        draw(process);
}



void MainWindow::round_robin()
{
    float temp1;
    int temp2, temp3;
    QString string = ui->lineEdit->text();
    vector<float> arrival(string.toInt());
    vector<int> burst_time(string.toInt());
    vector<int> process(string.toInt());
    vector<int> queue(string.toInt());
    vector<int> duration(string.toInt());
    vector<struct Process> actual_process(string.toInt());
            for (int i = 0; i < string.toInt(); i++)
            {
                QString string_1 = ui->tableWidget->item(i,0)->text();
                arrival[i] = string_1.toFloat();
                QString string_2 = ui->tableWidget->item(i,1)->text();
                burst_time[i] = string_2.toInt();
                process[i] = i;
                actual_process[i].arrival_time = arrival[i];
                actual_process[i].pid = i + 1;
                actual_process[i].burst_time = burst_time[i];

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


                struct Process temp;

                for (int i =0 ; i<n ;i++)
                {
                    temp.pid = queue[i];
                    temp.arrival_time =arrival[i];
                    temp.burst_time =duration[i];
                    p.push_back(temp);
                }


                std::queue<struct Process> q;
                std::queue <struct Process> ready_q;


                for (int i = 0; i < n; i++) {
                    q.push(p[i]);
                    p.pop_back();
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

                            temp.start_time =time;
                            temp.burst_time = quantum;
                            time += quantum;
                            temp.finish_time =time;
                            temp.color= colors[(ready_q.front().pid)];
                            temp.pid = ready_q.front().pid + 1;
                            p.push_back(temp);
                            temp = (ready_q.front());
                            ready_q.pop();
                            finished = false;

                        }
                        else {
                            temp.start_time =time;
                            time += (ready_q.front()).burst_time;


                            temp.burst_time = (ready_q.front()).burst_time;
                            temp.finish_time =time;
                            temp.color= colors[ready_q.front().pid];
                            temp.pid = ready_q.front().pid + 1;
                            p.push_back(temp);
                            ready_q.front().burst_time = 0;
                            finished = true;
                            temp = (ready_q.front());
                            ready_q.pop();
                        }

                    }
                    else if (!q.empty()) {
                        time = (q.front()).arrival_time;
                    }
                }
                vector<bool> first_time(string.toInt());
                for (int i =0; i < actual_process.size(); i++) {
                    for (int j = 0; j < p.size(); j++) {
                        if (actual_process[i].pid == p[j].pid) {
                            if (!first_time[i]) {
                                actual_process[i].start_time = p[j].start_time;
                                first_time[i] = true;
                            }
                            if (p[j].finish_time > actual_process[i].finish_time)
                                actual_process[i].finish_time = p[j].finish_time;
                        }
                    }
                }
                float waiting_t = waiting_time(actual_process, string.toInt());
                ui->label_4->setText(QString::number(waiting_t));
                draw_color_process(actual_process);
            draw(p);

}

void  MainWindow::priority_premative()
{
    QString string = ui->lineEdit->text();
    int x = string.toInt();
    vector<float> arrival_time;
    vector<float> arrival_time_sorted ;
    vector<float>duration_time;
    vector<int>priority;
    vector<struct Process> actual_process(x);
    for (int i = 0; i < x; i++)
      {
          QString string_1 = ui->tableWidget->item(i, 0)->text();
          arrival_time.push_back(string_1.toDouble());
          arrival_time_sorted.push_back(string_1.toDouble());
          QString string_2 = ui->tableWidget->item(i, 1)->text();
          duration_time.push_back(string_2.toInt());
          QString string_3 = ui->tableWidget->item(i, 2)->text();
          priority.push_back(string_3.toInt());
          actual_process[i].arrival_time = string_1.toDouble();
          actual_process[i].pid = i + 1;
          actual_process[i].burst_time = string_2.toInt();
      }

    sort(arrival_time_sorted.begin(), arrival_time_sorted.end());
    vector <int> process;
    vector <float> duration;
    vector <int> arrived;
    float time =arrival_time_sorted[0];
    int sj_index = 0;
    int ind = 0;

    for (int arr = 0; arr < x; arr++)
    {
        if (arr <x-1)
        {
            if(arrival_time_sorted[arr] == arrival_time_sorted[arr + 1])continue;
        }
        for (int i = 0; i < x; i++)
        {
            if (arrival_time[i] <= arrival_time_sorted[arr] && duration_time[i] > 0)
            {
                arrived.push_back(i);
            }
        }
        if (arr < x - 1) {
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

    vector <struct Process> p(process.size());
        float time_2 =arrival_time_sorted[0];

        for(int i=0 ;i<process.size();i++)
        {
            if(process[i] !=-1){
                p[i].pid =  process[i]+1;
                p[i].color = colors[process[i]];
                p[i].start_time= time_2;
                time_2 = time_2 +duration[i];
                p[i].finish_time=time_2;
                p[i].burst_time = duration[i];
            }
            else
            {
                time_2 = time_2 +duration[i];
                p.erase(p.begin() + i);
                process.erase(process.begin() + i);
                duration.erase(duration.begin() + i);
                i -= 1;
            }
        }
        for(int i = 0 ;i < p.size() - 1; i++)
        {
            while (p[i].pid == p[i + 1].pid)
            {
                p[i].finish_time=p[i + 1].finish_time;
                p[i].burst_time+=p[i + 1].burst_time;
                p.erase(p.begin()+i + 1);
            }
        }
        vector<bool> first_time(x);
        for (int i =0; i < actual_process.size(); i++) {
            for (int j = 0; j < p.size(); j++) {
                if (actual_process[i].pid == p[j].pid) {
                    if (!first_time[i]) {
                        actual_process[i].start_time = p[j].start_time;
                        first_time[i] = true;
                    }
                    if (p[j].finish_time > actual_process[i].finish_time)
                        actual_process[i].finish_time = p[j].finish_time;
                }
            }
        }
            float waiting_t = waiting_time(actual_process, x);
            ui->label_4->setText(QString::number(waiting_t));
            draw_color_process(actual_process);
            draw(p);
}

void  MainWindow::fcfs()
{
    float temp1;
            int temp2, temp3;
            QString string = ui->lineEdit->text();
            vector<float> arrival(string.toInt());
            vector<int> burst_time(string.toInt());
            vector<int> process(string.toInt());
            vector<int> queue(string.toInt());
            vector<int> duration(string.toInt());

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
            vector<struct Process> p(string.toInt());
            vector<float> start_time(string.toInt());
            vector<float> finish_time(string.toInt());
            for(int i = 0; i < string.toInt(); i++)
            {
                    if (i == 0)
                        start_time[i] = arrival[i];
                    else if (finish_time[i - 1] > arrival[i])
                        start_time[i] = finish_time[i-1];
                    else
                        start_time[i] = arrival[i];
                    finish_time[i] = start_time[i] + burst_time[i];
                    p[i].start_time = start_time[i];
                    p[i].finish_time = finish_time[i];
                    p[i].burst_time = burst_time[i];
                    p[i].color = colors[process[i]];
                    p[i].arrival_time = arrival[i];
            }
            float waiting_t = waiting_time(p, string.toInt());
            ui->label_4->setText(QString::number(waiting_t));
            draw_color_process(p);
            draw(p);
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
          process[i].pid = i + 1;
          process[i].color = colors[i];

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
//                swap(process[min_index].start_time, process[i].start_time);
//                swap(process[min_index].finish_time, process[i].finish_time);
//                swap(process[min_index].pid, process[i].pid);
//                swap(process[min_index].arrival_time, process[i].arrival_time);
//                swap(process[min_index].burst_time, process[i].burst_time);
//                swap(process[min_index].waiting_time, process[i].waiting_time);
//                swap(process[min_index].priority, process[i].priority);
//                swap(process[min_index].color, process[i].color);
                 swap(process[min_index], process[i]);
            }
            for (int i = 0; i < x; i++) {
                pid[i] = process[i].pid;
                duration[i] = process[i].finish_time - process[i].start_time;
                finish_time[i] = process[i].finish_time;
                start_time[i] = process[i].start_time;
            }
            float waiting_t = waiting_time(process, x);
            ui->label_4->setText(QString::number(waiting_t));
            draw_color_process(process);
            draw(process);
}


float MainWindow::waiting_time(vector <Process> p,int n) {
    QString choosed_process =  ui->comboBox->currentText();
    float waiting_t = 0;

        for (int i = 0; i < n; i++) {
            waiting_t += (p[i].finish_time - p[i].arrival_time - p[i].burst_time);
        }
        waiting_t = (float) waiting_t / n;

    return waiting_t;
}
