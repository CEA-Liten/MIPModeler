QT       -= gui

TEMPLATE = lib

message("MIPMskSolver compilation using mosek 8.1: '$$(MOSEK_HOME_81)'"))
TARGET = MIPMskSolver81
LIBS        += $$(MOSEK_HOME_81_LIB)/mosek64_8_1.lib
INCLUDEPATH += $$(MOSEK_HOME_81)/h/

LIBS        += $$(PEGASE_MPC_HOME)/lib/MIPModeler.lib
INCLUDEPATH += $$(PEGASE_MPC_HOME)/src/MIPModeler/MIPModelerCore/include/
INCLUDEPATH += $$(DEPS_HOME)/External/Eigen/3.2.9-modif/

DEFINES += MIPMSKSOLVER_LIBRARY

SOURCES += MIPMskSolver.cpp

HEADERS += MIPMskSolver_global.h \
           MIPMskSolver.h

DESTDIR     = $$(PEGASE_MPC_HOME)/lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT

