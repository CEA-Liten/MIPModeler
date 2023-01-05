TEMPLATE = subdirs
CONFIG  += ordered

localoption = $$(OPTION)
equals (localoption, "debug" ){
message(Using $$(OPTION) configuration for MIPModeler)
SUBDIRS +=\
#external/CoinOR\
core\
#MIPSolverInterface\MIPCbcSolver\
#MIPSolverInterface\MIPClpSolver\
MIPSolverInterface\MIPCpxSolver\
#MIPSolverInterface\MIPMskSolver\
#test\
}
equals (localoption, "release" ){
message(Using $$(OPTION) configuration for MIPModeler)
SUBDIRS +=\
#external/CoinOR\
core\
#MIPSolverInterface\MIPCbcSolver\
#MIPSolverInterface\MIPClpSolver\
MIPSolverInterface\MIPCpxSolver\
#MIPSolverInterface\MIPMskSolver\
#test\
}
_GAMS_HOME=$$(GAMS_HOME)

!isEmpty(_GAMS_HOME) {
message(Using $$(GAMS_HOME) configuration for GAMSModeler)
SUBDIRS +=\
GAMSModeler\
}
message("GAMS_HOME                     ": $$(GAMS_HOME))
message("MIPMODELER_HOME               ": $$(MIPMODELER_HOME))
message("MIPCpxSolver using cplex      ": $$(CPLEX_HOME))
message("MIPMskSolver using mosek      ": $$(MOSEK_HOME)))

