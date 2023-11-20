QT       -= gui

TARGET = MIPClpSolver
TEMPLATE = lib

win32 {
    LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libCgl.lib
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libClp.lib
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libCoinUtils.lib
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libOsi.lib
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libOsiClp.lib
}
unix {
    LIBS        += ../../lib/$$(OPTION)/libMIPModeler.so
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/liblibCgl.so
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/liblibClp.so
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/liblibCoinUtils.so
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/liblibOsi.so
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/liblibOsiClp.so
}

INCLUDEPATH += ../../core/
INCLUDEPATH += ../../external/Eigen/3.2.9/
INCLUDEPATH += ../../external/CoinOR/Cgl/src/
INCLUDEPATH += ../../external/CoinOR/CoinUtils/src/
INCLUDEPATH += ../../external/CoinOR/Osi/src/Osi
INCLUDEPATH += ../../external/CoinOR/Clp/src/OsiClp
INCLUDEPATH += ../../external/CoinOR/Clp/src/
INCLUDEPATH += ../MIPSolver
INCLUDEPATH += ../../ModelerInterface

DEFINES += MIPCLPSOLVER_LIBRARY

SOURCES += MIPClpSolver.cpp

HEADERS += MIPClpSolver.h \
           MIPClpSolver_global.h


DESTDIR     = ../../lib/$$(OPTION)

win32 {
    QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT
}

