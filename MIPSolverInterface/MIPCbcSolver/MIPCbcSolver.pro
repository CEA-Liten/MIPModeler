QT       -= gui

TARGET = MIPCbcSolver
TEMPLATE = lib

win32 {
    LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libCbc.lib
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libCbcSolver.lib
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libCoinUtils.lib
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libOsi.lib
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libOsiCbc.lib
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libOsiClp.lib
}
unix {
    LIBS        += ../../lib/$$(OPTION)/libMIPModeler.so
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/liblibCbc.so
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/liblibCbcSolver.so
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/liblibCgl.so
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/liblibClp.so
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/liblibCoinUtils.so
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/liblibOsi.so
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/liblibOsiCbc.so
    LIBS        += ../../external/CoinOR/lib/$$(OPTION)/liblibOsiClp.so
}

INCLUDEPATH += ../../core/
INCLUDEPATH += ../../external/Eigen/3.2.9/
INCLUDEPATH += ../../external/CoinOR/Cgl/src/
INCLUDEPATH += ../../external/CoinOR/CoinUtils/src/
INCLUDEPATH += ../../external/CoinOR/Osi/src/Osi/
INCLUDEPATH += ../../external/CoinOR/Cbc/src/
INCLUDEPATH += ../../external/CoinOR/Clp/src/OsiClp
INCLUDEPATH += ../../external/CoinOR/Clp/src/
INCLUDEPATH += ../MIPSolver
INCLUDEPATH += ../../ModelerInterface

DEFINES += MIPCBCSOLVER_LIBRARY

SOURCES += MIPCbcSolver.cpp

HEADERS += MIPCbcSolver.h \
           MIPCbcSolver_global.h

DESTDIR     = ../../lib/$$(OPTION)

win32 {
    QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT
}



