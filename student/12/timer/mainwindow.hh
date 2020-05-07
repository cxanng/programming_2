#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Normally this member should be in private part of the
    // class, but due to the automated tests it must be more
    // accessible.
    QTimer* timer;

private slots:
    // Add your slots here
    void running();


private:
    Ui::MainWindow *ui;
    int sec = 0;
    int min = 0;
    // Add other necessary members here
    void start_timer();
    void stop_timer();
    void reset_timer();
};

#endif // MAINWINDOW_HH
