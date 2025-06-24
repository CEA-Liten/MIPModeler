/**
    @file MIPVariable3D.cpp
    @version 1.0
    @author Yacine Gaoua (yacine.gaoua@cea.fr)
    @date 12/2019
*/

#include "MIPVariable3D.h"

namespace MIPModeler {
// --------------------------------------------------------------------------
MIPVariable3D::MIPVariable3D(const int& rows, const int& cols, const int& depths,
                             const double& lowerBound, const double& upperBound,
                             const MIPVarType& varType)
    : mLowerBound(lowerBound),
      mUpperBound(upperBound),
      mType(varType)
{
    int vSize = rows * cols * depths;
    mDims = new int[mNumDims]{rows, cols, depths};
    mVariables = std::vector<MIPVariable0D*>(vSize, nullptr);
    for(int i=0; i<vSize; i++)
        mVariables[i] = new MIPVariable0D(mLowerBound, mUpperBound, mType);
}
// --------------------------------------------------------------------------
void MIPVariable3D::setColIdx(int& idx) {
    std::vector<MIPVariable0D*>::iterator it = mVariables.begin();
    for (; it != mVariables.end(); it++)
        (*it)->setColIdx(idx);
}
// --------------------------------------------------------------------------
void MIPVariable3D::setName(const std::string& name){
    std::string label;
    int idx;
    for(int row = 0; row < mDims[0]; row++){
        for(int col = 0; col < mDims[1]; col++){
            for(int depth = 0; depth < mDims[2]; depth++){
                idx = (row * mDims[1] * mDims[2]) + (col * mDims[2]) + depth;
                label =  name + "(" + std::to_string(row) + ","
                                    + std::to_string(col) + ","
                                    + std::to_string(depth) + ")";
                mVariables[idx]->setName(label);
            }
        }
    }
}
// --------------------------------------------------------------------------
int MIPVariable3D::getColIdx(const int& row, const int& col, const int& depth) const {
     return mVariables[(row * mDims[1] * mDims[2]) + (col * mDims[2]) + depth]->getColIdx();
}
// --------------------------------------------------------------------------
MIPVariable0D& MIPVariable3D::operator()(const int& row, const int& col, const int& depth) const{
    return *(mVariables[(row * mDims[1] * mDims[2]) + (col * mDims[2]) + depth]);
}
//---------------------------------------------------------------------------
MIPVariable3D& MIPVariable3D::operator=(const MIPVariable3D& variable3D){
    mLowerBound = variable3D.mLowerBound,
    mUpperBound = variable3D.mUpperBound,
    mType = variable3D.mType,
    mVariables = variable3D.mVariables;
    mDims = variable3D.mDims;
    return *this;
}
// --------------------------------------------------------------------------
MIPVariable3D::~MIPVariable3D(){

}
// --------------------------------------------------------------------------
}
