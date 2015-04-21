#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_res_btn_clicked();

private:
    int *firstArr[];
    int *secondArr[];
    Ui::MainWindow *ui;
    void readData();
};

#endif // MAINWINDOW_H
