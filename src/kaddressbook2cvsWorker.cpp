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
    QTextStream(stdout) << QString(tr("%1 contacts in generated file\n")).arg(set.list.count()) << "\n";
    emit done();
    
}

