#include "Mem.h"

Mem::Mem()
{
  this->translator=new QTranslator();
  this->translatorQt=new QTranslator();
  this->loadQTranslator();
}

Mem::~Mem()
{
  delete this->translator;
  delete this->translatorQt;
}

void Mem::loadQTranslator()
{
    //Load QT
    this->translatorQt->load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(this->translatorQt);

    //Load APP
    if ( this->translator->load("kdepim2google_"+QLocale::system().name().left(2)+".qm")){
//         QTextStream(stdout) << "Loaded ./\n";
    }else{
      if ( this->translator->load("/usr/local/share/kdepim2google/kdepim2google_"+QLocale::system().name().left(2)+".qm")){
//         QTextStream(stdout) << "Loaded /usr/local\n";
      } else{
        if (this->translator->load("/usr/share/kdepim2google/kdepim2google_"+QLocale::system().name().left(2)+".qm")){
// 	  QTextStream(stdout) << "Loaded /usr/\n";
        } else {
// 	  QTextStream(stdout) << "Not loaded\n" ;
        }
      }
    }
    qApp->installTranslator(this->translator);
}

void Mem::showHelp(enum Apps app)
{
  QString s;
  QString version=tr("Version: %1").arg(QString(VERSION));
  QString hide=tr("You can add the string 'Hide birthday' to the contact in order to exclude the birthday from the generated file");
  switch(app){
    case Apps::Kaddressbook2CVS:
      s= tr("Usage: kaddressbook2cvs contacts_dir") + "\n" +
         "   " + version + "\n" +
	 "   " + tr("Create a cvs file to import in google calendar from kaddressbook birthdays") + "\n" +
	 "   " + tr("You must create/replace a new google calendar, then you have to import cvs file INTO IT") + "\n" +
	 "   " + tr("The program creates birthdays from today to 3 years.") + "\n" +
         "   " + hide + "\n" ;
      break;
    case Apps::Kaddressbook2ICS:
      s= tr("Usage: kaddressbook2ics contacts_dir") + "\n" +
         "   " + version + "\n" +
	 "   " + tr("Create a ics file to import in google calendar from kaddressbook birthdays") + "\n" +
	 "   " + tr("You must create/replace a new google calendar, then you have to import ics file INTO IT") + "\n"+
         "   " + hide + "\n" ;
      break;
  }
  QTextStream(stdout)  << s;
}

QString Mem::defaultContactDir(){
  QString home = QFile::decodeName(qgetenv("HOME"));
  if (home.isNull()) home = "/";
  return home+"/.local/share/contacts";
}
