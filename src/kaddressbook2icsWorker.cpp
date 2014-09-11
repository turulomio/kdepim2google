#include "kaddressbook2icsWorker.h"

WorkerICS::WorkerICS(QString path): QObject()
{
  this->path=path;
}

/**
 * Iterates path and create set of contacts
 */
void WorkerICS::run() {
    set.LoadFromPath(this->path);
    set.CreateICS();
    set.print();
    QTextStream(stdout) << QString(tr("%1 from %2 contacts added to generated file")).arg(set.countShowBirthday()).arg(set.list.size()) << "\n";
    emit done();
    
}

