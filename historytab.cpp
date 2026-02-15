#include "historytab.h"
#include <QListView>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlQuery>

HistoryTab::HistoryTab(QWidget *parent) {
    auto list = new QListView(this);
    model = new QSqlTableModel(this);
    model->setTable("sessions");
    model->select();
    model->setHeaderData(2, Qt::Horizontal, "Duration");
    model->setHeaderData(3, Qt::Horizontal, "Start");

    auto view = new QTableView(this);
    view->setModel(model);
    view->resize(720, 720);
    view->hideColumn(0);
    view->hideColumn(1);
    view->show();
}

void HistoryTab::refreshDB() {
    model->select();
}
