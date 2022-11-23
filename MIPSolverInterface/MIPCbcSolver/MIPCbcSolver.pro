#-------------------------------------------------
#
# Project created by QtCreator 2016-09-13T09:54:02
#
#-------------------------------------------------

QT       -= gui

TARGET = MIPCbcSolver
TEMPLATE = lib

LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libCbc.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libCbcSolver.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libCgl.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libClp.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libCoinUtils.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libOsi.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libOsiCbc.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libOsiClp.lib

INCLUDEPATH += ../../MIPModelerCore/
INCLUDEPATH += $$(SOLVER_DEPS)/Eigen/3.2.9-modif/
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

DESTDIR     = ../../lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT


