/**
    @file MIPVariable1D.cpp
    @version 1.0
    @author Yacine Gaoua (yacine.gaoua@cea.fr)
    @date 10/2018
*/

#include "MIPVariable1D.h"

namespace MIPModeler {
//-----------------------------------------------------------------------------
MIPVariable1D::MIPVariable1D(const int& cols,
                             const double& lowerBound, const double& upperBound,
                             const MIPVarType& varType)
    : mDims(cols),
      mLowerBound(lowerBound),
      mUpperBound(upperBound),
      mType(varType)
{
    mVariables = std::vector<MIPVariable0D*>(cols, nullptr);
    for(int i=0; i<cols; i++)
        mVariables[i] = new MIPVariable0D(mLowerBound, mUpperBound, mType);
}
//-----------------------------------------------------------------------------
void MIPVariable1D::setColIdx(int& idx) {
    std::vector<MIPVariable0D*>::iterator it = mVariables.begin();
    for (; it != mVariables.end(); it++)
        (*it)->setColIdx(idx);
}
//-----------------------------------------------------------------------------
void MIPVariable1D::setName(const std::string& name){
    std::string label;
    for(int col = 0; col < mDims; col++){
        label = name + "(" + std::to_string(col) + ")";
        mVariables[col]->setName(label);
    }
}
//-----------------------------------------------------------------------------
int MIPVariable1D::getColIdx(const int& col) const {
    return mVariables[col]->getColIdx();
}
//-----------------------------------------------------------------------------
MIPVariable0D& MIPVariable1D::operator()(const int& col) const {
    return *(mVariables[col]);
}
//-----------------------------------------------------------------------------
MIPVariable1D& MIPVariable1D::operator=(const MIPVariable1D& variable1D){
    mLowerBound = variable1D.mLowerBound,
    mUpperBound = variable1D.mUpperBound,
    mType = variable1D.mType,
    mVariables = variable1D.mVariables;
    mDims = variable1D.mDims;
    return *this;
}
//-----------------------------------------------------------------------------
MIPVariable1D::~MIPVariable1D(){

}
// --------------------------------------------------------------------------
}

