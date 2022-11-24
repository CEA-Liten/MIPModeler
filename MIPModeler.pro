TEMPLATE = subdirs
CONFIG  += ordered

localoption = $$(OPTION)
equals (localoption, "debug" ){
message(Using $$(OPTION) configuration for MIPModeler)
SUBDIRS +=\
External/CoinOR\
GAMSModeler\
MIPModelerCore\
MIPSolverInterface\MIPCbcSolver\
MIPSolverInterface\MIPClpSolver\
MIPSolverInterface\MIPCpxSolver\
MIPSolverInterface\MIPMskSolver\
test\
}
equals (localoption, "release" ){
message(Using $$(OPTION) configuration for MIPModeler)
SUBDIRS +=\
External/CoinOR\
GAMSModeler\
MIPModelerCore\
MIPSolverInterface\MIPCbcSolver\
MIPSolverInterface\MIPClpSolver\
MIPSolverInterface\MIPCpxSolver\
MIPSolverInterface\MIPMskSolver\
test\
}

message("GAMS_HOME                     ": $$(GAMS_HOME))
message("MIPMODELER_HOME               ": $$(MIPMODELER_HOME))
message("MIPCpxSolver using cplex      ": $$(CPLEX_HOME))
message("MIPMskSolver using mosek      ": $$(MOSEK_HOME)))

