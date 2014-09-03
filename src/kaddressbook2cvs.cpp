#include <QCoreApplication>
#include <QTimer>
#include <QTextStream>
#include <QStringList>

#include "Mem.h"
#include "kaddressbook2cvsWorker.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    
    Mem *mem=new Mem();

    QStringList arguments = app.arguments();

    if (arguments.size()==1) {
         QTextStream(stdout) << QObject::tr("Usage: kaddressbook2cvs contacts_dir") << "\n" 
                    << "   " << QObject::tr("Version: ") << QString(VERSION) << "\n"
                    << "   " << QObject::tr("Create a cvs file to import in google calendar from kaddressbook birthdays") <<"\n"
                    << "   " << QObject::tr("You must create/replace a new calendar called kaddressbook, then you have to import cvs file INTO IT") <<"\n"
                    << "   " << QObject::tr("The program creates birthdays from today to 3 years.") <<"\n"
                    ;
         return 0;
     }

    WorkerCVS worker(arguments.at(1));
    QObject::connect(&worker, SIGNAL(done()), &app, SLOT(quit()));
    QTimer::singleShot(0, &worker, SLOT(run()));
    int ret=app.exec();
    delete mem;
    return ret;
}
