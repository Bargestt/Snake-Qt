#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gw = new GameWindow(this);
    gw->show();

    resize(400,400);

}

MainWindow::~MainWindow()
{
    delete ui;
}
