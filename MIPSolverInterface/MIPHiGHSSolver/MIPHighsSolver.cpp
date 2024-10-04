/**
 * @file MIPCpxSolver.cpp
 * @version 2.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 08/2019
*/


#include "MIPHighsSolver.h"
#include <cstring>

// --------------------------------------------------------------------------
#define TIME_LIMIT 10e+8
#define GAP 1e-4
#define THREADS 0

namespace MIPSolverInterface {
// --------------------------------------------------------------------------
MIPHighsSolver::MIPHighsSolver(MIPModeler::MIPModel* model)
    : mModel(model),
      mTimeLimit(TIME_LIMIT),
      mGap(GAP),
      mThreads(THREADS),
      mLpFile(false),
      mSolverPrint(1)
{
    if (mModel->isProblemBuilt() == false)
        mModel->buildProblem();
}
/*
QString MIPHighsSolver::Infos()
{
    return "Highs";
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
*/
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
// --------------------------------------------------------------------------
void MIPHighsSolver::writeLp() {
    mLpFile = true;
}
// --------------------------------------------------------------------------
std::vector<double> convertToVector(const double* arr) {
    size_t length = sizeof(arr) / sizeof(arr[0]);
    return std::vector<double>(arr, arr + length);
}

std::vector<int> convertToVector(const int* arr) {
    size_t length = sizeof(arr) / sizeof(arr[0]);
    return std::vector<int>(arr, arr + length);
}


void MIPHighsSolver::solve() {
    std::cout<<"Start Solving using Highs"<<std::endl;

    HighsModel model;

    // Variables
    model.lp_.num_col_ = mModel->getNumCols();
    model.lp_.col_lower_ = convertToVector(mModel->getColLowerBounds());
    model.lp_.col_upper_ = convertToVector(mModel->getColUpperBounds());

    // Variable names
    model.lp_.col_names_ =  mModel->getColNames();

    // Variable Types
    model.lp_.integrality_ = std::vector<HighsVarType>(mModel->getNumCols(), HighsVarType::kContinuous);
    int numIntCols = mModel->getNumIntegerCols();
    if  (numIntCols > 0) {
        const int* intCols = mModel->getColIntegers();
        for(int col = 0; col< numIntCols; col++)
            model.lp_.integrality_[intCols[col]] = HighsVarType::kInteger;
     }

    // Objective Function
    model.lp_.col_cost_ = convertToVector(mModel->getObjectiveCoefficients());

    if (mModel->getObjectiveDirection() == MIPModeler::MIP_MAXIMIZE)
        model.lp_.sense_ = ObjSense::kMaximize;
    else if (mModel->getObjectiveDirection() == MIPModeler::MIP_MINIMIZE)
        model.lp_.sense_ = ObjSense::kMinimize;

    // Constraints
    vector<double> rowLowerBound(mModel->getNumRows(), kHighsInf);
    vector<double> rowUpperBound(mModel->getNumRows(), -kHighsInf);
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

    model.lp_.num_row_ = mModel->getNumRows();
    model.lp_.row_lower_ = rowLowerBound;
    model.lp_.row_upper_ = rowUpperBound;
    model.lp_.a_matrix_.value_ = convertToVector(mModel->getNonZeroElements()) ;
    model.lp_.a_matrix_.start_ = convertToVector(mModel->getStartIndexes()) ;
    model.lp_.a_matrix_.index_ = convertToVector(mModel->getIndexes()) ;
    model.lp_.a_matrix_.format_ = MatrixFormat::kRowwise;

    // Constraint names
    model.lp_.col_names_ = mModel->getColNames ();

    // Create a Highs instance
    Highs highs;
    HighsStatus return_status;

    // Pass the model to HiGHS
    highs.passModel(model);

    // write model in lp file
    if (mLpFile)
        highs.writeModel('highs_model');

    // Solve the model and get solve information
    highs.run();

    const HighsModelStatus& model_status = highs.getModelStatus();

    if (model_status == HighsModelStatus::kOptimal) {
        mOptimisationStatus = "Optimal";

    }
    else if (model_status == HighsModelStatus::kInfeasible) {
        mOptimisationStatus = "Infeasible";
    }
    else if (model_status == HighsModelStatus::kUnbounded) {
        mOptimisationStatus = "Unbounded";
    }
    else if (model_status == HighsModelStatus::kTimeLimit) {
        mOptimisationStatus = "Best Feasible (TimeLimit Reached)";
    }

    const HighsInfo& info = highs.getInfo();

    // Get the solution values
    mObjectiveValue = info.objective_function_value ;

    const HighsSolution& solution = highs.getSolution();
    mOptimalSolution = new double[model.lp_.num_col_] ;
    for(int col=0; col < model.lp_.num_col_; col++)
        mOptimalSolution[col] = solution.col_value[col];

    std::cout<<"Finish Solving using Highs"<<std::endl;
}
// --------------------------------------------------------------------------
MIPHighsSolver::~MIPHighsSolver() {

}
// --------------------------------------------------------------------------
}
