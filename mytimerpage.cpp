#include "mytimerpage.h"
#include <QWidget>
#include <QTimer>
#include <QPushButton>
#include <QVBoxLayout>

TimerPage::TimerPage(QWidget *parent, bool running_)
    : QWidget{parent}
{
    auto timerLayout = new QVBoxLayout(this);
    progressBar = new QProgressBar();
    progressBar->setTextVisible(false);

    timerLabel = new QLabel();
    timerLabel->setAlignment(Qt::AlignCenter);
    auto font = timerLabel->font();
    font.setFamily("Helvetica");
    font.setPointSize(12);
    font.setBold(true);
    timerLabel->setFont(font);

    stopButton = new QPushButton("STOP");
    QString text = (running_ ? "PAUSE" : "RESUME");
    mainButton = new QPushButton(text);

    timerLayout->addWidget(timerLabel);
    timerLayout->addWidget(mainButton);
    timerLayout->addWidget(stopButton);
    timerLayout->addWidget(progressBar);

    this->setLayout(timerLayout);
}

TimerPage::~TimerPage() {}

