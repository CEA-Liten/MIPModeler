QT       -= gui

TARGET = libCbc
TEMPLATE = lib
#CONFIG += staticlib

INCLUDEPATH += ../../../Cbc/src/
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
INCLUDEPATH += ../../../Cgl/src/CglResidualCapacity
INCLUDEPATH += ../../../Cgl/src/CglRedSplit2

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
DEFINES += WIN32
DEFINES += _LIB
DEFINES += USE_CBCCONFIG
DEFINES += COIN_NO_CLP_MESSAGE
DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _CRT_SECURE_NO_DEPRECATE

SOURCES += \
    ../../src/CbcBranchAllDifferent.cpp \
    ../../src/CbcBranchCut.cpp \
    ../../src/CbcBranchDecision.cpp \
    ../../src/CbcBranchDefaultDecision.cpp \
    ../../src/CbcBranchDynamic.cpp \
    ../../src/CbcBranchingObject.cpp \
    ../../src/CbcBranchLotsize.cpp \
    ../../src/CbcBranchToFixLots.cpp \
    ../../src/CbcClique.cpp \
    ../../src/CbcCompareDefault.cpp \
    ../../src/CbcCompareDepth.cpp \
    ../../src/CbcCompareEstimate.cpp \
    ../../src/CbcCompareObjective.cpp \
    ../../src/CbcConsequence.cpp \
    ../../src/CbcCountRowCut.cpp \
    ../../src/CbcCutGenerator.cpp \
    ../../src/CbcCutModifier.cpp \
    ../../src/CbcCutSubsetModifier.cpp \
    ../../src/CbcDummyBranchingObject.cpp \
    ../../src/CbcEventHandler.cpp \
    ../../src/CbcFathom.cpp \
    ../../src/CbcFathomDynamicProgramming.cpp \
    ../../src/CbcFixVariable.cpp \
    ../../src/CbcFollowOn.cpp \
    ../../src/CbcFullNodeInfo.cpp \
    ../../src/CbcGeneral.cpp \
    ../../src/CbcGeneralDepth.cpp \
    ../../src/CbcHeuristic.cpp \
    ../../src/CbcHeuristicDINS.cpp \
    ../../src/CbcHeuristicDive.cpp \
    ../../src/CbcHeuristicDiveCoefficient.cpp \
    ../../src/CbcHeuristicDiveFractional.cpp \
    ../../src/CbcHeuristicDiveGuided.cpp \
    ../../src/CbcHeuristicDiveLineSearch.cpp \
    ../../src/CbcHeuristicDivePseudoCost.cpp \
    ../../src/CbcHeuristicDiveVectorLength.cpp \
    ../../src/CbcHeuristicDW.cpp \
    ../../src/CbcHeuristicFPump.cpp \
    ../../src/CbcHeuristicGreedy.cpp \
    ../../src/CbcHeuristicLocal.cpp \
    ../../src/CbcHeuristicPivotAndFix.cpp \
    ../../src/CbcHeuristicRandRound.cpp \
    ../../src/CbcHeuristicRENS.cpp \
    ../../src/CbcHeuristicRINS.cpp \
    ../../src/CbcHeuristicVND.cpp \
    ../../src/CbcMessage.cpp \
    ../../src/CbcMipStartIO.cpp \
    ../../src/CbcModel.cpp \
    ../../src/CbcNode.cpp \
    ../../src/CbcNodeInfo.cpp \
    ../../src/CbcNWay.cpp \
    ../../src/CbcObject.cpp \
    ../../src/CbcObjectUpdateData.cpp \
    ../../src/CbcParam.cpp \
    ../../src/CbcPartialNodeInfo.cpp \
    ../../src/CbcSimpleInteger.cpp \
    ../../src/CbcSimpleIntegerDynamicPseudoCost.cpp \
    ../../src/CbcSimpleIntegerPseudoCost.cpp \
    ../../src/CbcSOS.cpp \
    ../../src/CbcStatistics.cpp \
    ../../src/CbcStrategy.cpp \
    ../../src/CbcSubProblem.cpp \
    ../../src/CbcThread.cpp \
    ../../src/CbcTree.cpp \
    ../../src/CbcTreeLocal.cpp \


HEADERS +=  \
    ../../src/CbcBranchActual.hpp \
    ../../src/CbcBranchAllDifferent.hpp \
    ../../src/CbcBranchBase.hpp \
    ../../src/CbcBranchCut.hpp \
    ../../src/CbcBranchDecision.hpp \
    ../../src/CbcBranchDefaultDecision.hpp \
    ../../src/CbcBranchDynamic.hpp \
    ../../src/CbcBranchingObject.hpp \
    ../../src/CbcBranchLotsize.hpp \
    ../../src/CbcBranchToFixLots.hpp \
    ../../src/CbcClique.hpp \
    ../../src/CbcCompare.hpp \
    ../../src/CbcCompareActual.hpp \
    ../../src/CbcCompareBase.hpp \
    ../../src/CbcCompareDefault.hpp \
    ../../src/CbcCompareDepth.hpp \
    ../../src/CbcCompareEstimate.hpp \
    ../../src/CbcCompareObjective.hpp \
    ../../src/CbcConfig.h \
    ../../src/CbcConsequence.hpp \
    ../../src/CbcCountRowCut.hpp \
    ../../src/CbcCutGenerator.hpp \
    ../../src/CbcCutModifier.hpp \
    ../../src/CbcCutSubsetModifier.hpp \
    ../../src/CbcDummyBranchingObject.hpp \
    ../../src/CbcEventHandler.hpp \
    ../../src/CbcFathom.hpp \
    ../../src/CbcFathomDynamicProgramming.hpp \
    ../../src/CbcFeasibilityBase.hpp \
    ../../src/CbcFixVariable.hpp \
    ../../src/CbcFollowOn.hpp \
    ../../src/CbcFullNodeInfo.hpp \
    ../../src/CbcGeneral.hpp \
    ../../src/CbcGeneralDepth.hpp \
    ../../src/CbcHeuristic.hpp \
    ../../src/CbcHeuristicDINS.hpp \
    ../../src/CbcHeuristicDive.hpp \
    ../../src/CbcHeuristicDiveCoefficient.hpp \
    ../../src/CbcHeuristicDiveFractional.hpp \
    ../../src/CbcHeuristicDiveGuided.hpp \
    ../../src/CbcHeuristicDiveLineSearch.hpp \
    ../../src/CbcHeuristicDivePseudoCost.hpp \
    ../../src/CbcHeuristicDiveVectorLength.hpp \
    ../../src/CbcHeuristicDW.hpp \
    ../../src/CbcHeuristicFPump.hpp \
    ../../src/CbcHeuristicGreedy.hpp \
    ../../src/CbcHeuristicLocal.hpp \
    ../../src/CbcHeuristicPivotAndFix.hpp \
    ../../src/CbcHeuristicRandRound.hpp \
    ../../src/CbcHeuristicRENS.hpp \
    ../../src/CbcHeuristicRINS.hpp \
    ../../src/CbcHeuristicVND.hpp \
    ../../src/CbcMessage.hpp \
    ../../src/CbcMipStartIO.hpp \
    ../../src/CbcModel.hpp \
    ../../src/CbcNode.hpp \
    ../../src/CbcNodeInfo.hpp \
    ../../src/CbcNWay.hpp \
    ../../src/CbcObject.hpp \
    ../../src/CbcObjectUpdateData.hpp \
    ../../../Clp/src/CbcOrClpParam.hpp \
    ../../src/CbcParam.hpp \
    ../../src/CbcPartialNodeInfo.hpp \
    ../../src/CbcSimpleInteger.hpp \
    ../../src/CbcSimpleIntegerDynamicPseudoCost.hpp \
    ../../src/CbcSimpleIntegerPseudoCost.hpp \
    ../../src/CbcSOS.hpp \
    ../../src/CbcStatistics.hpp \
    ../../src/CbcStrategy.hpp \
    ../../src/CbcSubProblem.hpp \
    ../../src/CbcThread.hpp \
    ../../src/CbcTree.hpp \
    ../../src/CbcTreeLocal.hpp \

DESTDIR = ../../../lib/$$(OPTION)
