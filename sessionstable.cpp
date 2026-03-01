#include "sessionstable.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

SessionsTable::SessionsTable() {}

void SessionsTable::initDatabase() {
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

void SessionsTable::createTable() {
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

void SessionsTable::insertSession(QString type, int duration) {
    QSqlQuery query;
    QString queryStr = QString("INSERT INTO sessions (type, duration)"
                               "VALUES ('%1', %2);")
                           .arg(type)
                           .arg(duration);
    if (!query.exec(queryStr)) {
        qDebug() << "Error: can't insert: " << query.lastError().text() << '\n';
    }
}
