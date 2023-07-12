QT       -= gui

TARGET = MIPCbcSolver
TEMPLATE = lib

LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib
LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libCbc.lib
LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libCbcSolver.lib
LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libCgl.lib
LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libClp.lib
LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libCoinUtils.lib
LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libOsi.lib
LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libOsiCbc.lib
LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libOsiClp.lib

INCLUDEPATH += ../../core/
INCLUDEPATH += ../../external/Eigen/3.2.9/
INCLUDEPATH += ../../external/CoinOR/Cgl/src/
INCLUDEPATH += ../../external/CoinOR/CoinUtils/src/
INCLUDEPATH += ../../external/CoinOR/Osi/src/Osi/
INCLUDEPATH += ../../external/CoinOR/Cbc/src/
INCLUDEPATH += ../../external/CoinOR/Clp/src/OsiClp
INCLUDEPATH += ../../external/CoinOR/Clp/src/
INCLUDEPATH += ../MIPSolver

DEFINES += MIPCBCSOLVER_LIBRARY

SOURCES += MIPCbcSolver.cpp

HEADERS += MIPCbcSolver.h \
           MIPCbcSolver_global.h

DESTDIR     = ../../lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT


