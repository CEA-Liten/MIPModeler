/**
 * @file MIPMskSolver.cpp
 * @version 2.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 08/2019
*/


#include "MIPMskSolver.h"

// --------------------------------------------------------------------------
#define TIME_LIMIT 10e+8
#define GAP 1e-4
#define THREADS 0

namespace MIPSolverInterface {
// --------------------------------------------------------------------------
MIPMskSolver::MIPMskSolver(MIPModeler::MIPModel* model)
    : mModel(model),
      mTimeLimit(TIME_LIMIT),
      mGap(GAP),
      mThreads(THREADS),
      mLpFile(false)
{
    if (mModel->isProblemBuilt() == false)
        mModel->buildProblem();
}
// --------------------------------------------------------------------------
void MIPMskSolver::setSolverPrint(const int& solverPrint) {
    mSolverPrint = solverPrint;
}
// --------------------------------------------------------------------------
void MIPMskSolver::setTimeLimit(const double& timeLimit) {
    mTimeLimit = timeLimit;
}
// --------------------------------------------------------------------------
void MIPMskSolver::setGap(const double& gap) {
    mGap = gap;
}
// --------------------------------------------------------------------------
void MIPMskSolver::setThreads(const int& threads) {
    mThreads = threads;
}
// --------------------------------------------------------------------------
void MIPMskSolver::writeLP() {
    mLpFile = true;
}
// --------------------------------------------------------------------------
void MIPMskSolver::solve() {
    std::cout<<"Start Solving using Mosek"<<std::endl;

    MSKenv_t env = NULL;
    MSKtask_t task = NULL;
    MSKrescodee err;

    // Create the mosek environment
    err = MSK_makeenv(&env, NULL);

    // Create the optimization task
    int numRows = mModel->getNumRows();
    int numCols = mModel->getNumCols();
    err = MSK_maketask(env, numRows, numCols, &task);

    // Append 'numcon' empty constraints
    err = MSK_appendcons(task, numRows);

    // Append 'numvar' variables
    err = MSK_appendvars(task, numCols);

    // Interpreting columns
    int* cols = new int[numCols];
    MSKboundkeye* varTypeBounds = new MSKboundkeye[numCols];
    for (int j = 0; j < numCols; j++) {
        cols[j] = j;
        varTypeBounds[j] = MSK_BK_RA;
    }

    err = MSK_putclist(task, numCols, cols, mModel->getObjectiveCoefficients());
    err = MSK_putvarboundlist(task, numCols, cols, varTypeBounds,
                              mModel->getColLowerBounds(), mModel->getColUpperBounds());

    // Interpreting integer variables if exist
    if (mModel->isMip()) {
        int numIntCols = mModel->getNumIntegerCols();
        const int* intCols = mModel->getColIntegers();
        MSKvariabletypee *varType = new MSKvariabletypee[numIntCols];
        for (int j = 0; j < numIntCols; j++)
            varType[j] = MSK_VAR_TYPE_INT;

        err = MSK_putvartypelist(task, numIntCols, intCols, varType);
    }

    //variable name informations (for high quality of LP file )
    std::vector<std::string> colNames = mModel->getColNames();
    for (int j = 0; j < numCols; j++)
        if (!colNames[j].empty())
           err = MSK_putvarname(task, j, colNames[j].c_str());

    // Interpreting info on constraints (rows)
    int* rows = new int[numRows];
    int* rowEnds = new int[numRows];
    double* rowlb = new double[numRows];
    double* rowub = new double[numRows];
    MSKboundkeye *cntTypeBounds = new MSKboundkeye[numRows];
    const int* rowStarts = mModel->getStartIndexes();
    const int* rowLengths = mModel->getLengths();
    const double *rhs = mModel->getRhs();
    const char* sense = mModel->getSense();
    for (int j = 0; j < numRows; j++) {
        rows[j] = j;
        rowEnds[j] = rowStarts[j] + rowLengths[j];
        if (sense[j] == 'G') {
            cntTypeBounds[j] = MSK_BK_LO;
            rowlb[j] = rhs[j];
            rowub[j] = MSK_INFINITY;
        }
        else if (sense[j] == 'L') {
            cntTypeBounds[j] = MSK_BK_UP;
            rowlb[j] = -MSK_INFINITY;
            rowub[j] = rhs[j];
        }
        else if (sense[j] == 'E') {
            cntTypeBounds[j] = MSK_BK_FX;
            rowlb[j] = rhs[j];
            rowub[j] = rhs[j];
        }
    }

    err = MSK_putarowlist(task,
                          numRows,
                          rows,
                          rowStarts,
                          rowEnds,
                          mModel->getIndexes(),
                          mModel->getNonZeroElements());
    err = MSK_putconboundlist(task, numRows, rows, cntTypeBounds, rowlb, rowub);

    //variable name informations (for high quality of LP file )
    std::vector<std::string> rowNames = mModel->getRowNames();
    for (int j = 0; j < numRows; j++)
        if (!rowNames[j].empty())
           err = MSK_putconname(task, j, rowNames[j].c_str());

    // optimization direction
    if (mModel->getObjectiveDirection() == MIPModeler::MIP_MAXIMIZE)
        err = MSK_putobjsense(task, MSK_OBJECTIVE_SENSE_MAXIMIZE);
    else if (mModel->getObjectiveDirection() == MIPModeler::MIP_MINIMIZE)
        err = MSK_putobjsense(task, MSK_OBJECTIVE_SENSE_MINIMIZE);

    //write .lp file for debugg
    if (mLpFile)
        MSK_writedata(task, "mosek_model.lp");

    // set mosek mip parameter
    if (mModel->isMip()) {
        err = MSK_putdouparam(task, MSK_DPAR_MIO_TOL_REL_GAP, mGap);
        err = MSK_putdouparam(task, MSK_DPAR_MIO_MAX_TIME, mTimeLimit);
        err = MSK_putintparam(task, MSK_IPAR_NUM_THREADS, mThreads);
    }

    // Run optimizer
    MSKrescodee trmcode;
    err = MSK_optimizetrm(task, &trmcode);
    MSK_solutionsummary(task, MSK_STREAM_LOG);

    // define solution type depending on problem status
    MSKsoltypee solution;
    double* colsol = new double[numCols];
    if (mModel->isMip() == false) {
        if (definedSolution(task, MSK_SOL_BAS) == true)
            solution = MSK_SOL_BAS;
        else if (definedSolution(task, MSK_SOL_ITR) == true)
            solution = MSK_SOL_ITR;
        else {
            mOptimisationStatus = "Unknown";
            MSK_deletetask(&task);
            MSK_deleteenv(&env);
            std::cerr<<"Solving mosek FAILED" << std::endl;
            return ;
        }
    }
    else if (definedSolution(task, MSK_SOL_ITG) == true)
        solution = MSK_SOL_ITG;
    else {
        mOptimisationStatus = "Unknown";
        MSK_deletetask(&task);
        MSK_deleteenv(&env);
        std::cerr<<"Solving mosek FAILED" << std::endl;
        return ;
    }

    // get optimizer results
    MSKsolstae solsta;
    err = MSK_getsolution(task,
                          solution,
                          NULL,
                          &solsta,
                          NULL,
                          NULL,
                          NULL,
                          NULL,
                          colsol,
                          NULL,
                          NULL,
                          NULL,
                          NULL,
                          NULL,
                          NULL);
    double objval;
    MSK_getprimalobj(task, solution, &objval);

    bool isProvenOptimal = (solsta == MSK_SOL_STA_OPTIMAL ||
                            solsta == MSK_SOL_STA_INTEGER_OPTIMAL ||
                            solsta == MSK_SOL_STA_NEAR_OPTIMAL ||
                            solsta == MSK_SOL_STA_NEAR_INTEGER_OPTIMAL);
    bool isAbandoned = (solsta == MSK_SOL_STA_UNKNOWN);
    bool isInfeasible = (solsta == MSK_SOL_STA_PRIM_INFEAS_CER ||
                         solsta == MSK_SOL_STA_NEAR_PRIM_INFEAS_CER ||
                         solsta == MSK_SOL_STA_DUAL_INFEAS_CER ||
                         solsta == MSK_SOL_STA_NEAR_DUAL_INFEAS_CER);
    if (isProvenOptimal)
        mOptimisationStatus = "Optimal";
    else if (isAbandoned)
        mOptimisationStatus = "Unknown";
    else if (isInfeasible)
        mOptimisationStatus = "Infeasible";

    mOptimalSolution = colsol;
    mObjectiveValue = objval;

    //close mosek environment
    MSK_deletetask(&task);
    MSK_deleteenv(&env);

    std::cout<<"Finish Solving using Mosek"<< std::endl;
}
// --------------------------------------------------------------------------
bool MIPMskSolver::definedSolution(MSKtask_t& task, int solType) {
    int err, res;
    err = MSK_solutiondef(task, (MSKsoltypee)solType, &res);
    return (res != MSK_RES_OK);
}
// --------------------------------------------------------------------------
MIPMskSolver::~MIPMskSolver() {

}
// --------------------------------------------------------------------------
}
