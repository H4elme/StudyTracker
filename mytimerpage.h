#ifndef MYTIMERPAGE_H
#define MYTIMERPAGE_H

#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include <QTimer>
#include <QPushButton>

class TimerPage : public QWidget
{
    Q_OBJECT
public:
    explicit TimerPage(QWidget *parent = nullptr, bool running_ = true);
    ~TimerPage();
    QPushButton *stopButton;
    QPushButton *mainButton;
    QProgressBar *progressBar;
    QLabel *timerLabel;
private:
    bool running;
signals:
};

#endif // MYTIMERPAGE_H
