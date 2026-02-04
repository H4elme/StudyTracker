#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSpinBox>
#include <QTimer>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool decrease(QSpinBox*);
    void update();
    void startMyTimer();
    ~MainWindow();
private:
    QSpinBox *seconds;
    QSpinBox *minutes;
    QSpinBox *hours;
    QTimer *timer;
};
#endif // MAINWINDOW_H
