QT += testlib
QT += positioning
QT -= gui


CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

INCLUDEPATH += ../../External/Eigen/3.2.9

LIBS        += ../../lib/$$(OPTION)/GAMSModeler39.lib
INCLUDEPATH += ../../GAMSModeler
INCLUDEPATH += $$(GAMS_HOME)/apifiles/C++/api


LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib
INCLUDEPATH += ../../MIPModelerCore

LIBS        += ../../lib/$$(OPTION)/MIPCpxSolver2010.lib
INCLUDEPATH += ../../MIPSolverInterface/MIPCpxSolver
INCLUDEPATH += $$(CPLEX_HOME)/include/ilcplex

LIBS        += ../../lib/$$(OPTION)/MIPCbcSolver.lib
INCLUDEPATH += ../../MIPSolverInterface/MIPCbcSolver

LIBS        += ../../lib/$$(OPTION)/MIPClpSolver.lib
INCLUDEPATH += ../../MIPSolverInterface/MIPClpSolver

INCLUDEPATH += ../../External/CoinOR/Cgl/src/
INCLUDEPATH += ../../External/CoinOR/CoinUtils/src/
INCLUDEPATH += ../../External/CoinOR/Osi/src/Osi/
INCLUDEPATH += ../../External/CoinOR/Cbc/src/
INCLUDEPATH += ../../External/CoinOR/Clp/src/OsiClp
INCLUDEPATH += ../../External/CoinOR/Clp/src/

SOURCES += tst_testTransport.cpp

DEFINES += EIGEN_MPL2_ONLY
DEFINES += USE_GAMS
