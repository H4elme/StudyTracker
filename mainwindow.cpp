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

    seconds->setValue(5);
    minutes->setValue(5);
    hours->setValue(1);
    qDebug() << (seconds->text()).toInt();

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

bool MainWindow::decrease(QSpinBox *spinBox) {
    int num = (spinBox->text()).toInt();
    if (!num) return false;
    spinBox->setValue(--num);
    return true;
}

void MainWindow::update() {
    if (!decrease(seconds)) {
        if (!decrease(minutes)) {
            if (!decrease(hours)) {
                // stop timer
            }
            else {
                minutes->setValue(59);
                seconds->setValue(59);
            }
        }
        else {
            seconds->setValue(59);
        }
    }
}

void MainWindow::startMyTimer() {
    timer->start(1000);
}
