#-------------------------------------------------
#
# Project created by QtCreator 2016-09-13T09:54:02
#
#-------------------------------------------------

QT      -= gui
TARGET   = MIPModeler
TEMPLATE = lib

INCLUDEPATH += ../external/Eigen/3.2.9

_GAMS_HOME=$$(GAMS_HOME)

!isEmpty(_GAMS_HOME) {
    LIBS        += $$(GAMS_HOME)/apifiles/C++/lib/vs2019/gamscpp.lib
    INCLUDEPATH += $$(GAMS_HOME)/apifiles/C++/api
    LIBS        += ../lib/$$(OPTION)/GAMSModeler39.lib
    INCLUDEPATH += ../GAMSModeler
}

SOURCES += \
        MIPConstraint.cpp \
        MIPExpression.cpp \
        MIPModel.cpp \
        MIPSubobjective.cpp \
        MIPVariable0D.cpp \
        MIPVariable1D.cpp \
        MIPVariable2D.cpp \
        MIPVariable3D.cpp \
        MIPSpecialOrderedSet.cpp \
        MIPUtils.cpp \
        MIPModeler.cpp \
        MIPWarmStart.cpp
HEADERS += \
        MIPModeler_global.h \
        MIPConstraint.h \
        MIPExpression.h \
        MIPModel.h \
        MIPVariable0D.h \
        MIPVariable1D.h \
        MIPVariable2D.h \
        MIPVariable3D.h \
        MIPSpecialOrderedSet.h \
        MIPUtils.h \
        MIPModeler.h \
        MIPWarmStart.h \
        MIPSubobjective.h

DEFINES += MIPMODELER_LIBRARY
DEFINES += EIGEN_MPL2_ONLY

DESTDIR      = ../lib/$$(OPTION)

# QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT

