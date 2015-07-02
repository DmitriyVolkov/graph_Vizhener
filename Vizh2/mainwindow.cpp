#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sstream>
#include <fstream>
using namespace std;
#include <QFileDialog>
QString infile, outfile;
string input,output,s;
string key2;
QString key;

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
void MainWindow::on_pushButton_clicked()
{
    infile=QFileDialog::getOpenFileName(this,tr("Открыть файл"),"/Users/","Allfiles(*)");
    input = infile.toStdString();

    ifstream in(input.c_str());
   getline(in,s);
   in.close();
    ui->lineEdit_3->setText(QString::fromStdString(s));

}
void MainWindow::on_pushButton_4_clicked()
{
    outfile=QFileDialog::getOpenFileName(this,tr("Открыть файл"),"/Users/","Allfiles(*)");
    output = outfile.toStdString();
}
void MainWindow::on_pushButton_2_clicked()
{
     output = outfile.toStdString();
    string result = "";
    ifstream in(input.c_str());


     string key_on_s = "";
            bool flag;
            int x = 0, y = 0; //Координаты нового символа из таблицы Виженера
            int registr = 0; //Регистр символа
            char dublicat; //Дубликат прописной буквы
            //Формирование таблицы Виженера на алфавите латиницы
            int shift = 0;
            char **tabula_recta = new char *[26];
            for (int i = 0; i < 26; i++)
                tabula_recta[i] = new char[26];
            string alfabet = "abcdefghijklmnopqrstuvwxyz";
            //Формирование таблицы
            for (int i = 0; i < 26; i++)
                for (int j = 0; j < 26; j++)
                {
                    shift = j + i;
                    if (shift >= 26) shift = shift % 26;
                    tabula_recta[i][j] = alfabet[shift];
                }

            string s;
                getline(in, s);

                in.close();
                //Формирование строки, длиной шифруемой, состоящей из повторений ключа
                for (int i = 0; i < s.length(); i++)
                {
                    key_on_s += key2[i % key2.length()];
                }
                //Шифрование при помощи таблицы
                for (int i = 0; i < s.length(); i++)
                {
                    //Если нешифруемый символ
                    if (((int)(s[i]) < 65) || ((int)(s[i]) > 122))
                        result += s[i];
                    else
                    {
                        //Поиск в первом столбце строки, начинающейся с символа ключа
                        int l = 0;
                        flag = false;
                        while ((l < 26) && (flag == false))
                        {
                            if (key_on_s[i] == tabula_recta[l][0])
                            {
                                //Запоминаем в х номер строки
                                x = l;
                                flag = true;
                            }
                            l++;
                        }
                        //Уменьшаем временно регистр прописной буквы
                        if (((int)(s[i]) <= 90) && ((int)(s[i]) >= 65))
                        {
                            dublicat = (char)((int)(s[i]) + 32);
                            registr = 1;
                        }
                        else
                        {
                            registr = 0;
                            dublicat = s[i];
                        }
                        l = 0;
                        flag = false;
                        //Пока не найден столбец в первой строке с символом строки
                        while ((l < 26) && (flag == false))
                        {
                            if (dublicat == tabula_recta[0][l])
                            {
                                //Запоминаем номер столбца
                                y = l;
                                flag = true;
                            }
                            l++;
                        }
                        //Увеличиваем регистр буквы до прописной
                        if (registr == 1)
                        {
                            //Изменяем символ на первоначальный регистр
                            dublicat = char((int)(tabula_recta[x][y]) - 32);
                            result += dublicat;
                        }
                        else
                            result += tabula_recta[x][y];
                    }
                }
    ui->label->setText(QString::fromStdString(result));
    ofstream out(output.c_str());
        out<<result;
       out.close();

}

void MainWindow::on_lineEdit_2_editingFinished()
{

   key=ui->lineEdit_2->text();
   key2 = key.toStdString();
  // ui->label->setText(QString::fromStdString(key2));

}

void MainWindow::on_lineEdit_3_editingFinished()
{
   // QString filename;
   //filename = ui->lineEdit_3->text();
   //input = filename.toStdString();

}

void MainWindow::on_pushButton_3_clicked()
{
    output = outfile.toStdString();
    string result = "";
    string key_on_s = "";
     ifstream in(input.c_str());
    bool flag;
    int x = 0, y = 0; //Координаты нового символа из таблицы Виженера
    int registr = 0; //Регистр символа
    char dublicat; //Дубликат прописной буквы
    //Формирование таблицы Виженера на алфавите латиницы
    int shift = 0;
    char **tabula_recta = new char *[26];
    for (int i = 0; i < 26; i++)
        tabula_recta[i] = new char[26];
    string alfabet = "abcdefghijklmnopqrstuvwxyz";
    //Формирование таблицы
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
        {
            shift = j + i;
            if (shift >= 26) shift = shift % 26;
            tabula_recta[i][j] = alfabet[shift];
        }
    string s;
            getline(in, s);

            in.close();
            //Формирование строки, длиной дешифруемой, состоящей из повторений ключа
            for (int i = 0; i < s.length(); i++)
            {
                key_on_s += key2[i % key2.length()];
            }
            //Дешифрование при помощи таблицы
            for (int i = 0; i < s.length(); i++)
            {
                if (((int)(s[i]) < 65) || ((int)(s[i]) > 122))
                    result += s[i];
                else
                {
                    //Поиск в первом столбце строки, начинающейся с символа ключа
                    int l = 0;
                    flag = false;
                    //Пока не найден символ
                    while ((l < 26) && (flag == false))
                    {
                        if (key_on_s[i] == tabula_recta[l][0])
                        {
                            //Запоминаем в х номер строки
                            x = l;
                            flag = true;
                        }
                        l++;
                    }
                    //Уменьшаем временно регистр прописной буквы
                    if (((int)(s[i]) <= 90) && ((int)(s[i]) >= 65))
                    {
                        dublicat = (char)((int)(s[i]) + 32);
                        registr = 1;
                    }
                    else
                    {
                        registr = 0;
                        dublicat = s[i];
                    }
                    l = 0;
                    flag = false;
                    //Пока не найден столбец в x строке с символом строки
                    while ((l < 26) && (flag == false))
                    {
                        if (dublicat == tabula_recta[x][l])
                        {
                            //Запоминаем номер столбца
                            y = l;
                            flag = true;
                        }
                        l++;
                    }
                    //Увеличиваем регистр буквы до прописной
                    if (registr == 1)
                    {
                        dublicat = char((int)(tabula_recta[0][y]) - 32);
                        result += dublicat;
                    }
                    else
                        result += tabula_recta[0][y];
                }
            }
            ui->label->setText(QString::fromStdString(result));
            ofstream out(output.c_str());
                       out<<result;
                      out.close();
}
