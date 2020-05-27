QT       -= gui

TARGET = MIPClpSolver
TEMPLATE = lib

LIBS        += $$(PEGASE_MPC_HOME)/lib/MIPModeler.lib
LIBS        += $$(COINOR_HOME)/lib/libCgl.lib
LIBS        += $$(COINOR_HOME)/lib/libClp.lib
LIBS        += $$(COINOR_HOME)/lib/libCoinUtils.lib
LIBS        += $$(COINOR_HOME)/lib/libOsi.lib
LIBS        += $$(COINOR_HOME)/lib/libOsiClp.lib

INCLUDEPATH += $$(PEGASE_MPC_HOME)/src/MIPModeler/MIPModelerCore/include/
INCLUDEPATH += $$(DEPS_HOME)/External/Eigen/3.2.9-modif/
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/
INCLUDEPATH += $$(COINOR_HOME)/CoinUtils/src/
INCLUDEPATH += $$(COINOR_HOME)/Osi/src/Osi
INCLUDEPATH += $$(COINOR_HOME)/Clp/src/OsiClp
INCLUDEPATH += $$(COINOR_HOME)/Clp/src/

DEFINES += MIPCLPSOLVER_LIBRARY

SOURCES += MIPClpSolver.cpp

HEADERS += MIPClpSolver.h \
           MIPClpSolver_global.h


DESTDIR     = $$(PEGASE_MPC_HOME)/lib

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT
