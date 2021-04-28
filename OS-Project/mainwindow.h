#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <vector>
#include<Qcolor>
const int Rectangle_Width=30;
const int Rectangle_Height=100;
struct Process {
    int pid;
    float arrival_time;
    float burst_time;
    int priority;
    float waiting_time;
    float start_time;
    float finish_time;
    QColor color;
};
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void sj_permiavtive();
    void sj_non();
    void priority_premative();
    void fcfs();
    void on_submit_clicked();
    void round_robin();
    void priority_non();
    void draw(std::vector<struct Process> process);
    float waiting_time(std::vector<struct Process> process, int n);
    void draw_color_process(std::vector<struct Process> process);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsScene *scene_2;
    QTimer *timer;
    QGraphicsRectItem *rectangle;
    QColor colors[11] = {QColor("red"), QColor("green"), QColor("yellow"),
                          QColor("blue"), QColor("orange"), QColor("pink"),
                          QColor("magenta"), QColor("brown"), QColor("purple"),
                          QColor("gold"), QColor("cyan")};
};
#endif // MAINWINDOW_H
