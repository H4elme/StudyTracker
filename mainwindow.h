#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSpinBox>
#include <QTimer>
#include <QProgressBar>
#include <QLabel>
#include <QStackedWidget>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool decrease(QSpinBox*);
    void update();
    void startMyTimer();
    void pauseMyTimer();
    void updateTimerLabel();
    ~MainWindow();
private:
    QSpinBox *seconds;
    QSpinBox *minutes;
    QSpinBox *hours;
    QTimer *timer;
    QProgressBar *progressBar;
    QLabel *timerLabel;
    QStackedWidget *stackedWidget;
    int totalSeconds = 0;
};
#endif // MAINWINDOW_H
