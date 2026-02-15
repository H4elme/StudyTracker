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
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->resize(720, 720);

    auto outer = new QVBoxLayout(this);
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
    activePage->timerLabel->setText(str);
    pausedPage->timerLabel->setText(str);
}

void MainWindow::update() {
    if (totalSeconds) {
        qDebug() << totalSeconds;
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
    initialSeconds = totalSeconds;
    stackedWidget->setCurrentIndex(1);
    updateTimerLabel();
    activePage->progressBar->setRange(0, totalSeconds);
    pausedPage->progressBar->setRange(0, totalSeconds);
    activePage->progressBar->setValue(totalSeconds);
    pausedPage->progressBar->setValue(totalSeconds);
    timer->start(1000);
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
    insertSession("Work", initialSeconds - totalSeconds);
}

void MainWindow::initDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("study_tracker.db");

    if (!db.open()) {
        qDebug() << "Error: can't connect to the database: " << db.lastError().text() << '\n';
    }
    else {
        qDebug() << "Connected.\n";
        createTable();
    }
}

void MainWindow::createTable() {
    QSqlQuery query;
    query.exec("DROP TABLE session;");
    QString queryStr = "CREATE TABLE IF NOT EXISTS sessions ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "type TEXT,"
        "duration INTEGER,"
        "start_time TEXT DEFAULT (datetime('now', 'localtime'))"
    ");";
    if (!query.exec(queryStr)) {
        qDebug() << "Error: can't create the table: " << query.lastError().text() << '\n';
    }
}

void MainWindow::insertSession(QString type, int duration) {
    QSqlQuery query;
    qDebug() << type << ' ' << duration << '\n';
    QString queryStr = QString("INSERT INTO sessions (type, duration)"
                               "VALUES ('%1', %2);")
                           .arg(type)
                           .arg(duration);
    if (!query.exec(queryStr)) {
        qDebug() << "Error: can't insert: " << query.lastError().text() << '\n';
    }
}
