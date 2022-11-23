QT += testlib
QT += positioning
QT -= gui


CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

INCLUDEPATH += $$(SOLVER_DEPS)/Eigen/3.2.9-modif

LIBS        += ../../lib/$$(OPTION)/GAMSModeler39.lib
INCLUDEPATH += ../../GAMSModeler
INCLUDEPATH += $$(GAMS_HOME)/apifiles/C++/api


LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib
INCLUDEPATH += ../../MIPModelerCore

LIBS        += ../../lib/$$(OPTION)/MIPCpxSolver201.lib
INCLUDEPATH += ../../MIPSolverInterface/MIPCpxSolver
INCLUDEPATH += $$(CPLEX_HOME)/include/ilcplex

LIBS        += ../../lib/$$(OPTION)/MIPCbcSolver.lib
INCLUDEPATH += ../../MIPSolverInterface/MIPCbcSolver

LIBS        += ../../lib/$$(OPTION)/MIPClpSolver.lib
INCLUDEPATH += ../../MIPSolverInterface/MIPClpSolver

INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/
INCLUDEPATH += $$(COINOR_HOME)/CoinUtils/src/
INCLUDEPATH += $$(COINOR_HOME)/Osi/src/Osi/
INCLUDEPATH += $$(COINOR_HOME)/Cbc/src/
INCLUDEPATH += $$(COINOR_HOME)/Clp/src/OsiClp
INCLUDEPATH += $$(COINOR_HOME)/Clp/src/

SOURCES += tst_testTransport.cpp

DEFINES += EIGEN_MPL2_ONLY
DEFINES += USE_GAMS
