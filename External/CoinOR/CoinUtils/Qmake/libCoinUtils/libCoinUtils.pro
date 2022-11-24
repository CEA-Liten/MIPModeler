QT       -= core gui

TARGET = libCoinUtils
TEMPLATE = lib
#CONFIG += staticlib

INCLUDEPATH += ../../../BuildTools/headers

DEFINES += COINUTILS_BUILD
DEFINES += WIN32
DEFINES += NDEBUG
DEFINES += _LIB
DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _CRT_SECURE_NO_DEPRECATE

SOURCES += \
    ../../src/CoinAlloc.cpp \
    ../../src/CoinBuild.cpp \
    ../../src/CoinDenseFactorization.cpp \
    ../../src/CoinDenseVector.cpp \
    ../../src/CoinError.cpp \
    ../../src/CoinFactorization1.cpp \
    ../../src/CoinFactorization2.cpp \
    ../../src/CoinFactorization3.cpp \
    ../../src/CoinFactorization4.cpp \
    ../../src/CoinFileIO.cpp \
    ../../src/CoinFinite.cpp \
    ../../src/CoinIndexedVector.cpp \
    ../../src/CoinLpIO.cpp \
    ../../src/CoinMessage.cpp \
    ../../src/CoinMessageHandler.cpp \
    ../../src/CoinModel.cpp \
    ../../src/CoinModelUseful.cpp \
    ../../src/CoinModelUseful2.cpp \
    ../../src/CoinMpsIO.cpp \
    ../../src/CoinOslFactorization.cpp \
    ../../src/CoinOslFactorization2.cpp \
    ../../src/CoinOslFactorization3.cpp \
    ../../src/CoinPackedMatrix.cpp \
    ../../src/CoinPackedVector.cpp \
    ../../src/CoinPackedVectorBase.cpp \
    ../../src/CoinParam.cpp \
    ../../src/CoinParamUtils.cpp \
    ../../src/CoinPostsolveMatrix.cpp \
    ../../src/CoinPrePostsolveMatrix.cpp \
    ../../src/CoinPresolveDoubleton.cpp \
    ../../src/CoinPresolveDual.cpp \
    ../../src/CoinPresolveDupcol.cpp \
    ../../src/CoinPresolveEmpty.cpp \
    ../../src/CoinPresolveFixed.cpp \
    ../../src/CoinPresolveForcing.cpp \
    ../../src/CoinPresolveHelperFunctions.cpp \
    ../../src/CoinPresolveImpliedFree.cpp \
    ../../src/CoinPresolveIsolated.cpp \
    ../../src/CoinPresolveMatrix.cpp \
    ../../src/CoinPresolveMonitor.cpp \
    ../../src/CoinPresolvePsdebug.cpp \
    ../../src/CoinPresolveSingleton.cpp \
    ../../src/CoinPresolveSubst.cpp \
    ../../src/CoinPresolveTighten.cpp \
    ../../src/CoinPresolveTripleton.cpp \
    ../../src/CoinPresolveUseless.cpp \
    ../../src/CoinPresolveZeros.cpp \
    ../../src/CoinRational.cpp \
    ../../src/CoinSearchTree.cpp \
    ../../src/CoinShallowPackedVector.cpp \
    ../../src/CoinSimpFactorization.cpp \
    ../../src/CoinSnapshot.cpp \
    ../../src/CoinStructuredModel.cpp \
    ../../src/CoinWarmStartBasis.cpp \
    ../../src/CoinWarmStartDual.cpp \
    ../../src/CoinWarmStartPrimalDual.cpp \
    ../../src/CoinWarmStartVector.cpp \

HEADERS +=  \
    ../../src/CoinAlloc.hpp \
    ../../src/CoinBuild.hpp \
    ../../src/CoinDenseFactorization.hpp \
    ../../src/CoinDenseVector.hpp \
    ../../src/CoinDistance.hpp \
    ../../src/CoinError.hpp \
    ../../src/CoinFactorization.hpp \
    ../../src/CoinFileIO.hpp \
    ../../src/CoinFinite.hpp \
    ../../src/CoinFloatEqual.hpp \
    ../../src/CoinHelperFunctions.hpp \
    ../../src/CoinIndexedVector.hpp \
    ../../src/CoinLpIO.hpp \
    ../../src/CoinMessage.hpp \
    ../../src/CoinMessageHandler.hpp \
    ../../src/CoinModel.hpp \
    ../../src/CoinModelUseful.hpp \
    ../../src/CoinMpsIO.hpp \
    ../../src/CoinOslC.h \
    ../../src/CoinOslFactorization.hpp \
    ../../src/CoinPackedMatrix.hpp \
    ../../src/CoinPackedVector.hpp \
    ../../src/CoinPackedVectorBase.hpp \
    ../../src/CoinParam.hpp \
    ../../src/CoinPragma.hpp \
    ../../src/CoinPresolveDoubleton.hpp \
    ../../src/CoinPresolveDual.hpp \
    ../../src/CoinPresolveDupcol.hpp \
    ../../src/CoinPresolveEmpty.hpp \
    ../../src/CoinPresolveFixed.hpp \
    ../../src/CoinPresolveForcing.hpp \
    ../../src/CoinPresolveImpliedFree.hpp \
    ../../src/CoinPresolveIsolated.hpp \
    ../../src/CoinPresolveMatrix.hpp \
    ../../src/CoinPresolveMonitor.hpp \
    ../../src/CoinPresolvePsdebug.hpp \
    ../../src/CoinPresolveSingleton.hpp \
    ../../src/CoinPresolveSubst.hpp \
    ../../src/CoinPresolveTighten.hpp \
    ../../src/CoinPresolveTripleton.hpp \
    ../../src/CoinPresolveUseless.hpp \
    ../../src/CoinPresolveZeros.hpp \
    ../../src/CoinRational.hpp \
    ../../src/CoinSearchTree.hpp \
    ../../src/CoinShallowPackedVector.hpp \
    ../../src/CoinSignal.hpp \
    ../../src/CoinSimpFactorization.hpp \
    ../../src/CoinSmartPtr.hpp \
    ../../src/CoinSnapshot.hpp \
    ../../src/CoinSort.hpp \
    ../../src/CoinStructuredModel.hpp \
    ../../src/CoinTime.hpp \
    ../../src/CoinTypes.hpp \
    ../../src/CoinUtility.hpp \
    ../../src/CoinUtilsConfig.h \
    ../../src/CoinWarmStart.hpp \
    ../../src/CoinWarmStartBasis.hpp \
    ../../src/CoinWarmStartDual.hpp \
    ../../src/CoinWarmStartPrimalDual.hpp \
    ../../src/CoinWarmStartVector.hpp \
    ../../src/Coin_C_defines.h \
    ../../src/Config_coinutils_default.h \
    ../../src/Config_default.h \
    ../../src/config.h \
    ../../src/config_coinutils.h \

DESTDIR = ../../../lib/$$(OPTION)

