#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "RedBlackTree.h"
#include "Node.h"
#include <string>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   x = new RedBlackTree();
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString inserted = ui->Insert->text();
    x->insert(inserted.split(" ")[0].toInt());
    QString output = QString::fromStdString(x->printTree());
    QString newString="";
    for(int i=0; i<output.length(); i++)
    {
            if(output[i].isDigit() && output[i-1] != 'l' && !output[i-1].isDigit() && output[i-1] !='-'&& output[i-2] != 'l')
            {
                newString += "     ";
            }
            else if(output[i] == '-')
            {
                newString += "     ";
            }
            newString += output[i];
    }
    ui->label->setText(newString);
}

void MainWindow::on_DeleteElement_clicked()
{
    QString value = ui->lineEdit->text();
    x->deleteByVal(value.split(" ")[0].toInt());
    QString output = QString::fromStdString(x->printTree());
    QString newString="";
    for(int i=0; i<output.length(); i++)
    {
            if(output[i].isDigit() && output[i-1] != 'l' && !output[i-1].isDigit() && output[i-1] !='-'&& output[i-2] != 'l')
            {
                newString += "     ";
            }
            else if(output[i] == '-')
            {
                newString += "     ";
            }
            newString += output[i];
    }
    ui->label->setText(newString);
}

void MainWindow::on_ClearAll_clicked()
{
    x->clear();
    QString newString = " ";
    ui->label->setText(newString);
}
