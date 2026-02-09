#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QTimer>
#include <QDebug>
#include <QProgressBar>
#include <QStackedWidget>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->resize(720, 720);

    auto outer = new QVBoxLayout(this);
    auto inputPage = new QWidget();
    auto timerPage = new QWidget();

    auto inputLayout = new QHBoxLayout(inputPage);
    auto timerLayout = new QVBoxLayout(timerPage);

    seconds = new QSpinBox();
    minutes = new QSpinBox();
    hours = new QSpinBox();

    seconds->setMaximum(59);
    minutes->setMaximum(59);
    hours->setMaximum(59);
    seconds->setWrapping(true);
    minutes->setWrapping(true);
    hours->setWrapping(true);

    inputLayout->addWidget(hours);
    inputLayout->addWidget(minutes);
    inputLayout->addWidget(seconds);

    auto startButton = new QPushButton("START");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            this, &MainWindow::update);

    connect(startButton, &QPushButton::pressed,
            this, &MainWindow::startMyTimer);


    timerLabel = new QLabel();

    timerLabel->setAlignment(Qt::AlignCenter);
    // move styles to .qss files later?
    QFont font = timerLabel->font();
    font.setFamily("Helvetica");
    font.setPointSize(12);
    font.setBold(true);
    timerLabel->setFont(font);

    progressBar = new QProgressBar(this);
    progressBar->setTextVisible(false);
    timerLayout->addWidget(timerLabel);
    timerLayout->addWidget(progressBar);

    // add a class for second page. there just change the pause/continue button, keep everything else the same.
    stackedWidget = new QStackedWidget(this);

    stackedWidget->addWidget(inputPage);
    stackedWidget->addWidget(timerPage);
    outer->addWidget(stackedWidget);
    outer->addWidget(startButton);
    this->setLayout(outer);
}

MainWindow::~MainWindow() {}

void MainWindow::updateTimerLabel() {
    int curHours = totalSeconds / 3600;
    int curMinutes = (totalSeconds % 3600) / 60;
    int curSeconds = (totalSeconds % 3600) % 60;

    QString str = QString("%1:%2:%3")
                      .arg(curHours, 2, 10, QChar('0'))
                      .arg(curMinutes, 2, 10, QChar('0'))
                      .arg(curSeconds, 2, 10, QChar('0'));
    timerLabel->setText(str);
}

void MainWindow::update() {
    if (totalSeconds) {
        qDebug() << totalSeconds;
        totalSeconds--;
        updateTimerLabel();
        progressBar->setValue(totalSeconds);
    }
    else {
        stackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::startMyTimer() {
    totalSeconds = hours->text().toInt() * 3600 + minutes->text().toInt() * 60 + seconds->text().toInt();
    stackedWidget->setCurrentIndex(1);
    updateTimerLabel();
    progressBar->setRange(0, totalSeconds);
    progressBar->setValue(totalSeconds);
    timer->start(1000);
}

void MainWindow::pauseMyTimer() {

}
