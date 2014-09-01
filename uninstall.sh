#!/bin/bash
DESTDIR=/usr/local
echo $DESTDIR
rm $DESTDIR/bin/kaddressbook2cvs $DESTDIR/bin/kaddressbook2ics
rm -Rf $DESTDIR/include/kdepim2google/
rm $DESTDIR/lib/libkdepim2google*
rm -Rf $DESTDIR/share/kdepim2google/
