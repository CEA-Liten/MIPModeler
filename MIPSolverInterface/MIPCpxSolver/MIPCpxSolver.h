/**
 * @file MIPCpxSolver.h
 * @brief Solver interface for Cplex solver
 * @version 2.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 08/2019
*/

#include "MIPCpxSolver_global.h"
#include "cplex.h"
#include "MIPModeler.h"
#include <iostream>

#ifndef MIPCPXSOLVER_H
#define MIPCPXSOLVER_H

namespace MIPSolverInterface {

class MIPCPXSOLVERSHARED_EXPORT MIPCpxSolver {
public:
// --------------------------------------------------------------------------
    MIPCpxSolver(MIPModeler::MIPModel* model);
    ~MIPCpxSolver();
// --------------------------------------------------------------------------
    void solve();
    void writeLp();
// --------------------------------------------------------------------------
    void setSolverPrint(const bool& solverPrint);
    void setTimeLimit(const double& timeLimit);
    void setGap(const double& gap);
    void setThreads(const int& threads);
// --------------------------------------------------------------------------
    const double* getOptimalSolution() const {return mOptimalSolution;}
    double getObjectiveValue() const {return mObjectiveValue;}
    double getLpValue() const {return mLpValue;}
    std::string getOptimisationStatus() const {return mOptimisationStatus;}
// --------------------------------------------------------------------------
private:
    MIPModeler::MIPModel* mModel;

    const double* mOptimalSolution;
    double mObjectiveValue;
    double mLpValue;
    std::string mOptimisationStatus;

    double mTimeLimit;
    double mGap;
    int mThreads;
    bool mLpFile;
    bool mSolverPrint;
};

}
#endif //MIPCPXSOLVER_H
