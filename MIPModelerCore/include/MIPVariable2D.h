/**
 * @file MIPVariable2D.h
 * @brief 2D optimisation variable.
 * MIPVariable2D is defined by
 * 2D dimensions (rows, cols),
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

#ifndef MIPVARIABLE2D_H
#define MIPVARIABLE2D_H

namespace MIPModeler {

class MIPVariable0D;

class MIPMODELERSHARED_EXPORT MIPVariable2D {
public:
//-----------------------------------------------------------------------------
    MIPVariable2D() = default;
    MIPVariable2D(const int& rows, const int& cols,
                  const double& lowerBound = -MIP_INFINITY, const double& upperBound = MIP_INFINITY,
                  const MIPVarType& varType = MIP_FLOAT);
    virtual ~MIPVariable2D();
//-----------------------------------------------------------------------------
    MIPVariable0D& operator()(const int& row, const int& col) const;
    MIPVariable2D& operator=(const MIPVariable2D& variable2D);
//-----------------------------------------------------------------------------
    void setColIdx(int& idx);
    void setName(const std::string& name);
//-----------------------------------------------------------------------------
    bool isInteger() const {return bool(mType);}
//-----------------------------------------------------------------------------
    int getColIdx(const int& row, const int& col) const;
    double getUpperBound() const {return mUpperBound;}
    double getLowerBound() const {return mLowerBound;}
    int getNumDims() const {return mNumDims;}
    int* getDims() {return mDims;}
    std::vector<MIPVariable0D*> const& getVariables() const {return mVariables;}
//-----------------------------------------------------------------------------
private:
    const int mNumDims = 2;
    int* mDims;
    double mLowerBound;
    double mUpperBound;
    MIPVarType mType;
    std::vector<MIPVariable0D*> mVariables;
};

}
#endif /* MIPVariable2D */
