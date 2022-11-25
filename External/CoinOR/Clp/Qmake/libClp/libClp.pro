QT       -= gui

TARGET = libClp
TEMPLATE = lib
#CONFIG += staticlib

INCLUDEPATH += ../../../CoinUtils/src
LIBS        += ../../../lib/$$(OPTION)/libCoinUtils.lib

DEFINES += CLP_BUILD
DEFINES += WIN32
DEFINES += NDEBUG
DEFINES += _LIB
DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _CRT_SECURE_NO_DEPRECATE

DEFINES += HAVE_MATH_H

SOURCES += \
    ../../src/Clp_C_Interface.cpp \
    ../../src/ClpCholeskyBase.cpp \
    ../../src/ClpCholeskyDense.cpp \
#   ../../src/ClpCholeskyUfl.cpp \
#   ../../src/ClpCholeskyWssmp.cpp \
#   ../../src/ClpCholeskyWssmpKKT.cpp \
    ../../src/ClpConstraint.cpp \
    ../../src/ClpConstraintLinear.cpp \
    ../../src/ClpConstraintQuadratic.cpp \
    ../../src/ClpDualRowDantzig.cpp \
    ../../src/ClpDualRowPivot.cpp \
    ../../src/ClpDualRowSteepest.cpp \
    ../../src/ClpDummyMatrix.cpp \
    ../../src/ClpDynamicExampleMatrix.cpp \
    ../../src/ClpDynamicMatrix.cpp \
    ../../src/ClpEventHandler.cpp \
    ../../src/ClpFactorization.cpp \
    ../../src/ClpGubDynamicMatrix.cpp \
    ../../src/ClpGubMatrix.cpp \
    ../../src/ClpHelperFunctions.cpp \
    ../../src/ClpInterior.cpp \
    ../../src/ClpLinearObjective.cpp \
    ../../src/ClpLsqr.cpp \
    ../../src/ClpMatrixBase.cpp \
    ../../src/ClpMessage.cpp \
    ../../src/ClpModel.cpp \
    ../../src/ClpNetworkBasis.cpp \
    ../../src/ClpNetworkMatrix.cpp \
    ../../src/ClpNode.cpp \
    ../../src/ClpNonLinearCost.cpp \
    ../../src/ClpObjective.cpp \
    ../../src/ClpPackedMatrix.cpp \
    ../../src/ClpPdco.cpp \
    ../../src/ClpPdcoBase.cpp \
    ../../src/ClpPlusMinusOneMatrix.cpp \
    ../../src/ClpPredictorCorrector.cpp \
    ../../src/ClpPresolve.cpp \
    ../../src/ClpPrimalColumnDantzig.cpp \
    ../../src/ClpPrimalColumnPivot.cpp \
    ../../src/ClpPrimalColumnSteepest.cpp \
    ../../src/ClpQuadraticObjective.cpp \
    ../../src/ClpSimplex.cpp \
    ../../src/ClpSimplexDual.cpp \
    ../../src/ClpSimplexNonlinear.cpp \
    ../../src/ClpSimplexOther.cpp \
    ../../src/ClpSimplexPrimal.cpp \
    ../../src/ClpSolve.cpp \
    ../../src/Idiot.cpp \
    ../../src/IdiSolve.cpp \
#   ../../src/ClpCholeskyMumps.cpp \

HEADERS +=  \
    ../../src/Clp_C_Interface.h \
    ../../src/ClpCholeskyBase.hpp \
    ../../src/ClpCholeskyDense.hpp \
    ../../src/ClpCholeskyMumps.hpp \
    ../../src/ClpCholeskyUfl.hpp \
    ../../src/ClpCholeskyWssmp.hpp \
    ../../src/ClpConfig.h \
    ../../src/ClpConstraint.hpp \
    ../../src/ClpConstraintLinear.hpp \
    ../../src/ClpConstraintQuadratic.hpp \
    ../../src/ClpDualRowDantzig.hpp \
    ../../src/ClpDualRowPivot.hpp \
    ../../src/ClpDualRowSteepest.hpp \
    ../../src/ClpDummyMatrix.hpp \
    ../../src/ClpDynamicExampleMatrix.hpp \
    ../../src/ClpDynamicMatrix.hpp \
    ../../src/ClpEventHandler.hpp \
    ../../src/ClpFactorization.hpp \
    ../../src/ClpGubDynamicMatrix.hpp \
    ../../src/ClpGubMatrix.hpp \
    ../../src/ClpHelperFunctions.hpp \
    ../../src/ClpInterior.hpp \
    ../../src/ClpLinearObjective.hpp \
    ../../src/ClpLsqr.hpp \
    ../../src/ClpMatrixBase.hpp \
    ../../src/ClpMessage.hpp \
    ../../src/ClpModel.hpp \
    ../../src/ClpNetworkBasis.hpp \
    ../../src/ClpNetworkMatrix.hpp \
    ../../src/ClpNode.hpp \
    ../../src/ClpNonLinearCost.hpp \
    ../../src/ClpObjective.hpp \
    ../../src/ClpPackedMatrix.hpp \
    ../../src/ClpParameters.hpp \
    ../../src/ClpPdco.hpp \
    ../../src/ClpPdcoBase.hpp \
    ../../src/ClpPlusMinusOneMatrix.hpp \
    ../../src/ClpPredictorCorrector.hpp \
    ../../src/ClpPresolve.hpp \
    ../../src/ClpPrimalColumnDantzig.hpp \
    ../../src/ClpPrimalColumnPivot.hpp \
    ../../src/ClpPrimalColumnSteepest.hpp \
    ../../src/ClpQuadraticObjective.hpp \
    ../../src/ClpSimplex.hpp \
    ../../src/ClpSimplexDual.hpp \
    ../../src/ClpSimplexNonlinear.hpp \
    ../../src/ClpSimplexOther.hpp \
    ../../src/ClpSimplexPrimal.hpp \
    ../../src/ClpSolve.hpp \
    ../../src/Idiot.hpp \

DESTDIR = ../../../lib/$$(OPTION)
