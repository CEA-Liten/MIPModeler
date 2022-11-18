QT       -= gui

TEMPLATE = lib


TARGET      = MIPMskSolver81
LIBS        += $$(MOSEK_HOME_81_LIB)/mosek64_8_1.lib
INCLUDEPATH += $$(MOSEK_HOME_81)/h/

LIBS        += $$(MIPMODELER_HOME)/lib/$$(OPTION)/MIPModeler.lib
INCLUDEPATH += $$(MIPMODELER_HOME)/MIPModelerCore/
INCLUDEPATH += $$(SOLVER_DEPS)/Eigen/3.2.9-modif/

DEFINES += MIPMSKSOLVER_LIBRARY

SOURCES += MIPMskSolver.cpp

HEADERS += MIPMskSolver_global.h \
           MIPMskSolver.h

DESTDIR     = $$(MIPMODELER_HOME)/lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT

