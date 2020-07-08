QT += testlib
QT += gui sql widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_validinput.cpp \
            ../../LungTrak/dbobj.cpp

