/**
 * @file MIPClpSolver.cpp
 * @version 2.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 11/2018
*/

#include "MIPClpSolver.h"

namespace MIPSolverInterface {
// --------------------------------------------------------------------------
MIPClpSolver::MIPClpSolver(MIPModeler::MIPModel* model)
    : mModel(model),
      mSolver(new OsiClpSolverInterface()),
      mLpFile(false),
      mSolverPrint(1)
{
    if (mModel->isProblemBuilt() == false)
        mModel->buildProblem();
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
void MIPClpSolver::solve() {
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
    double* rowlb = new double[numRows];
    double* rowub = new double[numRows];
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
    mSolver->loadProblem(matrix,
                         mModel->getColLowerBounds(),
                         mModel->getColUpperBounds(),
                         mModel->getObjectiveCoefficients(),
                         rowlb,
                         rowub);

    //optimisation direction
    mSolver->setObjSense(mModel->getObjectiveDirection());

    //variable name informations (for high quality of LP file )
    std::vector<std::string> colNames = mModel->getColNames();
    for(int i = 0 ; i < numCols ; i++){
        if (!colNames[i].empty())
            mSolver->setColName(i,colNames[i]);
    }

    //variable name informations (for high quality of LP file )
    std::vector<std::string> rowNames = mModel->getRowNames();
    for(int i = 0 ; i < numRows ; i++){
        if (!rowNames[i].empty())
            mSolver->setRowName(i,rowNames[i]);
    }

    //Lp File generation
    if (mLpFile)
        mSolver->writeLp("clp_model");

    // solve problem
    mSolver->messageHandler()->setLogLevel(mSolverPrint);
    mSolver->initialSolve();

    if (mSolver->isProvenOptimal()) {
        mOptimisationStatus = "Optimal";
        mOptimalSolution = mSolver->getColSolution();
        mObjectiveValue = mSolver->getObjValue();
    }
    else if (mSolver->isAbandoned())
        mOptimisationStatus = "Abandoned";
    else if (mSolver->isProvenPrimalInfeasible())
        mOptimisationStatus = "Infeasible";

    std::cout<<"Finish Solving using Clp"<<std::endl;
}
//---------------------------------------------------------------------------
MIPClpSolver::~MIPClpSolver() {

}
//---------------------------------------------------------------------------
}
