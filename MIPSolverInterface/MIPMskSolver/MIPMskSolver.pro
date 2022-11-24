QT       -= gui

TEMPLATE = lib

TARGET      = MIPMskSolver$$(MOSEK_LIB_VERSION)
LIBS        += $$(MOSEK_HOME_LIB)/mosek64$$(MOSEK_LIB_VERSION).lib
INCLUDEPATH += $$(MOSEK_HOME)/h/

LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib
INCLUDEPATH += ../../MIPModelerCore/
INCLUDEPATH += ../../External/Eigen/3.2.9/

DEFINES += MIPMSKSOLVER_LIBRARY

SOURCES += MIPMskSolver.cpp

HEADERS += MIPMskSolver_global.h \
           MIPMskSolver.h

DESTDIR     = ../../lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT

