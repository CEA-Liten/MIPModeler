/**
 * @file MIPCbcSolver.cpp
 * @version 2.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 11/2018
*/

#include "MIPCbcSolver.h"

//---------------------------------------------------------------------------
#define TIME_LIMIT 10e+8
#define GAP 1e-4
#define THREADS 0

namespace MIPSolverInterface {
//---------------------------------------------------------------------------
MIPCbcSolver::MIPCbcSolver()
    : mModel(nullptr),
      mSolver(new OsiClpSolverInterface()),
      mTimeLimit(TIME_LIMIT),
      mGap(GAP),
      mThreads(THREADS),
      mLpFile(false),
      mSolverPrint(1)
{   
}

QString MIPCbcSolver::Infos()
{
    return "Cbc";
}

int MIPCbcSolver::solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results)
{
    int vRet = -1;
    if (ap_Model) {
        mModel = ap_Model;
        if (mModel->isProblemBuilt() == false)
            mModel->buildProblem();

        for (auto& vParam : a_Params) {
            if (vParam.first == "Gap") setGap(vParam.second.value);
            else if (vParam.first == "TimeLimit") setTimeLimit(vParam.second.value);
            else if (vParam.first == "Threads") setThreads(vParam.second.value);            
            else if (vParam.first == "SolverPrint") setSolverPrint(vParam.second.value);
            else if (vParam.first == "WriteLp") if (vParam.second.value) writeLp();            
        }
        solve();

        a_Results.setResults(getOptimisationStatus(), getOptimalSolution());
        vRet = 0;
    }
    return vRet;
}

//---------------------------------------------------------------------------
void MIPCbcSolver::setSolverPrint(const int& solverPrint) {
    mSolverPrint = solverPrint;
}
//---------------------------------------------------------------------------
void MIPCbcSolver::setTimeLimit(const double& timeLimit) {
	mTimeLimit = timeLimit;
}
//---------------------------------------------------------------------------
void MIPCbcSolver::setGap(const double& gap) {
	mGap = gap;
}
//---------------------------------------------------------------------------
void MIPCbcSolver::setThreads(const int& threads) {
    mThreads = threads;
}
//---------------------------------------------------------------------------
void MIPCbcSolver::writeLp() {
    mLpFile = true;
}
//---------------------------------------------------------------------------
void MIPCbcSolver::solve() {
    std::cout<<"Start Solving using Cbc"<<std::endl;

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

    //integer variables information
    if (mModel->isMip())
        mSolver->setInteger(mModel->getColIntegers(),
                            mModel->getNumIntegerCols());

    //optimisation direction
    mSolver->setObjSense(mModel->getObjectiveDirection());

    //variable name informations (for high quality of LP file )
    std::vector<std::string> colNames = mModel->getColNames();
    for(int i = 0 ; i < numCols ; i++){
        if (!colNames[i].empty())
            mSolver->setColName(i,colNames[i]);
    }

    //constraint name informations (for high quality of LP file )
    std::vector<std::string> rowNames = mModel->getRowNames();
    for(int i = 0 ; i < numRows ; i++){
        if (!rowNames[i].empty())
            mSolver->setRowName(i,rowNames[i]);
    }

    //Lp File generation
    if (mLpFile)
        mSolver->writeLp("cbc_model");

    //CBCModel generation
    mCbcModel = new CbcModel(*mSolver);

    //setting SOS variables
    std::vector<MIPModeler::MIPSpecialOrderedSet> sos;
    std::vector<MIPModeler::MIPSOSType> sosType;
    sos = mModel->getSOS();
    sosType = mModel->getSOSType();
    int nbSOS = sos.size();

    if (nbSOS > 0) {
        CbcObject **objects = new CbcObject*[nbSOS];
        for (int i = 0; i < nbSOS; i++) {
            if (sosType[i] == MIPModeler::MIP_SOS1)
                objects[i] = new CbcSOS(mCbcModel,
                                        sos[i].getNumElements (),
                                        sos[i].getVarColIdx().data(),
                                        NULL,
                                        i, 1);
            else if (sosType[i] == MIPModeler::MIP_SOS2)
                objects[i] = new CbcSOS(mCbcModel,
                                        sos[i].getNumElements(),
                                        sos[i].getVarColIdx().data(),
                                        NULL,
                                        i, 2);
        }
        mCbcModel->addObjects(nbSOS, objects);
        for (int i = 0; i < nbSOS; i++)
            delete objects[i];
        delete[] objects;
    }

    // set mip parmameters
    if (mModel->isMip()){
        mCbcModel->setMaximumSeconds(mTimeLimit);
        mCbcModel->setAllowableGap(mGap);
        mCbcModel->setNumberThreads(mThreads);
    }

    // solve problem
    mCbcModel->messageHandler()->setLogLevel(mSolverPrint);
    const char *args[] = { "cbcModel", "-solve", "-quit" };
    CbcMain0(*mCbcModel);
    CbcMain1(3, args, *mCbcModel);

    if (mCbcModel->isProvenInfeasible()){
        mOptimisationStatus = "Infeasible";
    }
    else if (mCbcModel->isAbandoned()){
        mOptimisationStatus = "Abandoned (numerical difficulties)";
    }
    else if (mCbcModel->isProvenDualInfeasible()){
        mOptimisationStatus = "Unbounded";
    }
    else if (mCbcModel->isProvenOptimal()){
        mOptimisationStatus = "Optimal";
        mOptimalSolution = mCbcModel->getColSolution();
		mObjectiveValue = mCbcModel->getObjValue();
        mLpValue = mCbcModel->getBestPossibleObjValue();
	}
    else if (mCbcModel->isSecondsLimitReached()){
        mOptimisationStatus = "Best Feasible (TimeLimit Reached)";
        mOptimalSolution = mCbcModel->getColSolution();
        mObjectiveValue = mCbcModel->getObjValue();
        mLpValue = mCbcModel->getBestPossibleObjValue();
    }
    else {
        mOptimisationStatus = "Best Feasible";
        mOptimalSolution = mCbcModel->getColSolution();
        mObjectiveValue = mCbcModel->getObjValue();
        mLpValue = mCbcModel->getBestPossibleObjValue();
    }

    std::cout<<"Finish Solving using Cbc"<<std::endl;
}
//---------------------------------------------------------------------------
MIPCbcSolver::~MIPCbcSolver()
{

}
//---------------------------------------------------------------------------
}
