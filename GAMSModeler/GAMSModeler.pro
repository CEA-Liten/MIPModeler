QT       -= gui
TARGET    = GAMSModeler39
TEMPLATE  = lib

LIBS        += $$(GAMS_HOME)/apifiles/C++/lib/vs2019/gamscpp.lib
INCLUDEPATH += $$(GAMS_HOME)/apifiles/C++/api

DEFINES += GAMSMODELER_LIBRARY

HEADERS += GAMSModeler_global.h \
           GAMSData.h \
           GAMSDataSet.h \
           GAMSDataScalar.h \
           GAMSDataParam1D.h \
           GAMSDataParam2D.h \
           GAMSDataParam3D.h \
           GAMSModel.h \
           GAMSModeler.h
		   
SOURCES += GAMSData.cpp \
           GAMSDataSet.cpp \
           GAMSDataScalar.cpp \
           GAMSDataParam1D.cpp \
           GAMSDataParam2D.cpp \
           GAMSDataParam3D.cpp \
           GAMSModel.cpp \
           GAMSModeler.cpp

DESTDIR     =  ../lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT
