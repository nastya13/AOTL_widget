#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_res_btn_clicked()
{
    readData();
}

void MainWindow::readData()
{
    //-------------------------------------------//
    //read value from left text edit
    QString leftText = ui->leftText->toPlainText();

    //find number of lines
    int numN1 = leftText.split('\n').length();

    //array for lines
    QString strL[numN1];
    for (int i=0; i<numN1; i++)
        strL[i] = leftText.split('\n')[i];

    //find number of elements in lines
    int m = strL[0].length()/2+1;

    //create matrix
    int leftArr[numN1][m];
    bool b = true;

    //check on correct data
    for (int i=1;i<numN1;i++)
    {

        if (strL[i].length()/2+1!= m)
        {
            b = false;
            break;
        }
    }
    //generate matrix
    if (b) {
        for (int i=0; i<numN1; i++)
            for (int j=0; j<m; j++)
            {
                leftArr[i][j] = strL[i].split(' ')[j].toInt();
            }
    }
    else
    {
        ui->res_lbl->setStyleSheet("font: 8pt");
        ui->res_lbl->setText("Результат: Ошибка 1. Проверьте корректность введеннных данных для левой полки.");
    }


    //--------------------------------------------//
    //read value from right text edit
    QString rightText = ui->rightText->toPlainText();

    //find number of lines
    int numN2 = rightText.split('\n').length();

    //array for lines
    QString strR[numN2];
    for (int i=0; i<numN2; i++)
        strR[i] = rightText.split('\n')[i];

    //find number of elements in lines
    int m2 = strR[0].length()/2+1;

    //create matrix
    int rightArr[numN2][m];
    bool bb = true;

    //check on correct data from left and right text editor in summary
    if (m != m2)
    {
        ui->res_lbl->setStyleSheet("font: 8pt");
        ui->res_lbl->setText("Результат: Ошибка 2. Словарь левой и правой полки отличается. Количество столбцов должно быть одинаково.");
    } else {

        //check on correct data and generate matrix
        for (int i=0; i<numN2; i++)
            for (int j=0; j<m; j++)
            {
                if (strR[i].length()/2+1!=m)
                {
                    bb = false;
                    break;
                }
                rightArr[i][j] = strR[i].split(' ')[j].toInt();
            }

        //give error
        if (!bb) {ui->res_lbl->setStyleSheet("font: 8pt"); ui->res_lbl->setText("Результат: Ошибка 3. Проверьте корректность введеннных данных для правой полки.");}
    }

    //if all data os correct do calculations
    if (b && bb) {
        double pfa = 1.0 * numN1 / (numN1+numN2);
        double psa = 1.0 * numN1 / (numN1+numN2);
        int leng = ui->newText->toPlainText().split(' ').length()/2+1;
        if (leng != m)
        {
            ui->res_lbl->setStyleSheet("font: 8pt");
            ui->res_lbl->setText("Результат: Ошибка 4. Словарь искомой книги должен совпадать с общим словарем.");
        }
        else {
            int d[m];
            for (int i=0;i<m;i++)
                d[i] = ui->newText->toPlainText().split(' ')[i].toInt();
            double pdcfa = 1.0;
            int count = 0;
            for (int i=0; i<m; i++)
            {

                for (int j=0; j<numN1; j++)
                {
                    if (leftArr[j][i] == 1) count++;
                }
                pdcfa = pdcfa * ((d[i] * 1.0 * count / numN1) + ((1-d[i])* (1 - 1.0 * count / numN1)));
                count = 0;
            }

            double pdcsa = 1.0;
            count = 0;
            for (int i=0; i<m; i++)
            {

                for (int j=0; j<numN2; j++)
                {
                    if (rightArr[j][i] == 1) count++;
                }
                pdcsa = pdcsa * ((d[i] * 1.0 * count / numN2) + ((1-d[i])* (1 - 1.0 * count / numN2)));
                count = 0;
            }


            double ans1 = pfa * pdcfa;
            double ans2 = psa * pdcsa;

            if (ans1 > ans2)
            {
                ui->res_lbl->setStyleSheet("font: 14pt");
                ui->res_lbl->setText("Результат: Левая полка");
            }
            else {ui->res_lbl->setStyleSheet("font: 14pt");ui->res_lbl->setText("Результат: Правая полка");}
        }
    }
}
