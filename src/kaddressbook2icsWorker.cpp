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
    emit done();
    
}

