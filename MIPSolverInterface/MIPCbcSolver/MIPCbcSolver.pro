QT       -= gui

TARGET = MIPCbcSolver
TEMPLATE = lib

LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib
LIBS        += ../../External/CoinOR/lib/$$(OPTION)/libCbc.lib
LIBS        += ../../External/CoinOR/lib/$$(OPTION)/libCbcSolver.lib
LIBS        += ../../External/CoinOR/lib/$$(OPTION)/libCgl.lib
LIBS        += ../../External/CoinOR/lib/$$(OPTION)/libClp.lib
LIBS        += ../../External/CoinOR/lib/$$(OPTION)/libCoinUtils.lib
LIBS        += ../../External/CoinOR/lib/$$(OPTION)/libOsi.lib
LIBS        += ../../External/CoinOR/lib/$$(OPTION)/libOsiCbc.lib
LIBS        += ../../External/CoinOR/lib/$$(OPTION)/libOsiClp.lib

INCLUDEPATH += ../../MIPModelerCore/
INCLUDEPATH += ../../External/Eigen/3.2.9/
INCLUDEPATH += ../../External/CoinOR/Cgl/src/
INCLUDEPATH += ../../External/CoinOR/CoinUtils/src/
INCLUDEPATH += ../../External/CoinOR/Osi/src/Osi/
INCLUDEPATH += ../../External/CoinOR/Cbc/src/
INCLUDEPATH += ../../External/CoinOR/Clp/src/OsiClp
INCLUDEPATH += ../../External/CoinOR/Clp/src/

DEFINES += MIPCBCSOLVER_LIBRARY

SOURCES += MIPCbcSolver.cpp

HEADERS += MIPCbcSolver.h \
           MIPCbcSolver_global.h

DESTDIR     = ../../lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT


