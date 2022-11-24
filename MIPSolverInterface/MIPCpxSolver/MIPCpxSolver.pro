QT       -= gui

TEMPLATE = lib

TARGET      = MIPCpxSolver$$(CPLEX_LIB_VERSION)
LIBS        += $$(CPLEX_HOME_LIB)/cplex$$(CPLEX_LIB_VERSION).lib
INCLUDEPATH += $$(CPLEX_HOME)/include/ilcplex

LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib
INCLUDEPATH += ../../MIPModelerCore/
INCLUDEPATH += ../../External/Eigen/3.2.9/

DEFINES += MIPCPXSOLVER_LIBRARY

SOURCES += MIPCpxSolver.cpp \

HEADERS += MIPCpxSolver_global.h \
           MIPCpxSolver.h

DESTDIR  = ../../lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT

