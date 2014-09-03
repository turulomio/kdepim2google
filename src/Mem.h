#ifndef MEM_H
#define MEM_H

#include <QObject>
#include <QCoreApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QTextStream>
#include <QDir>


enum class Apps{ Kaddressbook2CVS, Kaddressbook2ICS};

class Mem : public QObject
{
    Q_OBJECT

public:
    Mem();
    ~Mem();
    void showHelp(enum Apps app);
    QString defaultContactDir();

private:
  QTranslator *translator;
  QTranslator *translatorQt;
  void loadQTranslator();
};

#endif // MEM_H
