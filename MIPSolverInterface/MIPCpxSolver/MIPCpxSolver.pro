QT       -= gui

TEMPLATE = lib

TARGET      = MIPCpxSolver201
LIBS        += $$(CPLEX_HOME_LIB)/cplex2010.lib
INCLUDEPATH += $$(CPLEX_HOME)/include/ilcplex

LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib
INCLUDEPATH += ../../MIPModelerCore/
INCLUDEPATH += $$(SOLVER_DEPS)/Eigen/3.2.9-modif/

DEFINES += MIPCPXSOLVER_LIBRARY

SOURCES += MIPCpxSolver.cpp \

HEADERS += MIPCpxSolver_global.h \
           MIPCpxSolver.h

DESTDIR  = ../../lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT

