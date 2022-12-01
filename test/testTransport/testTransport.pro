QT += testlib
QT += positioning
QT -= gui


CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

INCLUDEPATH += ../../external/Eigen/3.2.9

LIBS        += ../../lib/$$(OPTION)/GAMSModeler39.lib
INCLUDEPATH += ../../GAMSModeler
INCLUDEPATH += $$(GAMS_HOME)/apifiles/C++/api


LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib
INCLUDEPATH += ../../core

LIBS        += ../../lib/$$(OPTION)/MIPCpxSolver2010.lib
INCLUDEPATH += ../../MIPSolverInterface/MIPCpxSolver
INCLUDEPATH += $$(CPLEX_HOME)/include/ilcplex

LIBS        += ../../lib/$$(OPTION)/MIPCbcSolver.lib
INCLUDEPATH += ../../MIPSolverInterface/MIPCbcSolver

LIBS        += ../../lib/$$(OPTION)/MIPClpSolver.lib
INCLUDEPATH += ../../MIPSolverInterface/MIPClpSolver

INCLUDEPATH += ../../external/CoinOR/Cgl/src/
INCLUDEPATH += ../../external/CoinOR/CoinUtils/src/
INCLUDEPATH += ../../external/CoinOR/Osi/src/Osi/
INCLUDEPATH += ../../external/CoinOR/Cbc/src/
INCLUDEPATH += ../../external/CoinOR/Clp/src/OsiClp
INCLUDEPATH += ../../external/CoinOR/Clp/src/

SOURCES += tst_testTransport.cpp

DEFINES += EIGEN_MPL2_ONLY
DEFINES += USE_GAMS
