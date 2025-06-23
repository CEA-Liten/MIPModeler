/**
 * @file  tst_testTransport.cpp
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 11/2022
 * @abstract transportation problem is one of typical LP optimisation problems
  in operation research. In this example, transportation problem is modeled using MIPModeler.
*/


#include "test_MIPModeler.h"
#include "MIPClpSolver.h"


int main()
{
    MIPModeler::MIPModel model;

    MIPModeler::MIPVariable2D transp(mFactory, mClient, 0.0, MIP_INFINITY);
    model.add(transp, "Transp");

    for (int iclient = 0; iclient < mClient; iclient++) {
        MIPModeler::MIPExpression dem;
        for (int ifactory = 0; ifactory < mFactory; ifactory++)
            dem += transp(ifactory, iclient);
        model.add(dem >= mDemand[iclient], "demand_" + std::to_string(iclient));
        dem.close();
    }

    for (int ifactory = 0; ifactory < mFactory; ifactory++) {
        MIPModeler::MIPExpression cap;
        for (int iclient = 0; iclient < mClient; iclient++)
            cap += transp(ifactory, iclient);
        model.add(cap <= mCapacity[ifactory], "capacity_" + std::to_string(ifactory));
        cap.close();
    }

    MIPModeler::MIPExpression obj;
    for (int ifactory = 0; ifactory < mFactory; ifactory++)
        for (int iclient = 0; iclient < mClient; iclient++)
            obj += transp(ifactory, iclient) * mCost[ifactory][iclient];
    model.setObjective(obj, MIPModeler::MIP_MINIMIZE);
    obj.close();

    MIPSolverInterface::MIPClpSolver clpSolver;
    MIPSolverParams vParams;
    MIPSolverResults vResults;
    clpSolver.solve(&model, vParams, vResults);
    return VERIFY(clpSolver.getObjectiveValue(), 153.6750);
}