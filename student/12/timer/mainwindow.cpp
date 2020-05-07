#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(running()));
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::start_timer);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::reset_timer);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stop_timer);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::running()
{
    this->sec += 1;
    if (this->sec == 60) {
        this->min +=1;
        this->sec = 0;
    }
    ui->lcdNumberMin->display(this->min);
    ui->lcdNumberSec->display(this->sec);
}
void MainWindow::start_timer() {
    if (!timer->isActive()) {
        timer->start(1000);
    }

}

void MainWindow::stop_timer() {
    timer->stop();
    ui->lcdNumberMin->display(this->min);
    ui->lcdNumberSec->display(this->sec);
}

void MainWindow::reset_timer() {
    this->min = 0;
    this->sec = 0;
    ui->lcdNumberMin->display(this->min);
    ui->lcdNumberSec->display(this->sec);

}
