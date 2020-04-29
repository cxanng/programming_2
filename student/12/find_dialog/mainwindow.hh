#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

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
    void on_fileLineEdit_editingFinished();

    void on_keyLineEdit_editingFinished();

private:
    Ui::MainWindow *ui;
    std::string convert(std::string str);
    bool find_text(std::string find_from, std::string find_what);
    void terminate();
};
#endif // MAINWINDOW_H
