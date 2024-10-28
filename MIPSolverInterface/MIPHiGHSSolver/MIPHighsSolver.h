/**
 * @file MIPCpxSolver.h
 * @brief Solver interface for Cplex solver
 * @version 2.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 08/2019
*/

#include "MIPHighsSolver_global.h"
#include "Highs.h"
#include "MIPModeler.h"
#include <iostream>
#include <QtCore>
#include "IMIPSolver.h"

#ifndef MIPHIGHSSOLVER_H
#define MIPHIGHSSOLVER_H

namespace MIPSolverInterface {

class MIPHIGHSSOLVERSHARED_EXPORT MIPHighsSolver : public QObject,
    public IMIPSolver 
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID SolverInInterface_iid)
    Q_INTERFACES(IMIPSolver)
public:
// --------------------------------------------------------------------------
    MIPHighsSolver();
    ~MIPHighsSolver();
// --------------------------------------------------------------------------
    QString Infos();
    int solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results);

    int solve();
    void writeLp();
// --------------------------------------------------------------------------
    void setSolverPrint(const bool& solverPrint);
    void setTimeLimit(const double& timeLimit);
    void setGap(const double& gap);
    void setThreads(const int& threads);
// --------------------------------------------------------------------------
    const double* getOptimalSolution() const {return mOptimalSolution.data();}
    double getObjectiveValue() const {return mObjectiveValue;}
    std::string getOptimisationStatus() const {return mOptimisationStatus;}
// --------------------------------------------------------------------------
private:
    MIPModeler::MIPModel* mModel;

    std::vector<double> mOptimalSolution;    
    
    double mObjectiveValue{ 0 };
    std::string mOptimisationStatus;

    double mTimeLimit;
    double mGap;
    int mThreads;
    bool mLpFile;
    bool mSolverPrint;

};

}
#endif //MIPHIGHSSOLVER_H
