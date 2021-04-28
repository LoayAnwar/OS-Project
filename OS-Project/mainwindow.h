#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void priority_premative();
    void fcfs();
    void on_submit_clicked();
    void round_robin();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
