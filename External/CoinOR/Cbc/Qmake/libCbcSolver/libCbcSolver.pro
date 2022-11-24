#-------------------------------------------------
#
# Project created by QtCreator 2016-09-13T09:54:02
#
#-------------------------------------------------
QT       -= gui

TARGET = libCbcSolver
TEMPLATE = lib
#CONFIG += staticlib

INCLUDEPATH += ../../../Cbc/src
INCLUDEPATH += ../../../Cgl/src/CglZeroHalf
INCLUDEPATH += ../../../Cgl/src/CglGMI
INCLUDEPATH += ../../../Cgl/src/CglLandP
INCLUDEPATH += ../../../Cgl/src/CglTwomir
INCLUDEPATH += ../../../Cgl/src/CglMixedIntegerRounding
INCLUDEPATH += ../../../Cgl/src/CglMixedIntegerRounding2
INCLUDEPATH += ../../../Cgl/src/CglFlowCover
INCLUDEPATH += ../../../Cgl/src/CglClique
INCLUDEPATH += ../../../Cgl/src/CglOddHole
INCLUDEPATH += ../../../Cgl/src/CglKnapsackCover
INCLUDEPATH += ../../../Cgl/src/CglGomory
INCLUDEPATH += ../../../Cgl/src/CglPreProcess
INCLUDEPATH += ../../../Cgl/src/CglDuplicateRow
INCLUDEPATH += ../../../Cgl/src/CglRedSplit
INCLUDEPATH += ../../../Cgl/src/CglProbing
INCLUDEPATH += ../../../Cgl/src
INCLUDEPATH += ../../../Clp/src
INCLUDEPATH += ../../../Clp/src/OsiClp
INCLUDEPATH += ../../../Osi/src/Osi
INCLUDEPATH += ../../../CoinUtils/src
INCLUDEPATH += ../../../BuildTools/headers
INCLUDEPATH += ../../../Cgl/src/CglResidualCapacity
INCLUDEPATH += ../../../Cgl/src/CglRedSplit2

LIBS        += ../../../lib/$$(OPTION)/libCbc.lib
LIBS        += ../../../lib/$$(OPTION)/libCgl.lib
LIBS        += ../../../lib/$$(OPTION)/libClp.lib
LIBS        += ../../../lib/$$(OPTION)/libOsiClp.lib
LIBS        += ../../../lib/$$(OPTION)/libOsi.lib
LIBS        += ../../../lib/$$(OPTION)/libCoinUtils.lib

DEFINES += CBC_BUILD
DEFINES += WIN32
DEFINES += NDEBUG
DEFINES += _NDEBUG
DEFINES += COIN_FAST_CODE
DEFINES += CLP_FAST_CODE
DEFINES += COIN_NO_TEST_DUPLICATE
DEFINES += _CRT_SECURE_NO_WARNINGS

SOURCES += \
    ../../src/CbcCbcParam.cpp \
    ../../src/CbcLinked.cpp \
    ../../src/CbcLinkedUtils.cpp \
    ../../src/CbcSolver.cpp \
    ../../src/CbcSolverAnalyze.cpp \
    ../../src/CbcSolverExpandKnapsack.cpp \
    ../../src/CbcSolverHeuristics.cpp \
    ../../src/unitTestClp.cpp \

HEADERS +=  \
    ../../src/CbcLinked.hpp \
    ../../src/CbcSolver.hpp \
    ../../src/CbcSolverAnalyze.hpp \
    ../../src/CbcSolverExpandKnapsack.hpp \
    ../../src/CbcSolverHeuristics.hpp \

DESTDIR = ../../../lib/$$(OPTION)
