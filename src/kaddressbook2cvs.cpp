#include <QCoreApplication>
#include <QTimer>
#include <QStringList>

#include "Mem.h"
#include "kaddressbook2cvsWorker.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    
    Mem *mem=new Mem();

    QStringList arguments = app.arguments();

    if (arguments.size()==1) {
	 mem->showHelp(Apps::Kaddressbook2CVS);
         return 0;
     }

    WorkerCVS worker(arguments.at(1));
    QObject::connect(&worker, SIGNAL(done()), &app, SLOT(quit()));
    QTimer::singleShot(0, &worker, SLOT(run()));
    int ret=app.exec();
    delete mem;
    return ret;
}
