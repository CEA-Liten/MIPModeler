QT       -= gui

TEMPLATE = lib

#message("MIPCpxSolver compilation using cplex 12.9: '$$(CPLEX_HOME)'")
#TARGET = MIPCpxSolver1290
#LIBS        += $$(CPLEX_HOME_LIB)/cplex1290.lib
#INCLUDEPATH += $$(CPLEX_HOME)/include/ilcplex

message("MIPCpxSolver compilation using cplex 20.1: '$$(CPLEX_HOME)'")
TARGET = MIPCpxSolver201
LIBS        += $$(CPLEX_HOME_LIB)/cplex2010.lib
INCLUDEPATH += $$(CPLEX_HOME)/include/ilcplex

LIBS        += $$(PEGASE_MPC_HOME)/lib/$$(OPTION)/MIPModeler.lib
INCLUDEPATH += $$(PEGASE_MPC_HOME)/MIPModelerCore/include/
INCLUDEPATH += $$(SOLVER_DEPS)/Eigen/3.2.9-modif/

DEFINES += MIPCPXSOLVER_LIBRARY

SOURCES += MIPCpxSolver.cpp \

HEADERS += MIPCpxSolver_global.h \
           MIPCpxSolver.h

DESTDIR  = $$(PEGASE_MPC_HOME)/lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT
