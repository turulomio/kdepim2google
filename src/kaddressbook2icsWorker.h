#include <QObject>
#include "SetContacts.h"
class WorkerICS : public QObject {
Q_OBJECT

public:
    WorkerICS(QString path);
    QString path;
    SetContacts set;
signals:
    void done();
public slots:
    void run();
};
