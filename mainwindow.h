#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mytimerpage.h"
#include "historytab.h"
#include "sessionstable.h"
#include <QWidget>
#include <QSpinBox>
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
    void stopMyTimer();
    void continueMyTimer();
    void updateTimerLabel();
    ~MainWindow();
private:
    QSpinBox *seconds;
    QSpinBox *minutes;
    QSpinBox *hours;
    QTimer *timer;
    QStackedWidget *stackedWidget;

    TimerPage *activePage;
    TimerPage *pausedPage;

    HistoryTab *historyTab;

    int totalSeconds = 0;
    int initialSeconds = 0;
    void closeEvent(QCloseEvent *event) override;

    SessionsTable *sessions;
signals:
    void timerStopped();
};
#endif // MAINWINDOW_H
