/**
 * @file MIPCbcSolver.h
 * @brief Solver interface for Cbc Coin-OR solver
 * @version 2.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 11/2018
*/

#include "MIPCbcSolver_global.h"
#include <OsiSolverInterface.hpp>
#include <OsiClpSolverInterface.hpp>
#include <CbcModel.hpp>
#include <CbcSolver.hpp>
#include <CbcSOS.hpp>
#include "MIPModeler.h"
#include <iostream>

#ifndef MIPCBCSOLVER_H
#define MIPCBCSOLVER_H

namespace MIPSolverInterface {

class MIPCBCSOLVERSHARED_EXPORT MIPCbcSolver {
public:
//---------------------------------------------------------------------------
    MIPCbcSolver(MIPModeler::MIPModel* model);
    ~MIPCbcSolver();
//---------------------------------------------------------------------------
    void solve();
    void writeLp();
//---------------------------------------------------------------------------
    void setSolverPrint(const int& solverPrint);
    void setTimeLimit(const double& timeLimit);
    void setGap(const double& gap);
    void setThreads(const int& threads);
//---------------------------------------------------------------------------
    const double* getOptimalSolution() const {return mOptimalSolution;}
    double getObjectiveValue() const {return mObjectiveValue;}
    double getLpValue() const {return mLpValue;}
    std::string getOptimisationStatus() const {return mOptimisationStatus;}
//---------------------------------------------------------------------------
private:
    MIPModeler::MIPModel* mModel;
    OsiSolverInterface* mSolver;
    CbcModel* mCbcModel;

    const double* mOptimalSolution;
    double mObjectiveValue;
    double mLpValue;
    std::string mOptimisationStatus;

    double mTimeLimit;
    double mGap;
    int mThreads;
    bool mLpFile;
    int mSolverPrint;
};

}
#endif //MIPCBCSOLVER_H
