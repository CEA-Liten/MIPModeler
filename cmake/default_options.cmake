# ================================================================
# All the default values for pegase cmake parameters
#
# --------- User-defined options ---------
# Use cmake -DOPTION_NAME=some-value ... to modify default value.


# --- Build/compiling options ---
option(WITH_TESTING "Build tests. Default = OFF" OFF)

# TODO!!
set(WARNINGS_LEVEL 0 CACHE INTERNAL "Set compiler diagnostics level. 0: no warnings, 1: developer's minimal warnings, 2: strict level, warnings to errors and so on. Default =0")
option(BUILD_SHARED_LIBS "Building of shared libraries. Default = ON" ON)


# Qt, version, chemin,...
set(Qt5_HOME C:/Qt/Qt5.15.0/5.15.0/msvc2019_64 CACHE INTERNAL "Qt5 home path")
set(Qt5_DIR ${Qt5_HOME}/lib/cmake/Qt5 CACHE INTERNAL "Qt5 installation path")
set(Qt5_BIN ${Qt5_HOME}/bin CACHE INTERNAL "Qt5 bin path")


# Compilation de MIPModeler 
#set(GAMS_ROOT C:/GAMS/39 CACHE INTERNAL "GAMS installation path (if exists build GAMSModeler)")
set(MIPMODELER_HOME ${CMAKE_SOURCE_DIR} CACHE INTERNAL "MIPModeler installation path")
set(CPLEX_ROOT "C:/Program Files/IBM/ILOG/CPLEX_Studio201/cplex" CACHE INTERNAL "CPLEX installation path (if exists use CPLEX)")
set(COINOR_ROOT ${MIPMODELER_HOME}/external/CoinOR CACHE INTERNAL "Cbc, Clp installation path")
set(HIGHS_ROOT ${MIPMODELER_HOME}/external/HiGHS CACHE INTERNAL "HiGHS installation path")

# Python, to force Python (if not defined, use find_package Python3)
set(PYTHON_HOME C:/PythonPegase/3_10_9/python CACHE INTERNAL "Python installation path")
set(PYTHON_VENV C:/PythonPegase/3_10_9/envPegase CACHE INTERNAL "Python virtual environment")

