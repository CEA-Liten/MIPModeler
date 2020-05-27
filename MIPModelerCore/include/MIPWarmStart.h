/**
    @file MIPWarmStart.h
    @version 1.0
    @author Yacine Gaoua (yacine.gaoua@cea.fr)
    @date 02/2020
*/

#include "MIPModeler_global.h"
#include "MIPVariable0D.h"
#include <vector>

#ifndef MIPWARMSTART_H
#define MIPWARMSTART_H

namespace MIPModeler {

class MIPVariable0D;

class MIPMODELERSHARED_EXPORT MIPWarmStart {
public:
//-----------------------------------------------------------------------------
    MIPWarmStart();
    virtual ~MIPWarmStart();
//-----------------------------------------------------------------------------
    void add(MIPVariable0D& var, const double& value);
    void close();
//-----------------------------------------------------------------------------
    std::vector<MIPVariable0D*> const& getVariables() const {return mVariables;}
    std::vector<int> const& getVarColIdx() const {return mVarColIdx;}
    std::vector<double> const& getValues() const {return mValues;}
    int getNumElements() const {return mNumElements;}
//-----------------------------------------------------------------------------
private:
    std::vector<MIPVariable0D*> mVariables;
    std::vector<int> mVarColIdx;
    std::vector<double> mValues;
    int mNumElements;
};

}
#endif // MIPWARMSTART_H
