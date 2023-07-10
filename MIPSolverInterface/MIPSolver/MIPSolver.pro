QT       -= gui

TARGET = MIPSolver
TEMPLATE = lib


INCLUDEPATH += ../../core/

DEFINES += MIPSOLVER_LIBRARY

SOURCES += MIPSolverFactory.cpp

HEADERS += MIPSolverFactory.h \
           MIPSolver_global.h \
           IMIPSolver.h

DESTDIR     = ../../lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT


