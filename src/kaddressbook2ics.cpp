#include <QCoreApplication>
#include <QTimer>
#include <QStringList>

#include "Mem.h"
#include "kaddressbook2icsWorker.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    
    Mem *mem=new Mem();

    QString path;//path to look for
    QStringList arguments = app.arguments();
 QTextStream(stdout) << mem->defaultContactDir();
    if (arguments.size()==1) {
      mem->showHelp(Apps::Kaddressbook2ICS);
      return 0;
    } else {
      path=arguments.at(1);
    }

    WorkerICS worker(path);
    QObject::connect(&worker, SIGNAL(done()), &app, SLOT(quit()));
    QTimer::singleShot(0, &worker, SLOT(run()));
    int ret=app.exec();
    delete mem;
    return ret;
}


