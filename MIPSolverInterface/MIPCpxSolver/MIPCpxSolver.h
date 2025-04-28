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
#include <fstream>
#include "IMIPSolver.h"

#ifndef MIPCPXSOLVER_H
#define MIPCPXSOLVER_H

namespace MIPSolverInterface {

class MIPCPXSOLVERSHARED_EXPORT MIPCpxSolver :  public IMIPSolver
{        
public:
// --------------------------------------------------------------------------
    MIPCpxSolver();
    ~MIPCpxSolver();
// --------------------------------------------------------------------------
    QString Infos();
    int solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results);

    int solve();
    void writeLp();
    void writeLpCycle(const int cycel);
    void writeMipStart();
// --------------------------------------------------------------------------
    void setSolverPrint(const bool& solverPrint);
    void setTimeLimit(const double& timeLimit);
    void setGap(const double& gap);
    void setThreads(const int& threads);
    void setTreeMemoryLimit(const int& a_TreeMemoryLimit);
    void setLocation(const std::string &location);
    void setFileMipStart(const std::string &mipStartFile);
    void setMaxNumberOfSolutions(const int& maxNumberOfSolutions);
    void setReadParamFile();
    void setTerminateSignal(int* terminate);
    int* getTerminateSignal();
// --------------------------------------------------------------------------
    const double* getOptimalSolution() const {return mOptimalSolution.data(); }
    int getNbSolutionsGardees(){return mNbSolutionsGardees;}
    std::vector<double> getObjectiveOtherSolutions() const {return mObjectiveOtherSolutions;}
    double getObjectiveValue() const {return mObjectiveValue;}
    double getLpValue() const {return mLpValue;}
    std::string getOptimisationStatus() const {return mOptimisationStatus;}
// ------------------- Used for GUI debug interface -------------------------
    void setCheckConflicts(const bool checkConflicts);
// --------------------------------------------------------------------------
private:
    MIPModeler::MIPModel* mModel;

    std::vector<double> mOptimalSolution;
    std::vector<std::vector<double>> mOtherSolutions;

    double mObjectiveValue{ 0 };
    int mNbSolutionsGardees{ 0 };
    std::vector<double> mObjectiveOtherSolutions;
    double mLpValue {0};
    std::string mOptimisationStatus;
    std::string mFileMipStart;

    double mTimeLimit;
    double mGap;
    int mThreads;
    int mTreeMemoryLimit;
    bool mLpFile;
    int mLpFileCycle;
    bool mSolverPrint;
    bool mWriteMipStart;
    bool mReadParamFile;
    int mMaxNumberOfSolutions{ 1 };
    int* mTerminate;

    std::string mLocation ;
    
    std::fstream *mlogFile {nullptr};
    enum logLevel
    {
        INFO = 0,
        ERR = 1
    };

    void log(logLevel level, const std::string msg);
    void log(logLevel level, const std::string msg, double value);
    // ------------------- Used for GUI debug interface -------------------------
    void conflict(CPXENVptr env, CPXLPptr lp);
    bool mCheckConflicts;
    // --------------------------------------------------------------------------
};

}
#endif //MIPCPXSOLVER_H