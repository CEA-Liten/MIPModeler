cmake_minimum_required (VERSION 3.0)

project (MIPModeler VERSION 1.5.0 LANGUAGES CXX)

add_subdirectory(MIPModelerCore)
add_subdirectory(MIPSolverInterface/MIPCpxSolver)
