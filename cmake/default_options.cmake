# ================================================================
# All the default values for pegase cmake parameters
#
# --------- User-defined options ---------
# Use cmake -DOPTION_NAME=some-value ... to modify default value.


# --- Build/compiling options ---
option(WITH_TESTING "Build tests. Default = OFF" ON)

# TODO!!
set(WARNINGS_LEVEL 0 CACHE INTERNAL "Set compiler diagnostics level. 0: no warnings, 1: developer's minimal warnings, 2: strict level, warnings to errors and so on. Default =0")
option(BUILD_SHARED_LIBS "Building of shared libraries. Default = ON" ON)

# Compilation de MIPModeler 
set(MIPMODELER_HOME ${CMAKE_SOURCE_DIR} CACHE INTERNAL "MIPModeler installation path")
set(COINOR_ROOT ${MIPMODELER_HOME}/external/CoinOR CACHE INTERNAL "Cbc, Clp installation path")
option(WITH_HIGHS_INSTALL "Highs install" ON) 
option(WITH_EIGEN_INSTALL "Eigen install" ON) 
option(WITH_SPDLOG_INSTALL "spdlog install" ON)
option(USE_CPLEX "Enable CPLEX support" ON) 


# Cplex path
set(CPLEX_ROOT "C:/Program Files/IBM/ILOG/CPLEX_Studio201/cplex" CACHE INTERNAL "CPLEX installation path (if exists use CPLEX)")


# Python, to force Python (if not defined, use find_package Python3)
set(PYTHON_HOME C:/PythonPegase/3_10_9/python CACHE INTERNAL "Python installation path")
set(PYTHON_VENV C:/PythonPegase/3_10_9/envPegase CACHE INTERNAL "Python virtual environment")

