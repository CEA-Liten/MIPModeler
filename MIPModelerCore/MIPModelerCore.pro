#-------------------------------------------------
#
# Project created by QtCreator 2016-09-13T09:54:02
#
#-------------------------------------------------

QT       -= gui

TARGET = MIPModeler
TEMPLATE = lib

INCLUDEPATH += include
INCLUDEPATH += $$(DEPS_HOME)/External/Eigen/3.2.9-modif

SOURCES += \
        src/MIPConstraint.cpp \
        src/MIPExpression.cpp \
        src/MIPModel.cpp \
        src/MIPVariable0D.cpp \
        src/MIPVariable1D.cpp \
        src/MIPVariable2D.cpp \
        src/MIPVariable3D.cpp \
        src/MIPSpecialOrderedSet.cpp \
        src/MIPUtils.cpp \
        src/MIPModeler.cpp \
        src/MIPWarmStart.cpp
HEADERS += \
        include/MIPModeler_global.h \
        include/MIPConstraint.h \
        include/MIPExpression.h \
        include/MIPModel.h \
        include/MIPVariable0D.h \
        include/MIPVariable1D.h \
        include/MIPVariable2D.h \
        include/MIPVariable3D.h \
        include/MIPSpecialOrderedSet.h \
        include/MIPUtils.h \
        include/MIPModeler.h \
        include/MIPWarmStart.h

DEFINES += MIPMODELER_LIBRARY
DEFINES += EIGEN_MPL2_ONLY

DESTDIR     = $$(PEGASE_MPC_HOME)/lib/$$(OPTION)

QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT
