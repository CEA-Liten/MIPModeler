/**
 * @file MIPVariable3D.h
 * @brief MIP 3D optimisation variable.
 * MIPVariable3D is defined by
 * 3D dimensions (rows, cols, depths),
 * lower bound (by defaut -MIP_INFINITY),
 * its upper bound (by defaut MIP_INFINITY)
 * and its type which can be MIP_FLOAT or MIP_INT (by defaut MIP_FLOAT) definition
 * @version 1.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 12/2019
*/

#include "MIPModeler_global.h"
#include "MIPVariable0D.h"
#include <vector>

#ifndef MIPVARIABLE3D_H
#define MIPVARIABLE3D_H

namespace MIPModeler {

class MIPVariable0D;

class MIPMODELERSHARED_EXPORT MIPVariable3D {
public:
//-----------------------------------------------------------------------------
    MIPVariable3D() = default;
    MIPVariable3D(const int& rows, const int& cols, const int& depths,
                  const double& lowerBound = -MIP_INFINITY, const double& upperBound = MIP_INFINITY,
                  const MIPVarType& varType = MIP_FLOAT);
    virtual ~MIPVariable3D();
//-----------------------------------------------------------------------------
    MIPVariable0D& operator()(const int& row, const int& col, const int& depth) const;
    MIPVariable3D& operator=(const MIPVariable3D& variable3D);
//-----------------------------------------------------------------------------
    void setColIdx(int& idx);
    void setName(const std::string& name);
//-----------------------------------------------------------------------------
    bool isInteger() const {return bool(mType);}
//-----------------------------------------------------------------------------
    int getColIdx(const int& row, const int& col, const int& depth) const;
    double getUpperBound() const {return mUpperBound;}
    double getLowerBound() const {return mLowerBound;}
    int getNumDims() const {return mNumDims;}
    int* getDims() const {return mDims;}
    std::vector<MIPVariable0D*> const& getVariables() const {return mVariables;}
//-----------------------------------------------------------------------------
private:
    const int mNumDims = 3;
    int* mDims;
    double mLowerBound;
    double mUpperBound;
    MIPVarType mType;
    std::vector<MIPVariable0D*> mVariables;
};

}
#endif /* MIPVariable3D */
