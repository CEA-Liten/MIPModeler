/**
 * @file MIPClpSolver.h
 * @brief Solver interface for Clp Coin-OR solver
 * @version 2.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 11/2018
*/

#include "MIPClpSolver_global.h"
#include <OsiSolverInterface.hpp>
#include <OsiClpSolverInterface.hpp>
#include "MIPModeler.h"
#include <iostream>

#ifndef MIPCLPSOLVER_H
#define MIPCLPSOLVER_H

namespace MIPSolverInterface {

class MIPCLPSOLVERSHARED_EXPORT MIPClpSolver {
public:
//---------------------------------------------------------------------------
    MIPClpSolver(MIPModeler::MIPModel* model);
    ~MIPClpSolver();
//---------------------------------------------------------------------------
    void solve();
    void writeLp();
//---------------------------------------------------------------------------
    void setSolverPrint(const int& solverPrint);
//---------------------------------------------------------------------------
    const double* getOptimalSolution() const {return mOptimalSolution;}
    double getObjectiveValue() const {return mObjectiveValue;}
    std::string getOptimisationStatus() const {return mOptimisationStatus;}
//---------------------------------------------------------------------------
private:
    MIPModeler::MIPModel* mModel;
    OsiSolverInterface * mSolver;

    const double* mOptimalSolution;
    double mObjectiveValue;
    std::string mOptimisationStatus;
    bool mLpFile;
    int mSolverPrint;
};

}
#endif //MIPCLPSOLVER_H
