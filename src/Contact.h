
#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include <qdatetime.h>
#include <QTextStream>
#include <QFile>

class Contact : public QObject
{
    Q_OBJECT

public:
    Contact();
    ~Contact();
    QString name;
    QDate birthday;
    QString print();
    bool isValid();
    bool ParseFile(QString path);
    int age_in_birthday(int year);
    bool operator<(const Contact &a);


};
#endif // CONTACT_H
