#ifndef SESSIONSTABLE_H
#define SESSIONSTABLE_H
#include <QWidget>

class SessionsTable
{
public:
    SessionsTable();
    void initDatabase();
    void createTable();
    void insertSession(QString, int);
};

#endif // SESSIONSTABLE_H
