set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})
set (VERSION "0.1.1")
add_definitions(-DMYINSTALL_PREFIX=${CMAKE_INSTALL_PREFIX})
add_definitions(-DVERSION="${VERSION}")

# Qt4 package
find_package(Qt4 REQUIRED)
set(QT_DONT_USE_QTGUI TRUE)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
include_directories(${QT_INCLUDE_DIR})
set(LIBRARIES ${LIBRARIES} ${QT_LIBRARIES})


# Local files
set(HEADERS_KADDRESSBOOK2CVS kaddressbook2cvsWorker.h)
set(SOURCES_KADDRESSBOOK2CVS kaddressbook2cvs.cpp kaddressbook2cvsWorker.cpp )
set(HEADERS_KADDRESSBOOK2ICS kaddressbook2icsWorker.h)
set(SOURCES_KADDRESSBOOK2ICS kaddressbook2ics.cpp kaddressbook2icsWorker.cpp )
set(HEADERS_LIBRARY Contact.h Mem.h SetContacts.h)
set(SOURCES_LIBRARY Contact.cpp Mem.cpp SetContacts.cpp)

# I18n
SET(PROJECT_TRANSLATIONS ../i18n/kdepim2google_es.ts)
SET(FILES_TO_TRANSLATE ${HEADERS_KADDRESSBOOK2CVS} ${SOURCES_KADDRESSBOOK2CVS} ${HEADERS_KADDRESSBOOK2ICS} ${SOURCES_KADDRESSBOOK2ICS} ${HEADERS_LIBRARY} ${SOURCES_LIBRARY})
QT4_CREATE_TRANSLATION(QM_FILES ${FILES_TO_TRANSLATE} ${PROJECT_TRANSLATIONS})
ADD_CUSTOM_TARGET(TRANSLATIONS_TARGET DEPENDS ${QM_FILES})

# Create Qt MOC files
qt4_wrap_cpp(HEADERS_KADDRESSBOOK2CVS_MOC ${HEADERS_KADDRESSBOOK2CVS})
qt4_wrap_cpp(HEADERS_KADDRESSBOOK2ICS_MOC ${HEADERS_KADDRESSBOOK2ICS})
qt4_wrap_cpp(HEADERS_LIBRARY_MOC ${HEADERS_LIBRARY})

#Create library
ADD_LIBRARY(kdepim2google SHARED ${SOURCES_LIBRARY} ${HEADERS_LIBRARY_MOC})
SET_PROPERTY(TARGET kdepim2google PROPERTY SOVERSION ${VERSION})

# Create executable
add_executable(kaddressbook2cvs ${HEADERS_KADDRESSBOOK2CVS_MOC} ${SOURCES_KADDRESSBOOK2CVS} ${QM_FILES})
target_link_libraries(kaddressbook2cvs ${LIBRARIES} kdepim2google)
set_target_properties(kaddressbook2cvs PROPERTIES OUTPUT_NAME kaddressbook2cvs${BUILD_POSTFIX})

# Create executable
add_executable(kaddressbook2ics ${HEADERS_KADDRESSBOOK2ICS_MOC} ${SOURCES_KADDRESSBOOK2ICS} ${QM_FILES})
target_link_libraries(kaddressbook2ics ${LIBRARIES} kdepim2google)
set_target_properties(kaddressbook2ics PROPERTIES OUTPUT_NAME kaddressbook2ics${BUILD_POSTFIX})

# Create installation
INSTALL(TARGETS kaddressbook2cvs kaddressbook2ics DESTINATION bin)
INSTALL(TARGETS kdepim2google LIBRARY DESTINATION lib)
INSTALL(FILES ${HEADERS_LIBRARY} DESTINATION include/kdepim2google)
INSTALL(FILES ${QM_FILES} DESTINATION share/kdepim2google)
