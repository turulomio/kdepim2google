#include "kaddressbook2cvsWorker.h"

WorkerCVS::WorkerCVS(QString path): QObject()
{
  this->path=path;
}

/**
 * Iterates path and create set of contacts
 */
void WorkerCVS::run() {
    set.LoadFromPath(this->path);
    set.CreateCVS();
    set.print();
    QTextStream(stdout) << QString(tr("%1 from %2 contacts added to generated file")).arg(set.countShowBirthday()).arg(set.list.size()) << "\n";
    emit done();
    
}

