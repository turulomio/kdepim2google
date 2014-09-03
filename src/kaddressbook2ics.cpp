#include <QCoreApplication>
#include <QTimer>
#include <QTextStream>
#include <QStringList>

#include "Mem.h"
#include "kaddressbook2icsWorker.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    
    Mem *mem=new Mem();


    QStringList arguments = app.arguments();

    if (arguments.size()==1) {
         QTextStream(stdout) << QObject::tr("Usage: kaddressbook2ics contacts_dir") << "\n" 
                    << "   " << QObject::tr("Version: ") << QString (VERSION) << "\n"
                    << "   " << QObject::tr("Create a ics file to import in google calendar from kaddressbook birthdays") <<"\n"
                    << "   " << QObject::tr("You must create/replace a new calendar called kaddressbook, then you have to import ics file INTO IT") <<"\n"
                    ;
         return 0;
     }

    WorkerICS worker(arguments.at(1));
    QObject::connect(&worker, SIGNAL(done()), &app, SLOT(quit()));
    QTimer::singleShot(0, &worker, SLOT(run()));
    int ret=app.exec();
    delete mem;
    return ret;
}


