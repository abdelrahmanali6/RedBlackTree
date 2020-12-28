#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "RedBlackTree.h"
#include "Node.h"

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

    void on_DeleteElement_clicked();

    void on_ClearAll_clicked();

private:
    Ui::MainWindow *ui;
protected:
    RedBlackTree *x;
};
#endif // MAINWINDOW_H
