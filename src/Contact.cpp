#include "Contact.h"

Contact::Contact()
{
  this->showBirthday=true;
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
  QString showed;
  if (this->showBirthday==true){
    showed=QString("");
  } else{
    showed=QString("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< (%1)").arg(tr("Not showed"));
  }
  return QString("+ ")+ QString(tr("%1 was borned in %2 %3")).arg(this->name).arg(this->birthday.toString("yyyy-MM-dd")).arg(showed);
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
    QString all= line;
    while (!line.isNull()) {     
	 //Gets name
         if (line.startsWith("FN:", Qt::CaseSensitive)){
	   this->name=line.replace("FN:","");
	 }
	 if (this->name.isNull()){
	   if (line.startsWith("N:", Qt::CaseSensitive)){
	     this->name=line.replace("N:","");
	   }
	 }
	 if (this->name.isNull()){
	   if (line.startsWith("NAME:", Qt::CaseSensitive)){
	     this->name=line.replace("NAME:","");
	   }
	 }
	 //Gets birthday
         if (line.startsWith("BDAY:", Qt::CaseSensitive)){
	   if (QDate::fromString(line.replace("BDAY:","").left(10),"yyyy-MM-dd").isValid()){
	     this->birthday=QDate::fromString(line.replace("BDAY:","").left(10),"yyyy-MM-dd");
	   }
	 }
	 line=in.readLine();
	 all=all+line;
    }
    //Gets showBirthday. We must replace " " due to in ics file make end of line " "
    QString search=tr("Hide birthday");
    search=search.replace(" ","");
    all=all.replace(" ","");
    if (all.contains(search,Qt::CaseInsensitive)==true){
        this->showBirthday=false;
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