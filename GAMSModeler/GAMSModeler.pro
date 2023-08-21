QT       -= gui
TARGET    = GAMSModeler39
TEMPLATE  = lib

_GAMS_HOME=$$(GAMS_HOME)

!isEmpty(_GAMS_HOME) {
LIBS        += $$(GAMS_HOME)/apifiles/C++/lib/vs2019/gamscpp.lib
INCLUDEPATH += $$(GAMS_HOME)/apifiles/C++/api
INCLUDEPATH += ../ModelerInterface

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
}

DESTDIR     =  ../lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT
