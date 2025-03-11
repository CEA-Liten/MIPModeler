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
      mTimeLimit(TIME_LIMIT),
      mGap(GAP),
      mThreads(THREADS),
      mLpFile(false),
      mSolverPrint(1),
      mLpFileCycle(0)
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
            if (vParam.first == "Gap") setGap(vParam.second.value);
            else if (vParam.first == "TimeLimit") setTimeLimit(vParam.second.value);
            else if (vParam.first == "Threads") setThreads(vParam.second.value);            
            else if (vParam.first == "SolverPrint") setSolverPrint(vParam.second.value);
            else if (vParam.first == "WriteLp") {
                if (vParam.second.value) writeLp();
            }
        }
        vRet = solve();
        a_Results.setResults(getOptimisationStatus(), getOptimalSolution());        
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
// --------------------------------------------------------------------------
void MIPCbcSolver::writeLpCycle(const int cycel) {
    mLpFileCycle = cycel;
}
//---------------------------------------------------------------------------
int MIPCbcSolver::solve() {
    
    int vRet = -1;
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

    //integer variables information
    if (mModel->isMip())
        vSolver.setInteger(mModel->getColIntegers(),
                            mModel->getNumIntegerCols());

    //optimisation direction
    vSolver.setObjSense(mModel->getObjectiveDirection());

    //variable name informations (for high quality of LP file )
    std::vector<std::string> colNames = mModel->getColNames();
    for(int i = 0 ; i < numCols ; i++){
        if (!colNames[i].empty())
            vSolver.setColName(i,colNames[i]);
    }

    //constraint name informations (for high quality of LP file )
    std::vector<std::string> rowNames = mModel->getRowNames();
    for(int i = 0 ; i < numRows ; i++){
        if (!rowNames[i].empty())
            vSolver.setRowName(i,rowNames[i]);
    }

    //Lp File generation
    if (mLpFile)
        vSolver.writeLp("cbc_model");

    //CBCModel generation
    CbcModel vCbcModel(vSolver);
    
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
                objects[i] = new CbcSOS(&vCbcModel,
                                        sos[i].getNumElements (),
                                        sos[i].getVarColIdx().data(),
                                        NULL,
                                        i, 1);
            else if (sosType[i] == MIPModeler::MIP_SOS2)
                objects[i] = new CbcSOS(&vCbcModel,
                                        sos[i].getNumElements(),
                                        sos[i].getVarColIdx().data(),
                                        NULL,
                                        i, 2);
        }
        vCbcModel.addObjects(nbSOS, objects);
        for (int i = 0; i < nbSOS; i++)
            delete objects[i];
        delete[] objects;
    }

    // set mip parmameters
    if (mModel->isMip()){
        vCbcModel.setMaximumSeconds(mTimeLimit);
        vCbcModel.setAllowableGap(mGap);
        vCbcModel.setNumberThreads(mThreads);
    }

    // solve problem
    vCbcModel.messageHandler()->setLogLevel(mSolverPrint);
    const char *args[] = { "cbcModel", "-solve", "-quit" };
    CbcMain0(vCbcModel);
    CbcMain1(3, args, vCbcModel);

    if (vCbcModel.isProvenInfeasible()){
        mOptimisationStatus = "Infeasible";
        vRet = 1;
    }
    else if (vCbcModel.isAbandoned()){
        mOptimisationStatus = "Abandoned (numerical difficulties)";
        vRet = 1;
    }
    else if (vCbcModel.isProvenDualInfeasible()){
        mOptimisationStatus = "Unbounded";
        vRet = 1;
    }
    else if (vCbcModel.isProvenOptimal()){
        mOptimisationStatus = "Optimal";
        setOptimalSolution(numCols, vCbcModel);		
        vRet = 0;
	}
    else if (vCbcModel.isSecondsLimitReached()){
        mOptimisationStatus = "Best Feasible (TimeLimit Reached)";
        setOptimalSolution(numCols, vCbcModel);  
        vRet = 0;
    }
    else {
        mOptimisationStatus = "Best Feasible";
        setOptimalSolution(numCols, vCbcModel);        
        vRet = 0;
    }

    std::cout<<"Finish Solving using Cbc"<<std::endl;
    return vRet;
}

void MIPCbcSolver::setOptimalSolution(int numCols, const CbcModel& aCbcModel)
{
    mOptimalSolution.resize(numCols);
    const double* x = aCbcModel.getColSolution();
    mOptimalSolution.assign(x, x + numCols);

    mObjectiveValue = aCbcModel.getObjValue();
    mLpValue = aCbcModel.getBestPossibleObjValue();
}

//---------------------------------------------------------------------------
MIPCbcSolver::~MIPCbcSolver()
{    
}
//---------------------------------------------------------------------------
}
