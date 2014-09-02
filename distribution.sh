#!/bin/bash
VERSION=`cat src/CMakeLists.txt | grep '(VERSION '| cut --delimiter='"'  -f 2`
CWD=`pwd`
cd ..
a=kdepim2google
tar cvz  -f $a/kdepim2google-src-$VERSION.tar.gz $a/AUTHORS.txt $a/CHANGELOG.txt $a/CMakeLists.txt $a/RELEASES.txt $a/INSTALL.txt $a/GPL-3.txt $a/uninstall.sh $a/src/* $a/i18n/*.ts -C `pwd`
cd $CWD
