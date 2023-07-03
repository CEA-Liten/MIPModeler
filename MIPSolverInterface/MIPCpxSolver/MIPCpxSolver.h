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
#include <QtCore>
#include "IMIPSolver.h"

#ifndef MIPCPXSOLVER_H
#define MIPCPXSOLVER_H

namespace MIPSolverInterface {

class MIPCPXSOLVERSHARED_EXPORT MIPCpxSolver : public QObject, 
                                               public IMIPSolver
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID SolverInInterface_iid)
    Q_INTERFACES(IMIPSolver)

public:
// --------------------------------------------------------------------------
    MIPCpxSolver();
    ~MIPCpxSolver();
// --------------------------------------------------------------------------
    QString Infos();
    int solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results);

    void solve();
    void writeLp();
    void writeMipStart();
// --------------------------------------------------------------------------
    void setSolverPrint(const bool& solverPrint);
    void setTimeLimit(const double& timeLimit);
    void setGap(const double& gap);
    void setThreads(const int& threads);
    void setLocation(const char* location);
    void setFileMipStart(const char* mipStartFile);
    void setMaxNumberOfSolutions(const int& maxNumberOfSolutions);
    void setReadParamFile();
    void setTerminateSignal(int* terminate);
    int* getTerminateSignal();
// --------------------------------------------------------------------------
    const double* getOptimalSolution() const {return mOptimalSolution;}
    int getNbSolutionsGardees(){return mNbSolutionsGardees;}
    std::vector<double*> getOtherSolutions() const {return mOtherSolutions;}
    std::vector<double> getObjectiveOtherSolutions() const {return mObjectiveOtherSolutions;}
    double getObjectiveValue() const {return mObjectiveValue;}
    double getLpValue() const {return mLpValue;}
    std::string getOptimisationStatus() const {return mOptimisationStatus;}
// --------------------------------------------------------------------------
private:
    MIPModeler::MIPModel* mModel;

    const double* mOptimalSolution;
    std::vector<double*> mOtherSolutions;

    double mObjectiveValue;
    int mNbSolutionsGardees;
    std::vector<double> mObjectiveOtherSolutions;
    double mLpValue;
    std::string mOptimisationStatus;
    const char* mFileMipStart;

    double mTimeLimit;
    double mGap;
    int mThreads;
    bool mLpFile;
    bool mSolverPrint;
    bool mWriteMipStart;
    bool mReadParamFile;
    int mMaxNumberOfSolutions;
    int* mTerminate;

    const char* mLocation ;
};

}
#endif //MIPCPXSOLVER_H
