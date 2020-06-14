
VERSION=`cat src/CMakeLists.txt | grep -i "set (VERSION"| cut -f 2 -d'"'`

echo "New release procedure
=====================
1) Update version in src/CMakelists.txt
2) Update changelog in README.md
3) Ejecutar linguist
4) git commit -am kdepim2google-$VERSION
5) git push
6) Create a release in github with '$VERSION' as tag
7) Make a new ebuild with the new version
8) Upload the ebuild to myportage project
"