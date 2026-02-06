#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->resize(1000, 1000);

    auto outer = new QVBoxLayout(this);
    auto top = new QHBoxLayout();

    seconds = new QSpinBox();
    minutes = new QSpinBox();
    hours = new QSpinBox();

    seconds->setMaximum(59);
    minutes->setMaximum(59);
    hours->setMaximum(59);
    seconds->setWrapping(true);
    minutes->setWrapping(true);
    hours->setWrapping(true);

    top->addWidget(hours);
    top->addWidget(minutes);
    top->addWidget(seconds);

    auto startButton = new QPushButton("START");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            this, &MainWindow::update);

    connect(startButton, &QPushButton::pressed,
            this, &MainWindow::startMyTimer);
    outer->addLayout(top);
    outer->addWidget(startButton);

    this->setLayout(outer);
}

MainWindow::~MainWindow() {}

void MainWindow::update() {
    if (totalSeconds) {
        qDebug() << totalSeconds;
        totalSeconds--;
        hours->setValue(totalSeconds / 3600);
        minutes->setValue((totalSeconds % 3600) / 60);
        seconds->setValue((totalSeconds % 3600) % 60);
    }
}

void MainWindow::startMyTimer() {
    totalSeconds = hours->text().toInt() * 3600 + minutes->text().toInt() * 60 + seconds->text().toInt();
    timer->start(1000);
}
