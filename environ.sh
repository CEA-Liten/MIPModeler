#!/bin/bash
export TRILOGY_ROOT=/volatile/Trilogy
export FBSF_HOME=${TRILOGY_ROOT}/fbsfOpenSource
if [ -d ${FBSF_HOME}/lib/release ] 
then
  export FBSF_BUILD_MODE=release
elif [ -d ${FBSF_HOME}/lib/debug ] 
then
  export FBSF_BUILD_MODE=debug
else
  echo "Fbsf libraries not found!"
  exit
fi
source ${FBSF_HOME}/QtVersion.sh
export PERSEE_HOME=${TRILOGY_ROOT}/Persee
export CPLEX_HOME=${TRILOGY_ROOT}/cplex/cplex
export MIPMODELER_INSTALL=${TRILOGY_ROOT}/MIPModeler_install
export MIPMODELER_HOME=${TRILOGY_ROOT}/MIPModeler
