QT       -= gui

TEMPLATE = lib


TARGET      = MIPCpxSolver201
LIBS        += $$(CPLEX_HOME_LIB)/cplex2010.lib
INCLUDEPATH += $$(CPLEX_HOME)/include/ilcplex

LIBS        += $$(MIPMODELER_HOME)/lib/$$(OPTION)/MIPModeler.lib
INCLUDEPATH += $$(MIPMODELER_HOME)/MIPModelerCore/
INCLUDEPATH += $$(SOLVER_DEPS)/Eigen/3.2.9-modif/

DEFINES += MIPCPXSOLVER_LIBRARY

SOURCES += MIPCpxSolver.cpp \

HEADERS += MIPCpxSolver_global.h \
           MIPCpxSolver.h

DESTDIR  = $$(MIPMODELER_HOME)/lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT
