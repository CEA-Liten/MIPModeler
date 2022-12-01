/**
    @file MIPVariable0D.cpp
    @version 1.0
    @author Yacine Gaoua (yacine.gaoua@fr)
    @date 10/2018
*/


#include "MIPVariable0D.h"

namespace MIPModeler {

//-----------------------------------------------------------------------------
MIPVariable0D::MIPVariable0D()
    : mIdxCol(-1),
      mLowerBound(-MIP_INFINITY),
      mUpperBound(MIP_INFINITY),
      mType(MIP_FLOAT),
      mName("")
{

}
//-----------------------------------------------------------------------------
MIPVariable0D::MIPVariable0D(const double& lowerBound, const double& upperBound,
                             const MIPVarType& varType)
    : mIdxCol(-1),
      mLowerBound(lowerBound),
      mUpperBound(upperBound),
      mType(varType),
      mName("")
{

}
//-----------------------------------------------------------------------------
void MIPVariable0D::setColIdx(int& idx) {
    mIdxCol = idx;
    idx++;
}
//-----------------------------------------------------------------------------
void MIPVariable0D::setName(const std::string& name){
    mName = name;
}
//-----------------------------------------------------------------------------
MIPVariable0D& MIPVariable0D::operator=(const MIPVariable0D& variable0D){
    mLowerBound = variable0D.mLowerBound,
    mUpperBound = variable0D.mUpperBound,
    mType = variable0D.mType,
    mIdxCol = variable0D.mIdxCol;
    return *this;
}
//-----------------------------------------------------------------------------
void MIPVariable0D::fix(const double& value ){
    mLowerBound = value;
    mUpperBound = value;
    mType = MIP_FLOAT;
}
//-----------------------------------------------------------------------------
void MIPVariable0D::lower(const double& value ){
    mLowerBound = value;
}
//-----------------------------------------------------------------------------
void MIPVariable0D::upper(const double& value ){
    mUpperBound = value;
}
//-----------------------------------------------------------------------------
const double MIPVariable0D::extractValue(const double* solution) const {
    return solution[mIdxCol];
}
//-----------------------------------------------------------------------------
MIPVariable0D::~MIPVariable0D(){

}
//-----------------------------------------------------------------------------
}
