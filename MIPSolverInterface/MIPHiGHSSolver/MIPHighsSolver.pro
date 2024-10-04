QT       -= gui

TEMPLATE = lib

TARGET      = MIPHighsSolver

LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib
LIBS        += ../../external/CoinOR/lib/$$(OPTION)/libHighs.lib

INCLUDEPATH += ../../core/
INCLUDEPATH += ../../external/Eigen/3.2.9/
INCLUDEPATH += ../../external/CoinOR/Highs/include/highs

DEFINES += MIPHIGHSSOLVER_LIBRARY

SOURCES += MIPHighsSolver.cpp \

HEADERS += MIPHighsSolver_global.h \
           MIPHighsSolver.h

DESTDIR  = ../../lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT

