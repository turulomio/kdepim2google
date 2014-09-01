#include "Contact.h"

Contact::Contact()
{
}

Contact::~Contact()
{
}

bool Contact::operator<(const Contact &a) {
//   bool bu=this->name<a.name;
//     QTextStream(stdout) << "Comparing " << this->name << " Vs " << a.name<< ": " <<bu << "\n";  
        return this->name < a.name;
}

QString Contact::print()
{
  return QString("+ ")+ QString(tr("%1 was borned in %2")).arg(this->name).arg(this->birthday.toString("yyyy-MM-dd"));
}

bool Contact::isValid()
{
  if (!this->birthday.isNull() and !this->name.isNull()){
    return true;
  }
  return false;
}


bool Contact::ParseFile(QString filepath){
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull()) {     
         if (line.startsWith("FN:", Qt::CaseSensitive)){
	   this->name=line.replace("FN:","");
	 }
	 if (this->name.isNull()){
	   if (line.startsWith("NAME:", Qt::CaseSensitive)){
	     this->name=line.replace("NAME:","");
	   }
	 }
         if (line.startsWith("BDAY:", Qt::CaseInsensitive)){
	   if (QDate::fromString(line.replace("BDAY:","").left(10),"yyyy-MM-dd").isValid()){
	     this->birthday=QDate::fromString(line.replace("BDAY:","").left(10),"yyyy-MM-dd");
	   }
	 }
	
      line = in.readLine();
    }
    return this->isValid();
}


/**
 * Gives the age of the contact in the parameter date
 */
int Contact::age_in_birthday(int year)
{
  return year-this->birthday.year();
  
}