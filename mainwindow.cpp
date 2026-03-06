#include "mainwindow.h"
#include "historytab.h"
#include <QVBoxLayout>
#include <QTabWidget>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    sessions = new SessionsTable();
    sessions->initDatabase();
    this->setMinimumSize(600, 400);
    auto tabs = new QTabWidget(this);

    auto timerTab = new QWidget(this);
    historyTab = new HistoryTab(this);

    auto mainLayout = new QVBoxLayout(this);

    auto outer = new QVBoxLayout();
    auto inputPage = new QWidget();
    auto inputLayout = new QVBoxLayout(inputPage);
    auto inputInnerLayout = new QHBoxLayout();

    seconds = new QSpinBox();
    minutes = new QSpinBox();
    hours = new QSpinBox();

    seconds->setMaximum(59);
    minutes->setMaximum(59);
    hours->setMaximum(59);
    seconds->setWrapping(true);
    minutes->setWrapping(true);
    hours->setWrapping(true);

    auto startButton = new QPushButton("START");

    inputInnerLayout->addWidget(hours);
    inputInnerLayout->addWidget(minutes);
    inputInnerLayout->addWidget(seconds);

    inputLayout->addLayout(inputInnerLayout);
    inputLayout->addWidget(startButton);


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            this, &MainWindow::update);

    connect(startButton, &QPushButton::pressed,
            this, &MainWindow::startMyTimer);


    stackedWidget = new QStackedWidget(this);

    activePage = new TimerPage(this);
    pausedPage = new TimerPage(this, false);

    connect(activePage->stopButton, &QPushButton::pressed,
            this, &MainWindow::stopMyTimer);
    connect(pausedPage->stopButton, &QPushButton::pressed,
            this, &MainWindow::stopMyTimer);

    connect(pausedPage->mainButton, &QPushButton::pressed,
            this, &MainWindow::continueMyTimer);

    connect(activePage->mainButton, &QPushButton::pressed,
            this, &MainWindow::pauseMyTimer);


    stackedWidget->addWidget(inputPage);
    stackedWidget->addWidget(activePage);
    stackedWidget->addWidget(pausedPage);

    outer->addWidget(stackedWidget);
    timerTab->setLayout(outer);
    tabs->addTab(timerTab, "Timer");
    tabs->addTab(historyTab, "History");

    mainLayout->addWidget(tabs);

    connect(this, &MainWindow::timerStopped,
            historyTab, &HistoryTab::refreshDB);
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
    activePage->timerLabel->setText(str);
    pausedPage->timerLabel->setText(str);
}

void MainWindow::update() {
    if (totalSeconds) {
        totalSeconds--;
        updateTimerLabel();
        activePage->progressBar->setValue(totalSeconds);
        pausedPage->progressBar->setValue(totalSeconds);
    }
    else {
        stopMyTimer();
    }
}

void MainWindow::startMyTimer() {
    totalSeconds = hours->text().toInt() * 3600 + minutes->text().toInt() * 60 + seconds->text().toInt();
    if (totalSeconds > 0) {
        initialSeconds = totalSeconds;
        stackedWidget->setCurrentIndex(1);
        updateTimerLabel();
        activePage->progressBar->setRange(0, totalSeconds);
        pausedPage->progressBar->setRange(0, totalSeconds);
        activePage->progressBar->setValue(totalSeconds);
        pausedPage->progressBar->setValue(totalSeconds);
        timer->start(1000);
    }
}

void MainWindow::continueMyTimer() {
    stackedWidget->setCurrentIndex(1);
    timer->start(1000);
}

void MainWindow::pauseMyTimer() {
    timer->stop();
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::stopMyTimer() {
    timer->stop();
    stackedWidget->setCurrentIndex(0);
    if (initialSeconds - totalSeconds > 0) sessions->insertSession("Work", initialSeconds - totalSeconds);
    initialSeconds = 0;
    emit timerStopped();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (timer->isActive()) {
        stopMyTimer();
    }
    event->accept();
}
