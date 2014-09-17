#include "SetContacts.h"

SetContacts::SetContacts()
{
}

SetContacts::~SetContacts()
{
}

void SetContacts::LoadFromPath(QString dirpath)
{
    QDir dir(dirpath);
    dir.setFilter(QDir::Files);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        Contact *c=new Contact();
        QFileInfo fileInfo = list.at(i);
	c->ParseFile(dirpath+ "/" +fileInfo.fileName());
	if (c->isValid()){
	  this->list.append(c);
	}
    }
}

void SetContacts::CreateCVS(){
  QFile file("kaddressbook.cvs");
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream out(&file);
  out << "Subject,Start Date,End Date,All Day Event,Description\n";
  foreach(Contact *c, this->list){
    if (c->showBirthday==false){
      continue;
    }
    for (int year=QDate::currentDate().year();year<=QDate::currentDate().year()+3;year++){
      if (QDate(year,c->birthday.month(),c->birthday.day())>=QDate::currentDate()) {
	out << tr("Birthday of %1,%2-%3-%4,%2-%3-%4,True,Age of %5\n").arg(c->name).arg(year).arg(c->birthday.month()).arg(c->birthday.day()).arg(c->age_in_birthday(year));
      }
    }
  }
  out << QString("kaddressbook2google insert the last birthday. Please run the program again,%1-12-31,%1-12-31,True,Replace it\n").arg(QDate::currentDate().year()+3);
  file.close(); 

}

void SetContacts::CreateICS(){
  QFile file("kaddressbook.ics");
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream out(&file);
  out << "BEGIN:VCALENDAR\n";
  out << "VERSION:2.0\n";
  out << "X-WR-CALNAME:Kaddressbook birthdays\n";
  out << "X-WR-TIMEZONE:Europe/Madrid\n";
  out << "CALSCALE:GREGORIAN\n";
  out << "METHOD:PUBLISH\n";

  foreach(Contact *c, this->list){
    if (c->showBirthday==false){
      continue;
    }
    //out << QString(tr("Birthday of %1,%2-%3-%4,%2-%3-%4,True,Age of %5\n")).arg(c->name).arg(year).arg(c->birthday.month()).arg(c->birthday.day()).arg(c->age_in_birthday(year));
    QString date=c->birthday.toString("yyyyMMdd");
    out << "BEGIN:VEVENT\n";
    out << "DTSTART;VALUE=DATE:"<< date <<"\n";
    out << "DTEND;VALUE=DATE:"<< date <<"\n";
    out << "SUMMARY:" << tr("Birthday of %1").arg(c->name) << "\n";
    out << "RRULE:FREQ=YEARLY;INTERVAL=1\n";
    out << "END:VEVENT\n";
  }
  out << "END:VCALENDAR\n";
  file.close(); 

}



/*
 * Both are used to sort, function is used due to sorts pointers
 * LogEvent event1, event2;
LogEvent *eventptr1=&event1,*eventptr2=&event2;
event1<event2; // Operator not defined in your code
event1<eventptr2; // This will call the operator you have defined
eventptr1<eventptr2; // This will compare the pointers themselves, not the LogEv
 */
template<class T>
bool dereferencedLessThan(T * o1, T * o2) {
    return *o1 < *o2;
}
void SetContacts::sort()
{
  qSort(this->list.begin(), this->list.end(), dereferencedLessThan<Contact>);
}




void SetContacts::print(){
  this->sort();
  foreach(Contact *c, this->list){
    QTextStream(stdout)<< c->print() <<"\n";
  }
}

/**
 * Sum contacts that can show birthday
 */
int SetContacts::countShowBirthday()
{
  int i=0;
  foreach(Contact *c, this->list){
    if (c->showBirthday==true){
      i++;
    }
  }
  return i;

}

