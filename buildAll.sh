#!/bin/bash
source environ.sh
#
if [ ! -d ${TRILOGY_ROOT}/MIPModeler_build ];then
  mkdir ${TRILOGY_ROOT}/MIPModeler_build
fi
cd ${TRILOGY_ROOT}/MIPModeler_build
if [ $? = 0 ]
then
  pwd
  rm -rf *
  # build and install MIPModeler
  if [ ${FBSF_BUILD_MODE} == release ]
  then
    cmake ${MIPMODELER_HOME} -DCMAKE_INSTALL_PREFIX=${MIPMODELER_INSTALL} -DCMAKE_BUILD_TYPE=Release
  elif [ ${FBSF_BUILD_MODE} == debug ]
  then
    cmake ${MIPMODELER_HOME} -DCMAKE_INSTALL_PREFIX=${MIPMODELER_INSTALL} -DCMAKE_BUILD_TYPE=Debug
  fi
  if [ $? != 0 ]; then exit; fi
  make install
  if [ $? != 0 ]; then exit; fi
  echo "MIPModeler installation completed!"
fi
