/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2014  Mariano Muñoz <mmmarquinez@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
        QTextStream(stdout) << "Loaded ./\n";
    }else{
      if ( this->translator->load("/usr/local/share/kdepim2google/kdepim2google_"+QLocale::system().name().left(2)+".qm")){
        QTextStream(stdout) << "Loaded /usr/local\n";
      } else{
        if (this->translator->load("/usr/share/kdepim2google/kdepim2google_"+QLocale::system().name().left(2)+".qm")){
	  QTextStream(stdout) << "Loaded /usr/\n";
        } else {
	  QTextStream(stdout) << "Not loaded\n" ;
        }
      }
    }
    qApp->installTranslator(this->translator);
}
