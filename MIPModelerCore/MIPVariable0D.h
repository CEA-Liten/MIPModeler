/**
 * @file MIPVariable0D.h
 * @brief 0D optimisation variable.
 * MIPVariable0D is defined by
 * lower bound (by defaut -MIP_INFINITY),
 * upper bound (by defaut MIP_INFINITY)
 * and type which can be MIP_FLOAT or MIP_INT (by defaut MIP_FLOAT)
 * @version 1.0
 * @author Yacine Gaoua (yacine.gaoua@fr)
 * @date 10/2018
*/

#include "MIPModeler_global.h"
#include <string>
#include <limits>

#ifndef MIPVARIABLE0D_H
#define MIPVARIABLE0D_H

namespace MIPModeler {

#ifndef MIP_INFINITY
#define MIP_INFINITY 1e+20
#endif

#ifndef MIPVARTYPE
#define MIPVARTYPE
enum MIPVarType {MIP_FLOAT = false, MIP_INT = true};
#endif

class  MIPMODELERSHARED_EXPORT MIPVariable0D {
public:
//-----------------------------------------------------------------------------
    MIPVariable0D();
    MIPVariable0D(const double& lowerBound, const double& upperBound,
                  const MIPVarType& varType = MIP_FLOAT);
    virtual ~MIPVariable0D();    
//-----------------------------------------------------------------------------
    MIPVariable0D& operator=(const MIPVariable0D& variable0D);
//-----------------------------------------------------------------------------
    void setColIdx(int& idx);
    void setName(const std::string& name);
//-----------------------------------------------------------------------------
    int getColIdx() const {return mIdxCol;}
    double getUpperBound() const {return mUpperBound;}
    double getLowerBound() const {return mLowerBound;}
    bool isInteger() const {return bool(mType);}
    std::string getName() const {return mName;}
//-----------------------------------------------------------------------------
    void fix(const double& value );
    void lower(const double& value );
    void upper(const double& value );
//-----------------------------------------------------------------------------
    const double extractValue(const double* solution) const;
//-----------------------------------------------------------------------------
private:
    int mIdxCol;
    double mLowerBound;
    double mUpperBound;
    MIPVarType mType;
    std::string mName;
};

}

#endif /* MIPVariable0D */
