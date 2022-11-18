/**
    @file MIPSpecialOrderedSet.cpp
    @version 1.0
    @author Yacine Gaoua (yacine.gaoua@cea.fr)
    @date 07/2018
*/

#include "MIPSpecialOrderedSet.h"

namespace MIPModeler {
//-----------------------------------------------------------------------------
MIPSpecialOrderedSet::MIPSpecialOrderedSet()
    : mNumElements(0)
{

}
//-----------------------------------------------------------------------------
const MIPVariable0D& MIPSpecialOrderedSet::operator ()(const int& col) const {
    return *(mVariables[col]);
}
//-----------------------------------------------------------------------------
void MIPSpecialOrderedSet::add(MIPVariable0D& var) {
    mVariables.push_back(&var);
    mVarColIdx.push_back(var.getColIdx());
    mWeights.push_back(mNumElements);
    mNumElements++;
}
//-----------------------------------------------------------------------------
void MIPSpecialOrderedSet::close() {
    mVariables.clear();
    mVarColIdx.clear();
    mWeights.clear();
    mNumElements = 0;
}
//-----------------------------------------------------------------------------
MIPSpecialOrderedSet::~MIPSpecialOrderedSet() {

}
//-----------------------------------------------------------------------------
}
