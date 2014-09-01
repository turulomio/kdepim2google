#include <QCoreApplication>
#include <QTimer>
#include <QTextStream>
#include <QStringList>
#include <QTranslator>
#include <QLibraryInfo>

#include "kaddressbook2icsWorker.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    QTranslator translator;
    if ( translator.load("/usr/share/kdepim2google/kdepim2google_"+QLocale::system().name().left(2)+".qm")){
      QTextStream(stdout) << "Loaded /usr\n";
    } else{
      if (translator.load("/usr/local/share/kdepim2google/kdepim2google_"+QLocale::system().name().left(2)+".qm")){
	QTextStream(stdout) << "Loaded /usr/local\n";
      } else {
	QTextStream(stdout) << "Not loaded\n" ;
      }
    }    app.installTranslator(&translator);

    QStringList arguments = app.arguments();

    if (arguments.size()==1) {
         QTextStream(stdout) << QObject::tr("Usage: kaddressbook2ics contacts_dir") << "\n" 
                    << "   " << QObject::tr("Version: ") << VERSION << "\n"
                    << "   " << QObject::tr("Create a ics file to import in google calendar from kaddressbook birthdays") <<"\n"
                    << "   " << QObject::tr("You must create/replace a new calendar call kaddressbook, then you have to import ics file INTO IT") <<"\n"
                    ;
         return 0;
     }

    WorkerICS worker(arguments.at(1));
    QObject::connect(&worker, SIGNAL(done()), &app, SLOT(quit()));
    QTimer::singleShot(0, &worker, SLOT(run()));
    return app.exec();
}
