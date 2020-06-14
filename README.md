# kdepim2google

## Dependencies

You need QtCore from qt libraries


## Installation

1) Uncompress the source and change to the first directory with CMakeList.txt
1) Run `mkdir build`
1) Run `cd build`
1) Run `cmake ..`
1) Run `make; make install`

## Changelog

### 0.6.0
- Project has been migrated to Qt5.
- Added cmake uninstall command.
- Added comand line argument parser.
- First release in Github.

### 0.5.0
- Contact name is searched in N: too

### 0.4.0
- Fixed bad spanish translations

### 0.3.0
- Fixed contact counters.
- Improved search of 'Hide birthday' string in contact.
- Improved help instructions.

### 0.2.0
- Added default directory.
- Hide birthdays when a string 'Hide birthday' is set in the contact.

### 0.1.1
- Added shared libraries.
- Added uninstall bash script.

### 0.1.0
- Extracts birthdays from kaddressbook to ics and vcs files to import in Google Calendar.

