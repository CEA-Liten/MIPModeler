TEMPLATE = subdirs
CONFIG += ordered

localoption = $$(OPTION)
equals (localoption, "debug" ){
message(Using $$(OPTION) configuration for MIPModeler Solvers)
SUBDIRS +=\
MIPModelerCore\
#MIPSolverInterface\MIPCbcSolver\
#MIPSolverInterface\MIPClpSolver\
MIPSolverInterface\MIPCpxSolver\
MIPSolverInterface\MIPMskSolver\
}
equals (localoption, "release" ){
message(Using $$(OPTION) configuration for MIPModeler Solvers )
SUBDIRS +=\
MIPModelerCore\
MIPSolverInterface\MIPCbcSolver\
MIPSolverInterface\MIPClpSolver\
MIPSolverInterface\MIPCpxSolver\
MIPSolverInterface\MIPMskSolver\
}



