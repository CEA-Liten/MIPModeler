/**
    @file MIPWarmStart.cpp
    @version 1.0
    @author Yacine Gaoua (yacine.gaoua@cea.fr)
    @date 02/2020
*/

#include "MIPWarmStart.h"

namespace MIPModeler {
//-----------------------------------------------------------------------------
MIPWarmStart::MIPWarmStart()
    : mNumElements(0)
{

}
//-----------------------------------------------------------------------------
void MIPWarmStart::add(MIPVariable0D& var, const double& value) {
    mVariables.push_back(&var);
    mVarColIdx.push_back(var.getColIdx());
    mValues.push_back(value);
    mNumElements++;
}
//-----------------------------------------------------------------------------
void MIPWarmStart::close() {
    mVariables.clear();
    mVarColIdx.clear();
    mValues.clear();
    mNumElements = 0;
}
//-----------------------------------------------------------------------------
MIPWarmStart::~MIPWarmStart() {

}
//-----------------------------------------------------------------------------
}
