QT       -= gui

TARGET = MIPClpSolver
TEMPLATE = lib

LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib
LIBS        += $$(COINOR_HOME)/lib/libCgl.lib
LIBS        += $$(COINOR_HOME)/lib/libClp.lib
LIBS        += $$(COINOR_HOME)/lib/libCoinUtils.lib
LIBS        += $$(COINOR_HOME)/lib/libOsi.lib
LIBS        += $$(COINOR_HOME)/lib/libOsiClp.lib

INCLUDEPATH += ../../MIPModelerCore/
INCLUDEPATH += $$(SOLVER_DEPS)/Eigen/3.2.9-modif/
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/
INCLUDEPATH += $$(COINOR_HOME)/CoinUtils/src/
INCLUDEPATH += $$(COINOR_HOME)/Osi/src/Osi
INCLUDEPATH += $$(COINOR_HOME)/Clp/src/OsiClp
INCLUDEPATH += $$(COINOR_HOME)/Clp/src/

DEFINES += MIPCLPSOLVER_LIBRARY

SOURCES += MIPClpSolver.cpp

HEADERS += MIPClpSolver.h \
           MIPClpSolver_global.h


DESTDIR     = ../../lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT

