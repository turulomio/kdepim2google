#include <QCoreApplication>
#include <QTimer>
#include <QTextStream>
#include <QStringList>
#include <QTranslator>
#include <QLibraryInfo>

#include "kaddressbook2cvsWorker.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    QTranslator translator;
    if ( translator.load("kdepim2google_"+QLocale::system().name().left(2)+".qm")){
        QTextStream(stdout) << "Loaded ./\n";
    }else{
      if ( translator.load("/usr/local/share/kdepim2google/kdepim2google_"+QLocale::system().name().left(2)+".qm")){
        QTextStream(stdout) << "Loaded /usr/local\n";
      } else{
        if (translator.load("/usr/share/kdepim2google/kdepim2google_"+QLocale::system().name().left(2)+".qm")){
	  QTextStream(stdout) << "Loaded /usr/\n";
        } else {
	  QTextStream(stdout) << "Not loaded\n" ;
        }
      }
    }
    app.installTranslator(&translator);

    QStringList arguments = app.arguments();

    if (arguments.size()==1) {
         QTextStream(stdout) << QObject::tr("Usage: kaddressbook2cvs contacts_dir") << "\n" 
                    << "   " << QObject::tr("Version: ") << QString(VERSION) << "\n"
                    << "   " << QObject::tr("Create a cvs file to import in google calendar from kaddressbook birthdays") <<"\n"
                    << "   " << QObject::tr("You must create/replace a new calendar call kaddressbook, then you have to import cvs file INTO IT") <<"\n"
                    << "   " << QObject::tr("The program creates birthdays from today to 3 years.") <<"\n"
                    ;
         return 0;
     }

    WorkerCVS worker(arguments.at(1));
    QObject::connect(&worker, SIGNAL(done()), &app, SLOT(quit()));
    QTimer::singleShot(0, &worker, SLOT(run()));
    return app.exec();
}
