/**
    @file MIPExpression.h
    @version 1.0
    @author Pimprenelle Parmentier (pimprenelle.parmentier@cea.fr)
    @date 08/2022
*/


#include "MIPModeler_global.h"
#include "MIPExpression.h"
#include <vector>

#ifndef MIPSUBOBJECTIVE_H
#define MIPSUBOBJECTIVE_H



namespace MIPModeler {

class MIPMODELERSHARED_EXPORT MIPSubobjective {
public:
//-----------------------------------------------------------------------------
    MIPSubobjective(std::string& objName);
    virtual ~MIPSubobjective();
//-----------------------------------------------------------------------------
    void setSubObjective(MIPExpression& objective,
                         int objectiveDirection,
                         int rankObjective, double& abstol,
                         double& reltol);
    MIPExpression const getSubObjectiveExpression(){return mSubObjectiveExpression;};
    int getObjectiveDirection() const {return mObjectiveDirection;}
    double getAbsTol() const {return mAbsTol;}
    double getRelTol() const {return mRelTol;}
    int getRank() const {return mRank;}
    std::string const getName() const {return mNameSubObj;}
private:
    MIPExpression mSubObjectiveExpression;
    std::string mNameSubObj;
    int mObjectiveDirection;
    double mAbsTol;
    double mRelTol;
    int mRank;
};
}
#endif // MIPSUBOBJECTIVE_H



