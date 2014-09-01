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
    emit done();
    
}

