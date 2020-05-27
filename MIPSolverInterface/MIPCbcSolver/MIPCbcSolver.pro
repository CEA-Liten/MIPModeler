#-------------------------------------------------
#
# Project created by QtCreator 2016-09-13T09:54:02
#
#-------------------------------------------------

QT       -= gui

TARGET = MIPCbcSolver
TEMPLATE = lib

message("MIPCbcSolver compilation using coinor 0.107: '$$(COINOR_HOME)'")

LIBS        += $$(PEGASE_MPC_HOME)/lib/MIPModeler.lib
LIBS        += $$(COINOR_HOME)/lib/libCbc.lib
LIBS        += $$(COINOR_HOME)/lib/libCbcSolver.lib
LIBS        += $$(COINOR_HOME)/lib/libCgl.lib
LIBS        += $$(COINOR_HOME)/lib/libClp.lib
LIBS        += $$(COINOR_HOME)/lib/libCoinUtils.lib
LIBS        += $$(COINOR_HOME)/lib/libOsi.lib
LIBS        += $$(COINOR_HOME)/lib/libOsiCbc.lib
LIBS        += $$(COINOR_HOME)/lib/libOsiClp.lib

INCLUDEPATH += $$(PEGASE_MPC_HOME)/src/MIPModeler/MIPModelerCore/include/
INCLUDEPATH += $$(DEPS_HOME)/External/Eigen/3.2.9-modif/
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/
INCLUDEPATH += $$(COINOR_HOME)/CoinUtils/src/
INCLUDEPATH += $$(COINOR_HOME)/Osi/src/Osi/
INCLUDEPATH += $$(COINOR_HOME)/Cbc/src/
INCLUDEPATH += $$(COINOR_HOME)/Clp/src/OsiClp
INCLUDEPATH += $$(COINOR_HOME)/Clp/src/

DEFINES += MIPCBCSOLVER_LIBRARY

SOURCES += MIPCbcSolver.cpp

HEADERS += MIPCbcSolver.h \
           MIPCbcSolver_global.h

DESTDIR     = $$(PEGASE_MPC_HOME)/lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT

