#!/bin/bash
export TRILOGY_ROOT=/volatile/Trilogy
export FBSF_HOME=${TRILOGY_ROOT}/fbsfOpenSource
if [ -f ${FBSF_HOME}/lib/release/FbsfFramework ]
then
  export FBSF_BUILD_MODE=release
elif [ -f ${FBSF_HOME}/lib/debug/FbsfFramework ]
then
  export FBSF_BUILD_MODE=debug
else
  echo "Fbsf not found!"
  exit
fi
echo "mode "${FBSF_BUILD_MODE}
source ${FBSF_HOME}/QtVersion.sh
export CPLEX_HOME=${TRILOGY_ROOT}/cplex/cplex
export MIPMODELER_INSTALL=${TRILOGY_ROOT}/MIPModeler_install
export MIPMODELER_HOME=${TRILOGY_ROOT}/MIPModeler
