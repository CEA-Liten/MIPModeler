QT       -= gui

TEMPLATE = lib

TARGET      = MIPCpxSolver$$(CPLEX_VERSION)
win32 {
    LIBS        += $$(CPLEX_HOME_LIB)/cplex$$(CPLEX_VERSION).lib
    LIBS        += ../../lib/$$(OPTION)/MIPModeler.lib

}
unix {
    LIBS        += $$(CPLEX_HOME_LIB)/libcplex.a
    LIBS        += ../../lib/$$(OPTION)/libMIPModeler.so
}

INCLUDEPATH += $$(CPLEX_HOME)/include/ilcplex

INCLUDEPATH += ../../core/
INCLUDEPATH += ../../external/Eigen/3.2.9/
INCLUDEPATH += ../MIPSolver
INCLUDEPATH += ../../ModelerInterface

DEFINES += MIPCPXSOLVER_LIBRARY

SOURCES += MIPCpxSolver.cpp \

HEADERS += MIPCpxSolver_global.h \
           MIPCpxSolver.h

DESTDIR  = ../../lib/$$(OPTION)

# QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT

message($$(CPLEX_HOME_LIB)/cplex$$(CPLEX_VERSION).lib)
