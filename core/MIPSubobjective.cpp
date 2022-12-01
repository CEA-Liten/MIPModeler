#include "MIPSubobjective.h"


namespace MIPModeler {

MIPSubobjective::MIPSubobjective(std::string& objName)
    :mSubObjectiveExpression(MIPExpression()),
      mAbsTol(0),
      mRelTol(0),
      mRank(0),
      mObjectiveDirection(1)
{
    mNameSubObj = objName;
}
void MIPSubobjective::setSubObjective(MIPExpression& objective,
                     int objectiveDirection,
                     int rankObjective, double& abstol,
                     double& reltol ){
    mSubObjectiveExpression = objective;
    mObjectiveDirection = objectiveDirection;
    mRank = rankObjective;
    mAbsTol = abstol;
    mRelTol = reltol;
}

MIPSubobjective::~MIPSubobjective(){

}
}
