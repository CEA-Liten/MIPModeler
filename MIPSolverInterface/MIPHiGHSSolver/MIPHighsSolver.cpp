/**
 * @file MIPCpxSolver.cpp
 * @version 2.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 08/2019
*/


#include "MIPHighsSolver.h"
#include <cstring>
#include "spdlog/spdlog.h"

extern "C" MIPHIGHSSOLVERSHARED_EXPORT IMIPSolver* createSolver()
{
    return new MIPSolverInterface::MIPHighsSolver();
}

// --------------------------------------------------------------------------
#define TIME_LIMIT 10e+8
#define GAP 1e-4
#define THREADS 0

namespace MIPSolverInterface {
// --------------------------------------------------------------------------
MIPHighsSolver::MIPHighsSolver()
    : mModel(nullptr),
      mTimeLimit(TIME_LIMIT),
      mGap(GAP),
      mThreads(THREADS),
      mLpFile(false),
      mSolverPrint(1)
{    
}

std::string MIPHighsSolver::Infos()
{
    return "Highs";
}


void userCallback(const int callback_type, const char* message, const HighsCallbackDataOut* data_out, HighsCallbackDataIn* data_in, void* user_callback_data)
{
    //spdlog::info(message);
    if (data_in && user_callback_data) {
        data_in->user_interrupt = *(int*)user_callback_data;
    }
}

int MIPHighsSolver::solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results)
{
    int vRet = -1;
    if (ap_Model) {
        mModel = ap_Model;
        if (mModel->isProblemBuilt() == false) {
            try {
                mModel->buildProblem();
            }
            catch (...) {
                spdlog::error("An Exception is detected in MIPModel::buildProblem()!");
                return -1;
            }
        }

        for (auto& vParam : a_Params) {
            if (vParam.first == "Gap") setGap(vParam.second.value);
            else if (vParam.first == "TimeLimit") setTimeLimit(vParam.second.value);
            else if (vParam.first == "Threads") setThreads(vParam.second.value);
            else if (vParam.first == "SolverPrint") setSolverPrint(vParam.second.value);
            else if (vParam.first == "Location") {
                setLocation(vParam.second.str);
            }
            else if (vParam.first == "WriteLp") {
                if (vParam.second.value) writeLp();
            }
            else if (vParam.first == "TerminateSignal") {
                mTerminateSignal = vParam.second.signal;
            }            
        }
        vRet = solve();
        a_Results.setResults(getOptimisationStatus(), getOptimalSolution());
    }
    return vRet;
}

// --------------------------------------------------------------------------
void MIPHighsSolver::setSolverPrint(const bool& solverPrint){
    mSolverPrint = solverPrint;
}
// --------------------------------------------------------------------------
void MIPHighsSolver::setTimeLimit(const double& timeLimit) {
    mTimeLimit = timeLimit;
}
// --------------------------------------------------------------------------
void MIPHighsSolver::setGap(const double& gap){
    mGap = gap;
}
// --------------------------------------------------------------------------
void MIPHighsSolver::setThreads(const int& threads) {
    mThreads = threads;
}
void MIPHighsSolver::setLocation(const std::string& location)
{
    mLocation = location;
}

// --------------------------------------------------------------------------
void MIPHighsSolver::writeLp() {
    mLpFile = true;
}
// --------------------------------------------------------------------------

int MIPHighsSolver::solve() {
    int vRet = -1;
    spdlog::info("Start Solving using Highs");

    // Variable Types
    std::vector<HighsInt> integrality_ = std::vector<HighsInt>(mModel->getNumCols(), (HighsInt)HighsVarType::kContinuous);
    int numIntCols = mModel->getNumIntegerCols();
    if  (numIntCols > 0) {
        const int* intCols = mModel->getColIntegers();
        for(int col = 0; col< numIntCols; col++)
            integrality_[intCols[col]] = (HighsInt)HighsVarType::kInteger;
     }
    
    HighsInt senseObj = 0;
    if (mModel->getObjectiveDirection() == MIPModeler::MIP_MAXIMIZE)
        senseObj = (HighsInt)ObjSense::kMaximize;
    else if (mModel->getObjectiveDirection() == MIPModeler::MIP_MINIMIZE)
        senseObj = (HighsInt)ObjSense::kMinimize;

    // Constraints
    vector<double> rowLowerBound(mModel->getNumRows(), -kHighsInf);
    vector<double> rowUpperBound(mModel->getNumRows(), kHighsInf);
    const double* rhs = mModel->getRhs();
    const char* sense = mModel->getSense();
    for(int row=0 ; row < mModel->getNumRows(); row++) {
        if (sense[row] == 'E') {
            rowLowerBound[row] = rhs[row];
            rowUpperBound[row] = rhs[row];
        }
        else if(sense[row] == 'L') {
            rowUpperBound[row] = rhs[row];
        }
        else if(sense[row] == 'G') {
            rowLowerBound[row] = rhs[row];
        }
    }
        
    
    // Create a Highs instance
    Highs highs;
    HighsStatus return_status = highs.setCallback(userCallback, mTerminateSignal);    
    highs.setOptionValue("log_file", mLocation + "_optim.log");
    highs.startCallback(1);
    

    // Pass the model to HiGHS
    highs.passModel(
        mModel->getNumCols(),
        mModel->getNumRows(),
        mModel->getNumNonZeroElements(), //const HighsInt num_nz,        
        (HighsInt)MatrixFormat::kRowwise, //const HighsInt a_format,         
        senseObj, //const HighsInt sense, 
        0, //const double offset, 
        mModel->getObjectiveCoefficients(),
        mModel->getColLowerBounds(),
        mModel->getColUpperBounds(),
        rowLowerBound.data(),
        rowUpperBound.data(), 
        mModel->getStartIndexes(),
        mModel->getIndexes(),
        mModel->getNonZeroElements(),
        integrality_.data()
    );

    // Variable names
    HighsInt col = 0;
    for (auto& vName : mModel->getColNames()) {
        highs.passColName(col++, vName);
    }
    
    // Constraint names
    HighsInt row = 0;    
    for (auto& vName : mModel->getRowNames()) {
        highs.passRowName(row++, vName);
    }
        
    // write model in lp file
    if (mLpFile)
        highs.writeModel(mLocation + "_model.lp");

    // Solve the model and get solve information
    highs.run();

    const HighsModelStatus& model_status = highs.getModelStatus();

    if (model_status == HighsModelStatus::kOptimal) {
        mOptimisationStatus = "Optimal";
        vRet = 0;

    }
    else if (model_status == HighsModelStatus::kInfeasible) {
        mOptimisationStatus = "Infeasible";
        vRet = 1;
    }
    else if (model_status == HighsModelStatus::kUnbounded) {
        mOptimisationStatus = "Unbounded";
        vRet = 1;
    }
    else if (model_status == HighsModelStatus::kTimeLimit) {
        mOptimisationStatus = "Best Feasible (TimeLimit Reached)";
        vRet = 0;
    }
    else {
        mOptimisationStatus = "Unknown Highs code:" + std::to_string((int)model_status);
        vRet = 1;
    }

    const HighsInfo& info = highs.getInfo();

    // Get the solution values
    mObjectiveValue = info.objective_function_value ;

    const HighsSolution& solution = highs.getSolution();
    mOptimalSolution.resize(mModel->getNumCols(),0);
    for(int col=0; col < mModel->getNumCols(); col++)
        mOptimalSolution[col] = solution.col_value[col];

    highs.stopCallback(1);
    spdlog::info("Finish Solving using Highs");
    return vRet;
}
// --------------------------------------------------------------------------
MIPHighsSolver::~MIPHighsSolver() {

}
// --------------------------------------------------------------------------
}
