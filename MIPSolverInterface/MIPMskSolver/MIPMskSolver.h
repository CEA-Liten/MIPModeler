/**
 * @file MIPMskSolver.h
 * @brief Solver interface for Mosek solver
 * @version 2.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 08/2019
*/

#include "MIPMskSolver_global.h"
#include "mosek.h"
#include "MIPModeler.h"
#include <iostream>

#ifndef MIPMSKSOLVER_H
#define MIPMSKSOLVER_H

namespace MIPSolverInterface {

class MIPMSKSOLVERSHARED_EXPORT MIPMskSolver {
public:
//----------------------------------------------------------------------------
    MIPMskSolver(MIPModeler::MIPModel* model);
    ~MIPMskSolver();
//----------------------------------------------------------------------------
    void solve();
    void writeLP();
//----------------------------------------------------------------------------
    void setSolverPrint(const int& solverPrint);
    void setTimeLimit(const double& timeLimit);
    void setGap(const double& gap);
    void setThreads(const int& threads);
//----------------------------------------------------------------------------
    const double* getOptimalSolution() { return mOptimalSolution; }
    double getObjectiveValue() { return mObjectiveValue; }
    std::string getOptimisationStatus() { return mOptimisationStatus; }
private:
//----------------------------------------------------------------------------
    bool definedSolution(MSKtask_t& task , int solType);
//----------------------------------------------------------------------------
private:
    MIPModeler::MIPModel* mModel;

    const double* mOptimalSolution;
    double mObjectiveValue;
    std::string mOptimisationStatus;

    double mTimeLimit;
    double mGap;
    int mThreads;
    bool mLpFile;
    int mSolverPrint;
};

}
#endif //MIPMSKSOLVER_H
