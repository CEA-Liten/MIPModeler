QT       -= gui

TARGET = MIPClpSolver
TEMPLATE = lib

LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib
LIBS        += ../../External/CoinOR/lib/$$(OPTION)/libCgl.lib
LIBS        += ../../External/CoinOR/lib/$$(OPTION)/libClp.lib
LIBS        += ../../External/CoinOR/lib/$$(OPTION)/libCoinUtils.lib
LIBS        += ../../External/CoinOR/lib/$$(OPTION)/libOsi.lib
LIBS        += ../../External/CoinOR/lib/$$(OPTION)/libOsiClp.lib

INCLUDEPATH += ../../MIPModelerCore/
INCLUDEPATH += ../../External/Eigen/3.2.9/
INCLUDEPATH += ../../External/CoinOR/Cgl/src/
INCLUDEPATH += ../../External/CoinOR/CoinUtils/src/
INCLUDEPATH += ../../External/CoinOR/Osi/src/Osi
INCLUDEPATH += ../../External/CoinOR/Clp/src/OsiClp
INCLUDEPATH += ../../External/CoinOR/Clp/src/

DEFINES += MIPCLPSOLVER_LIBRARY

SOURCES += MIPClpSolver.cpp

HEADERS += MIPClpSolver.h \
           MIPClpSolver_global.h


DESTDIR     = ../../lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT

