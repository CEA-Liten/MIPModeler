QT       -= gui

TARGET = MIPSolver
TEMPLATE = lib


INCLUDEPATH += ../../core/
INCLUDEPATH += ../../ModelerInterface
INCLUDEPATH += ../../external/Eigen/3.2.9/

DEFINES += MIPSOLVER_LIBRARY

SOURCES += MIPSolverFactory.cpp

HEADERS += MIPSolverFactory.h \
           MIPSolver_global.h \
           IMIPSolver.h

DESTDIR     = ../../lib/$$(OPTION)

win32 {
    QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT
}



