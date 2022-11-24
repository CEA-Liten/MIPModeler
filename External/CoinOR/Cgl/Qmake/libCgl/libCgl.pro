#-------------------------------------------------
#
# Project created by QtCreator 2016-09-13T09:54:02
#
#-------------------------------------------------
QT       -= gui

TARGET = libCgl
TEMPLATE = lib
#CONFIG += staticlib

INCLUDEPATH += ../../../Cgl/src/CglDuplicateRow
INCLUDEPATH += ../../../Cgl/src/CglMixedIntegerRounding
INCLUDEPATH += ../../../Cgl/src/CglMixedIntegerRounding2
INCLUDEPATH += ../../../Cgl/src/CglFlowCover
INCLUDEPATH += ../../../Cgl/src/CglClique
INCLUDEPATH += ../../../Cgl/src/CglOddHole
INCLUDEPATH += ../../../Cgl/src/CglKnapsackCover
INCLUDEPATH += ../../../Cgl/src/CglGomory
INCLUDEPATH += ../../../Cgl/src/CglPreProcess
INCLUDEPATH += ../../../Cgl/src/CglRedSplit
INCLUDEPATH += ../../../Cgl/src/CglResidualCapacity
INCLUDEPATH += ../../../Cgl/src/CglProbing
INCLUDEPATH += ../../../Cgl/src
INCLUDEPATH += ../../../Osi/src/Osi
INCLUDEPATH += ../../../Clp/src/OsiClp
INCLUDEPATH += ../../../Clp/src
INCLUDEPATH += ../../../CoinUtils/src
INCLUDEPATH += ../../../BuildTools/headers

LIBS        += ../../../lib/$$(OPTION)/libOsi.lib
LIBS        += ../../../lib/$$(OPTION)/libOsiClp.lib
LIBS        += ../../../lib/$$(OPTION)/libClp.lib
LIBS        += ../../../lib/$$(OPTION)/libCoinUtils.lib

DEFINES += CGL_BUILD
DEFINES += WIN32
DEFINES += NDEBUG
DEFINES += _LIB
DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _CRT_SECURE_NO_DEPRECATE
DEFINES += _SCL_SECURE_NO_WARNINGS

SOURCES += \
    ../../src/CglZeroHalf/CglZeroHalfTest.cpp \
    ../../src/CglZeroHalf/CglZeroHalf.cpp \
    ../../src/CglZeroHalf/Cgl012cut.cpp \
    ../../src/CglTwomir/CglTwomir.cpp \
    ../../src/CglTreeInfo.cpp \
    ../../src/CglStored.cpp \
    ../../src/CglSimpleRounding/CglSimpleRounding.cpp \
    ../../src/CglResidualCapacity/CglResidualCapacityTest.cpp \
    ../../src/CglResidualCapacity/CglResidualCapacity.cpp \
    ../../src/CglRedSplit/CglRedSplitParam.cpp \
    ../../src/CglRedSplit/CglRedSplit.cpp \
    ../../src/CglRedSplit2/CglRedSplit2Test.cpp \
    ../../src/CglRedSplit2/CglRedSplit2Param.cpp \
    ../../src/CglRedSplit2/CglRedSplit2.cpp \
    ../../src/CglProbing/CglProbing.cpp \
    ../../src/CglPreProcess/CglPreProcess.cpp \
    ../../src/CglParam.cpp \
    ../../src/CglOddHole/CglOddHole.cpp \
    ../../src/CglMixedIntegerRounding/CglMixedIntegerRounding.cpp \
    ../../src/CglMixedIntegerRounding2/CglMixedIntegerRounding2.cpp \
    ../../src/CglMessage.cpp \
    ../../src/CglLiftAndProject/CglLiftAndProject.cpp \
    ../../src/CglLandP/CglLandPValidator.cpp \
    ../../src/CglLandP/CglLandPUtils.cpp \
    ../../src/CglLandP/CglLandPTabRow.cpp \
    ../../src/CglLandP/CglLandPSimplex.cpp \
    ../../src/CglLandP/CglLandPMessages.cpp \
    ../../src/CglLandP/CglLandP.cpp \
    ../../src/CglKnapsackCover/CglKnapsackCover.cpp \
    ../../src/CglGomory/CglGomory.cpp \
    ../../src/CglGMI/CglGMIParam.cpp \
    ../../src/CglGMI/CglGMI.cpp \
    ../../src/CglFlowCover/CglFlowCover.cpp \
    ../../src/CglDuplicateRow/CglDuplicateRow.cpp \
    ../../src/CglCutGenerator.cpp \
    ../../src/CglClique/CglCliqueHelper.cpp \
    ../../src/CglClique/CglClique.cpp \
    ../../src/CglAllDifferent/CglAllDifferent.cpp \

HEADERS +=  \
    ../../src/CglAllDifferent/CglAllDifferent.hpp \
    ../../src/CglClique/CglClique.hpp \
    ../../src/CglConfig.h\
    ../../src/CglCutGenerator.hpp \
    ../../src/CglDuplicateRow/CglDuplicateRow.hpp \
    ../../src/CglFlowCover/CglFlowCover.hpp \
    ../../src/CglGMI/CglGMI.hpp \
    ../../src/CglGMI/CglGMIParam.hpp \
    ../../src/CglGomory/CglGomory.hpp \
    ../../src/CglKnapsackCover/CglKnapsackCover.hpp \
    ../../src/CglLandP/CglLandP.hpp \
    ../../src/CglLandP/CglLandPMessages.hpp \
    ../../src/CglLandP/CglLandPSimplex.hpp \
    ../../src/CglLandP/CglLandPTabRow.hpp \
    ../../src/CglLandP/CglLandPUtils.hpp \
    ../../src/CglLandP/CglLandPValidator.hpp \
    ../../src/CglLiftAndProject/CglLiftAndProject.hpp \
    ../../src/CglMessage.hpp \
    ../../src/CglMixedIntegerRounding/CglMixedIntegerRounding.hpp \
    ../../src/CglMixedIntegerRounding2/CglMixedIntegerRounding2.hpp \
    ../../src/CglOddHole/CglOddHole.hpp \
    ../../src/CglParam.hpp \
    ../../src/CglPreProcess/CglPreProcess.hpp \
    ../../src/CglProbing/CglProbing.hpp \
    ../../src/CglRedSplit2/CglRedSplit2.hpp \
    ../../src/CglRedSplit2/CglRedSplit2Param.hpp \
    ../../src/CglRedSplit/CglRedSplit.hpp \
    ../../src/CglRedSplit/CglRedSplitParam.hpp \
    ../../src/CglResidualCapacity/CglResidualCapacity.hpp \
    ../../src/CglSimpleRounding/CglSimpleRounding.hpp \
    ../../src/CglStored.hpp \
    ../../src/CglTreeInfo.hpp \
    ../../src/CglTwomir/CglTwomir.hpp \
    ../../src/CglZeroHalf/Cgl012cut.hpp \
    ../../src/CglZeroHalf/CglZeroHalf.hpp \

DESTDIR = ../../../lib/$$(OPTION)
