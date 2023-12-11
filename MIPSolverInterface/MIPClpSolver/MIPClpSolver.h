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
#include "IMIPSolver.h"
#include <iostream>

#ifndef MIPCLPSOLVER_H
#define MIPCLPSOLVER_H

namespace MIPSolverInterface {

class MIPCLPSOLVERSHARED_EXPORT MIPClpSolver : public QObject,
    public IMIPSolver
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID SolverInInterface_iid)
    Q_INTERFACES(IMIPSolver)

public:
//---------------------------------------------------------------------------
    MIPClpSolver();
    ~MIPClpSolver();
//---------------------------------------------------------------------------
    QString Infos();
    int solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results);

    int solve();
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

    const double* mOptimalSolution{ nullptr };
    double mObjectiveValue{ 0.0 };
    std::string mOptimisationStatus;
    bool mLpFile;
    int mSolverPrint;
};

}
#endif //MIPCLPSOLVER_H
