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
#include "IMIPSolver.h"
#include <iostream>

#ifndef MIPCBCSOLVER_H
#define MIPCBCSOLVER_H

namespace MIPSolverInterface {

class MIPCBCSOLVERSHARED_EXPORT MIPCbcSolver : public QObject,
    public IMIPSolver
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID SolverInInterface_iid)
    Q_INTERFACES(IMIPSolver)

public:
//---------------------------------------------------------------------------
    MIPCbcSolver();
    ~MIPCbcSolver();
//---------------------------------------------------------------------------
    QString Infos();
    int solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results);

    int solve();
    void writeLp();
    void writeLpCycle(const int aStep);
//---------------------------------------------------------------------------
    void setSolverPrint(const int& solverPrint);
    void setTimeLimit(const double& timeLimit);
    void setGap(const double& gap);
    void setThreads(const int& threads);
//---------------------------------------------------------------------------
    const double* getOptimalSolution() const {return mOptimalSolution.data();}
    double getObjectiveValue() const {return mObjectiveValue;}
    double getLpValue() const {return mLpValue;}
    std::string getOptimisationStatus() const {return mOptimisationStatus;}
//---------------------------------------------------------------------------
private:
    MIPModeler::MIPModel* mModel;

    void setOptimalSolution(int numCols, const CbcModel &aCbcModel);
    std::vector<double> mOptimalSolution;
    double mObjectiveValue{ 0.0 };
    double mLpValue{ 0.0 };
    std::string mOptimisationStatus;

    double mTimeLimit;
    double mGap;
    int mThreads;
    bool mLpFile;
    int mLpFileCycle;
    int mSolverPrint;
};

}
#endif //MIPCBCSOLVER_H
