# set MIPModeler solvers environement
export extension=

# MIPModeler env
echo -e "\n$YELLOW➡  Setting MIPModeler environnement $RESET"
export MIPMODELER_HOME=${IMPORT_HOME}/MIPModeler
echo -e "$MAGENTA \t☸  MIPModeler directory: $QTDIR $RESET"

# Cplex env
source ${MIPMODELER_HOME}/MIPSolverInterface/MIPCpxSolver/CplexEnv.sh

# Add CPlex and MIPModeler to PATH
export PATH=${MIPMODELER_HOME}/lib/${OPTION}:${PATH}:${CPLEX_HOME_BIN}
echo -e "$GREEN \t✅ CPlex is: ${MIPMODELER_HOME}/lib/${OPTION} $RESET"
echo -e "$GREEN \t✅ MIPModeler is: ${MIPMODELER_HOME}/lib/${OPTION} $RESET"

export PATH=${MIPMODELER_HOME}/external/CoinOR/lib/${OPTION}:${PATH}
export LD_LIBRARY_PATH=${MIPMODELER_HOME}/external/CoinOR/lib/${OPTION}:$LD_LIBRARY_PATH

