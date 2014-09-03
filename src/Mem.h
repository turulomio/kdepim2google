#ifndef MEM_H
#define MEM_H

#include <QObject>
#include <QCoreApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QTextStream>

class Mem : public QObject
{
    Q_OBJECT

public:
    Mem();
    ~Mem();

private:
  QTranslator *translator;
  QTranslator *translatorQt;
  void loadQTranslator();
};

#endif // MEM_H
