QT       -= gui

TARGET = MIPClpSolver
TEMPLATE = lib

LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib
LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libCgl.lib
LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libClp.lib
LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libCoinUtils.lib
LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libOsi.lib
LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libOsiClp.lib

INCLUDEPATH += ../../core/
INCLUDEPATH += ../../external/Eigen/3.2.9/
INCLUDEPATH += ../../external/CoinOR/Cgl/src/
INCLUDEPATH += ../../external/CoinOR/CoinUtils/src/
INCLUDEPATH += ../../external/CoinOR/Osi/src/Osi
INCLUDEPATH += ../../external/CoinOR/Clp/src/OsiClp
INCLUDEPATH += ../../external/CoinOR/Clp/src/

DEFINES += MIPCLPSOLVER_LIBRARY

SOURCES += MIPClpSolver.cpp

HEADERS += MIPClpSolver.h \
           MIPClpSolver_global.h


DESTDIR     = ../../lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT

