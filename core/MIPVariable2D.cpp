/**
    @file MIPVariable2D.cpp
    @version 1.0
    @author Yacine Gaoua (yacine.gaoua@cea.fr)
    @date 10/2018
*/

#include "MIPVariable2D.h"

namespace MIPModeler {
// --------------------------------------------------------------------------
MIPVariable2D::MIPVariable2D(const int& rows, const int& cols,
                             const double& lowerBound, const double& upperBound,
                             const MIPVarType& varType)
    : mLowerBound(lowerBound),
      mUpperBound(upperBound),
      mType(varType)
{
    int vSize = rows * cols;
    mDims = new int[mNumDims]{rows, cols};
    mVariables = std::vector<MIPVariable0D*>(vSize, nullptr);
    for(int i = 0 ; i < vSize ; i++)
        mVariables[i] = new MIPVariable0D(mLowerBound, mUpperBound, mType);
}
// --------------------------------------------------------------------------
void MIPVariable2D::setColIdx(int& idx) {
    std::vector<MIPVariable0D*>::iterator it = mVariables.begin();
    for (; it != mVariables.end(); it++)
        (*it)->setColIdx(idx);
}
//-----------------------------------------------------------------------------
void MIPVariable2D::setName(const std::string& name){
    std::string label;
    int idx;
    for(int row = 0; row < mDims[0]; row++){
        for(int col = 0; col < mDims[1]; col++){
            idx = row * mDims[1] + col;
            label = name + "(" + std::to_string(row) + "," + std::to_string(col) + ")";
            mVariables[idx]->setName(label);
        }
    }
}
// --------------------------------------------------------------------------
int MIPVariable2D::getColIdx(const int& row, const int& col) const {
    return mVariables[row * mDims[1] + col]->getColIdx();
}
// --------------------------------------------------------------------------
MIPVariable0D& MIPVariable2D::operator()(int const& row, int const& col) const{
    return *(mVariables[row * mDims[1] + col]);
}
//---------------------------------------------------------------------------
MIPVariable2D& MIPVariable2D::operator=(const MIPVariable2D& variable2D){
    mLowerBound = variable2D.mLowerBound,
    mUpperBound = variable2D.mUpperBound,
    mType = variable2D.mType,
    mVariables = variable2D.mVariables;
    mDims = variable2D.mDims;
    return *this;
}
// --------------------------------------------------------------------------
MIPVariable2D::~MIPVariable2D(){

}
// --------------------------------------------------------------------------
}
