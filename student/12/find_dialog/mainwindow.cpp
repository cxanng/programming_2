#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <QTextStream>
#include <QDebug>
#include <algorithm>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (ui->findPushButton->isFlat()) {
        on_fileLineEdit_editingFinished();
        on_keyLineEdit_editingFinished();
    }
    connect(ui->closePushButton, &QPushButton::clicked, this, &MainWindow::terminate);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileLineEdit_editingFinished()
{
    std::string file_name = ui->fileLineEdit->text().toStdString();
    std::ifstream file_object(file_name);
    if (!file_object) {
        ui->textBrowser->setText("File not found");
    }
    else {
        ui->textBrowser->setText("File found");
    }
}



void MainWindow::on_keyLineEdit_editingFinished()
{
    std::string file_name = ui->fileLineEdit->text().toStdString();
    std::ifstream file_object(file_name);
    if (!file_object) {
        return;
    }

    std::string find_what = ui->keyLineEdit->text().toStdString();
    if (find_what == "") {
        return;
    }
    bool check = ui->matchCheckBox->isChecked();
    ui->textBrowser->reload();
    std::string line = "";
    bool found = false;
    while( getline(file_object, line)) {
        if (check) {
            line = convert(line);
            find_what = convert(find_what);
        }
        if (find_text(line, find_what)) {
            found = true;
            break;
        }
    }
    if (found) {
       ui->textBrowser->setText("Word found");
    }
    else {
        ui->textBrowser->setText("Word not found");
    }
}

std::string MainWindow::convert(std::string str) {
    std::string result = "";
    for (char ch : str) {
        result += toupper(ch);
    }
    return result;
}

bool MainWindow::find_text(std::string find_from, std::string find_what) {
    std::string::size_type location = find_from.find(find_what, 0);
    if (location == std::string::npos) {
        return false;
    }
    else {
        return true;
    }
}

void MainWindow::terminate() {
    this->close();
}

