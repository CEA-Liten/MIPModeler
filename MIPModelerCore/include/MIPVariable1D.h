/**
 * @file MIPVariable1D.h
 * @brief 1D optimisation variable.
 * MIPVariable1D is defined by
 * 1D dimension (cols),
 * lower bound (by defaut -MIP_INFINITY),
 * its upper bound (by defaut MIP_INFINITY)
 * and its type which can be MIP_FLOAT or MIP_INT (by defaut MIP_FLOAT) definition
 * @version 1.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 10/2018
*/

#include "MIPModeler_global.h"
#include "MIPVariable0D.h"
#include <vector>

#ifndef MIPVARIABLE1D_H
#define MIPVARIABLE1D_H

namespace MIPModeler {

class MIPVariable0D;

class  MIPMODELERSHARED_EXPORT MIPVariable1D {
public:
//-----------------------------------------------------------------------------
    MIPVariable1D() = default;
    MIPVariable1D(const int& cols,
                  const double& lowerBound = -MIP_INFINITY, const double& upperBound = MIP_INFINITY,
                  const MIPVarType& varType = MIP_FLOAT);
    virtual ~MIPVariable1D();
//-----------------------------------------------------------------------------
    MIPVariable0D& operator()(int const& col) const;
    MIPVariable1D& operator=(const MIPVariable1D& variable1D);
//-----------------------------------------------------------------------------
    bool isInteger() const {return bool(mType);}
//-----------------------------------------------------------------------------
    void setColIdx(int& idx);
    void setName(const std::string& name);
//-----------------------------------------------------------------------------
    int getColIdx(const int& col) const;
    double getUpperBound() const {return mUpperBound;}
    double getLowerBound() const {return mLowerBound;}
    int getNumDims() const {return mNumDims;}
    int getDims() const {return mDims;}
    std::vector<MIPVariable0D*> const& getVariables() const {return mVariables;}
//-----------------------------------------------------------------------------
private:
    const int mNumDims = 1;
    int mDims;
    double mLowerBound;
    double mUpperBound;
    MIPVarType mType;
    std::vector<MIPVariable0D*> mVariables;
};

}
#endif /* MIPVariable1D */
