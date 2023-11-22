QT       -= gui

TEMPLATE = lib

TARGET      =  MIPMskSolver$$(MOSEK_VERSION)
LIBS        += $$(MOSEK_HOME_LIB)/mosek64$$(MOSEK_VERSION).lib
INCLUDEPATH += $$(MOSEK_HOME)/h/

LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib
INCLUDEPATH += ../../core/
INCLUDEPATH += ../../external/Eigen/3.2.9/

DEFINES += MIPMSKSOLVER_LIBRARY

SOURCES += MIPMskSolver.cpp

HEADERS += MIPMskSolver_global.h \
           MIPMskSolver.h

DESTDIR     = ../../lib/$$(OPTION)

win32 {
    QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT
}


