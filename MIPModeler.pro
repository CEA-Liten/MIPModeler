TEMPLATE = subdirs
CONFIG += ordered

localoption = $$(OPTION)
equals (localoption, "debug" ){
message(Using $$(OPTION) configuration for MIPModeler)
SUBDIRS +=\
GAMSModeler\
MIPModelerCore\
MIPSolverInterface\MIPCbcSolver\
MIPSolverInterface\MIPClpSolver\
MIPSolverInterface\MIPCpxSolver\
MIPSolverInterface\MIPMskSolver\
}

equals (localoption, "release" ){
message(Using $$(OPTION) configuration for MIPModeler)
SUBDIRS +=\
GAMSModeler\
MIPModelerCore\
MIPSolverInterface\MIPCbcSolver\
MIPSolverInterface\MIPClpSolver\
MIPSolverInterface\MIPCpxSolver\
MIPSolverInterface\MIPMskSolver\
}

message("GAMS_HOME                     ": $$(GAMS_HOME))
message("SOLVER_DEPS path to eigen     ": $$(SOLVER_DEPS))
message("COIN_OR                       ": $$(COINOR_HOME))
message("MIPMODELER_HOME               ": $$(MIPMODELER_HOME))
message("MIPCpxSolver using cplex 20.1 ": $$(CPLEX_HOME))
message("MIPMskSolver using mosek 8.1  ": $$(MOSEK_HOME_81)))

