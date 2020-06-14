#include <QCoreApplication>
#include <QCommandLineParser>
#include <QTimer>
#include <QStringList>


#include "Mem.h"
#include "kaddressbook2icsWorker.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    app.setApplicationName("kaddressbook2ics");
    app.setApplicationVersion(VERSION);

    QCommandLineParser parser;

    QString s = QCoreApplication::translate("main", "Converts kaddressbook contact important dates to a 'ics' calendar file") + "\n" +
         "   " + QCoreApplication::translate("main", "Then, you must create/replace a new google calendar, where you'll import ics file into it.") + "\n" +
         "   " + QCoreApplication::translate("main", "The program creates birthdays from today to 3 years.") + "\n" +
         "   " + QCoreApplication::translate("main", "You can add the string 'Hide birthday' to the contact in order to exclude the birthday from the generated file") + "\n" ;

    parser.setApplicationDescription(s);
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("directory", QCoreApplication::translate("main", "Contacts directory."));
    parser.process(app);

    Mem *mem=new Mem();

    QString path;//path to look for

    const QStringList args = parser.positionalArguments();
    if (args.length()==0) {
      path=mem->defaultContactDir();
      QTextStream(stdout) << QCoreApplication::translate("main", "Path not especified. Using default: %1").arg(path) <<"\n";
    } else {
      path=args.at(0);
    }

    WorkerICS worker(path);
    QObject::connect(&worker, SIGNAL(done()), &app, SLOT(quit()));
    QTimer::singleShot(0, &worker, SLOT(run()));
    int ret=app.exec();
    delete mem;
    return ret;
}


