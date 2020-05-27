/**
 * @file MIPSpecialOrderedSet.h
 * @brief MIP SOS variable definition
 * @version 1.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 07/2018
*/

#include "MIPModeler_global.h"
#include "MIPVariable0D.h"
#include <vector>

#ifndef MIPSPECIALORDEREDSET_H
#define MIPSPECIALORDEREDSET_H

namespace MIPModeler {

class MIPVariable0D;

class MIPMODELERSHARED_EXPORT MIPSpecialOrderedSet {
public:
//-----------------------------------------------------------------------------
    MIPSpecialOrderedSet();
    virtual ~MIPSpecialOrderedSet();
//-----------------------------------------------------------------------------
    const MIPVariable0D& operator()(const int& col) const;
//-----------------------------------------------------------------------------
    void add(MIPVariable0D& var);
    void close();
//-----------------------------------------------------------------------------
    std::vector<MIPVariable0D*> const& getVariables() const {return mVariables;}
    std::vector<int> const& getVarColIdx() const {return mVarColIdx;}
    std::vector<double> const& getWeights() const {return mWeights;}
    int getNumElements() const {return mNumElements;}
//-----------------------------------------------------------------------------
private:
    std::vector<MIPVariable0D*> mVariables;
    std::vector<int> mVarColIdx;
    std::vector<double> mWeights;
    int mNumElements;
};

}
#endif // MIPSPECIALORDEREDSET_H
