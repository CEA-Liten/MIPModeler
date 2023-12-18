/**
 * @file MIPClpSolver.cpp
 * @version 2.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 11/2018
*/

#include "MIPClpSolver.h"

namespace MIPSolverInterface {
// --------------------------------------------------------------------------
MIPClpSolver::MIPClpSolver()
    : mModel(nullptr),
      mLpFile(false),
      mSolverPrint(1)
{   
}


QString MIPClpSolver::Infos()
{
    return "Clp";
}

int MIPClpSolver::solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results)
{
    int vRet = -1;
    if (ap_Model) {
        mModel = ap_Model;
        if (mModel->isProblemBuilt() == false) {
            try {
                mModel->buildProblem();
            }
            catch (...) {
                qCritical() << "An Exception is detected in MIPModel::buildProblem()!";
                return -1;
            }
        }

        for (auto& vParam : a_Params) {                                    
            if (vParam.first == "SolverPrint") setSolverPrint(vParam.second.value);
            else if (vParam.first == "WriteLp") {
                if (vParam.second.value) writeLp();
            }
        }
        vRet = solve();
        a_Results.setResults(getOptimisationStatus(), getOptimalSolution());        
    }
    return vRet;
}

//--------------------------------------------------------------------------
void MIPClpSolver::setSolverPrint(const int& solverPrint) {
    mSolverPrint = solverPrint;
}
//--------------------------------------------------------------------------
void MIPClpSolver::writeLp(){
    mLpFile = true;
}
//--------------------------------------------------------------------------
int MIPClpSolver::solve() {
    int vRet = -1;
    std::cout<<"Start Solving using Clp"<<std::endl;

    //constraint matrix
    int numCols = mModel->getNumCols();
    int numRows = mModel->getNumRows();
    CoinPackedMatrix matrix(false,
                            numCols,
                            numRows,
                            mModel->getNumNonZeroElements(),
                            mModel->getNonZeroElements(),
                            mModel->getIndexes(),
                            mModel->getStartIndexes(),
                            mModel->getLengths());

    //variable and constraint informations
    std::vector<double> rowlb(numRows);
    std::vector<double> rowub(numRows);
    const double* rhs = mModel->getRhs();
    const char* sense = mModel->getSense();
    for(int i=0 ; i < numRows; i++) {
        if (sense[i] == 'E') {
            rowlb[i] = rhs[i];
            rowub[i] = rhs[i];
        }
        else if(sense[i] == 'L') {
            rowub[i] = rhs[i];
            rowlb[i] = -COIN_DBL_MAX;
        }
        else if(sense[i] == 'G') {
            rowub[i] = COIN_DBL_MAX;
            rowlb[i] = rhs[i];
        }
    }

    //OsiSolverInterface optimisation problem
    OsiClpSolverInterface vSolver;
    vSolver.loadProblem(matrix,
                         mModel->getColLowerBounds(),
                         mModel->getColUpperBounds(),
                         mModel->getObjectiveCoefficients(),
                         rowlb.data(),
                         rowub.data());

    //optimisation direction
    vSolver.setObjSense(mModel->getObjectiveDirection());

    //variable name informations (for high quality of LP file )
    std::vector<std::string> colNames = mModel->getColNames();
    for(int i = 0 ; i < numCols ; i++){
        if (!colNames[i].empty())
            vSolver.setColName(i,colNames[i]);
    }

    //variable name informations (for high quality of LP file )
    std::vector<std::string> rowNames = mModel->getRowNames();
    for(int i = 0 ; i < numRows ; i++){
        if (!rowNames[i].empty())
            vSolver.setRowName(i,rowNames[i]);
    }

    //Lp File generation
    if (mLpFile)
        vSolver.writeLp("clp_model");

    // solve problem
    vSolver.messageHandler()->setLogLevel(mSolverPrint);
    vSolver.initialSolve();

    if (vSolver.isProvenOptimal()) {
        mOptimisationStatus = "Optimal";
        mOptimalSolution.resize(numCols);
        const double *x = vSolver.getColSolution();
        mOptimalSolution.assign(x, x + numCols);
        mObjectiveValue = vSolver.getObjValue();
        vRet = 0;
    }
    else if (vSolver.isAbandoned()) {
        mOptimisationStatus = "Abandoned";
        vRet = 1;
    }
    else if (vSolver.isProvenPrimalInfeasible()) {
        mOptimisationStatus = "Infeasible";
        vRet = 1;
    }

    std::cout<<"Finish Solving using Clp"<<std::endl;
    return vRet;
}
//---------------------------------------------------------------------------
MIPClpSolver::~MIPClpSolver() {

}
//---------------------------------------------------------------------------
}
