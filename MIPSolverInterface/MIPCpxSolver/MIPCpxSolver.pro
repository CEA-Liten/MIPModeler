QT       -= gui

TEMPLATE = lib

#message("MIPCpxSolver compilation using cplex 12.8: '$$(CPLEX_HOME_128)'")
#TARGET = MIPCpxSolver
#LIBS        += $$(CPLEX_HOME_128_LIB)/cplex1280.lib
#INCLUDEPATH += $$(CPLEX_HOME_128)/include/ilcplex

message("MIPCpxSolver compilation using cplex 12.9: '$$(CPLEX_HOME_129)'")
TARGET = MIPCpxSolver1290
LIBS        += $$(CPLEX_HOME_129_LIB)/cplex1290.lib
INCLUDEPATH += $$(CPLEX_HOME_129)/include/ilcplex

# message("MIPCpxSolver compilation using cplex 12.10: '$$(CPLEX_HOME_1210)'")
# TARGET = MIPCpxSolver12100
# LIBS        += $$(CPLEX_HOME_1210_LIB)/cplex12100.lib
# INCLUDEPATH += $$(CPLEX_HOME_1210)/include/ilcplex

LIBS        += $$(PEGASE_MPC_HOME)/lib/$$(OPTION)/MIPModeler.lib
INCLUDEPATH += $$(PEGASE_MPC_HOME)/MIPModelerCore/include/
INCLUDEPATH += $$(SOLVER_DEPS)/Eigen/3.2.9-modif/

DEFINES += MIPCPXSOLVER_LIBRARY

SOURCES += MIPCpxSolver.cpp \

HEADERS += MIPCpxSolver_global.h \
           MIPCpxSolver.h

DESTDIR  = $$(PEGASE_MPC_HOME)/lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT
