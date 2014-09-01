#include <QObject>
#include "SetContacts.h"
class WorkerCVS : public QObject {
Q_OBJECT

public:
    WorkerCVS(QString path);
    QString path;
    SetContacts set;
signals:
    void done();
public slots:
    void run();
};
