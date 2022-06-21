/**
 * @file MIPCpxSolver.cpp
 * @version 2.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 08/2019
*/


#include "MIPCpxSolver.h"

// --------------------------------------------------------------------------
#define TIME_LIMIT 10e+8
#define GAP 1e-4
#define THREADS 0

namespace MIPSolverInterface {
// --------------------------------------------------------------------------
MIPCpxSolver::MIPCpxSolver(MIPModeler::MIPModel* model)
    : mModel(model),
      mTimeLimit(TIME_LIMIT),
      mGap(GAP),
      mThreads(THREADS),
      mLpFile(false),
      mSolverPrint(CPX_ON),
      mLocation("cplex"),
      mWriteMipStart(false),
      mFileMipStart(""),
      mReadParamFile(false)
{
    if (mModel->isProblemBuilt() == false)
        mModel->buildProblem();
}
// --------------------------------------------------------------------------
void MIPCpxSolver::setSolverPrint(const bool& solverPrint){
    mSolverPrint = solverPrint;
}
// --------------------------------------------------------------------------
void MIPCpxSolver::setTimeLimit(const double& timeLimit) {
    mTimeLimit = timeLimit;
}
// --------------------------------------------------------------------------

void MIPCpxSolver::setGap(const double& gap){
    mGap = gap;
}
// --------------------------------------------------------------------------
void MIPCpxSolver::setReadParamFile(){
    mReadParamFile = true;
}

// --------------------------------------------------------------------------
void MIPCpxSolver::setFileMipStart(const char* mipStartFile){
    mFileMipStart = mipStartFile;
}
// --------------------------------------------------------------------------

void MIPCpxSolver::setThreads(const int& threads) {
    mThreads = threads;
}

void MIPCpxSolver::setLocation(const char *location)
{
    mLocation = location ;
}

// --------------------------------------------------------------------------
void MIPCpxSolver::writeLp() {
    mLpFile = true;
}
// --------------------------------------------------------------------------
void MIPCpxSolver::writeMipStart() {
    mWriteMipStart = true;
}
// --------------------------------------------------------------------------
void MIPCpxSolver::solve() {
    std::cout<<"Start Solving using Cplex"<<std::endl;

    CPXENVptr env = NULL;
    CPXLPptr lp = NULL;
    int status;

    //create cplex environment
    env = CPXopenCPLEX(&status);
    if ( env == NULL ) {
        char errmsg[1024];
        CPXgeterrorstring (env, status, errmsg);
        std::cerr <<"CPXopenCPLEX: Failed to open Cplex env. " << errmsg <<std::endl;
        return;
    }
    std::string optimFile = mLocation ;
    optimFile += "_optim.log";
    char* stdLocation ;
    stdLocation = new char [optimFile.size()+1];
    std::strcpy( stdLocation, optimFile.c_str() );
    char const *filename = stdLocation ;
//    char const *mode ;
//    std::cout << "Writting to location file " << *filename ;
    CPXsetlogfilename (env, filename, "w");

    // show solving information
    status = CPXsetintparam(env, CPX_PARAM_SCRIND, mSolverPrint);

    //create model
    lp = CPXcreateprob(env, &status, "problem");
    if ( lp == NULL ){
        std::cerr <<"CPXcreateprob: Failed to create model"<<std::endl;
        return;
    }
    else {
        //create variables
        int numCols = mModel->getNumCols();
        char * coltype = new char[numCols];
        for (int i=0 ; i< numCols; i++)
            coltype[i] = 'C';

        if (mModel->isMip()) {
            int numIntCols = mModel->getNumIntegerCols();
            const int* intCols = mModel->getColIntegers();
            for(int i = 0; i< numIntCols; ++i)
                coltype[intCols[i]] = 'I';
        }

        std::vector<std::string> varNames = mModel->getColNames();
        std::vector<char*> colNames(numCols);
        for(int i = 0 ; i < numCols ; i++)
            colNames[i] = (char*)varNames[i].c_str();

        status = CPXnewcols (env, lp,
                             numCols,
                             mModel->getObjectiveCoefficients(),
                             mModel->getColLowerBounds(),
                             mModel->getColUpperBounds(),
                             coltype,
                             colNames.data());   //variable names
        if (status){
            std::cerr<<"CPXnewcols: Failed when creating variables"<<std::endl;
            return;
        }

        //create constraints
        int numRows = mModel->getNumRows();
        std::vector<std::string> cntNames = mModel->getRowNames();
        std::vector<char*> rowNames(numRows);
        for(int i = 0 ; i < numRows ; i++)
            rowNames[i] = (char*)cntNames[i].c_str();

        status = CPXaddrows (env, lp,
                             0,
                             numRows,
                             mModel->getNumNonZeroElements(),
                             mModel->getRhs(),
                             mModel->getSense(),
                             mModel->getStartIndexes(),
                             mModel->getIndexes(),
                             mModel->getNonZeroElements(),
                             NULL, rowNames.data()); //variables and constraint names
        if (status){
            std::cerr<<"CPXaddrows: Failed when creating constraints"<<std::endl;
            return;
        }

        //setting SOS variables
        std::vector<MIPModeler::MIPSpecialOrderedSet> sos;
        std::vector<MIPModeler::MIPSOSType> sosType;
        sos = mModel->getSOS();
        sosType = mModel->getSOSType();
        int nbSOS = sos.size();

        if (nbSOS > 0) {
            std::vector<int> CPX_sosColIndexes;
            std::vector<double> CPX_sosWeights;
            std::vector<int> CPX_sosStartIndexes;

            char* CPX_sosType = new char[nbSOS];
            for (int i = 0; i < nbSOS; ++i) {
                if (sosType[i] == MIPModeler::MIP_SOS1)
                    CPX_sosType[i] = '1';
                else if (sosType[i] == MIPModeler::MIP_SOS2)
                    CPX_sosType[i] = '2';

                // variable indexes (col index)
                std::vector<int> sosColIndexes = sos[i].getVarColIdx();
                CPX_sosColIndexes.insert(CPX_sosColIndexes.end(),
                                         sosColIndexes.begin(),
                                         sosColIndexes.end());

                // variable weight (to specify variable orders)
                std::vector<double> sosWeights = sos[i].getWeights();
                CPX_sosWeights.insert(CPX_sosWeights.end(),
                                      sosWeights.begin(),
                                      sosWeights.end());

                if (CPX_sosStartIndexes.empty())
                    CPX_sosStartIndexes.push_back(0);

                int last = CPX_sosStartIndexes.back();
                CPX_sosStartIndexes.push_back(last + sos[i].getNumElements());
            }

            status = CPXaddsos(env, lp,
                               int(nbSOS),
                               int(CPX_sosColIndexes.size()),
                               CPX_sosType,
                               CPX_sosStartIndexes.data(),
                               CPX_sosColIndexes.data(),
                               CPX_sosWeights.data(),
                               NULL);
            if (status){
                std::cerr<<"CPXaddsos: Failed when setting SOS variables"<<std::endl;
                return;
            }
        }

        //set warm start solution
        std::vector<MIPModeler::MIPWarmStart> CPX_warmStarts = mModel->getWarmStarts();
        if (!CPX_warmStarts.empty()){
            std::vector<int> CPX_warmStartBegIdx;
            std::vector<int> CPX_warmStartIdx;
            std::vector<double> CPX_warmStartVal;
            std::vector<int> CPX_effortlevel;
            std::vector<MIPModeler::MIPWarmStart>::iterator it = CPX_warmStarts.begin();
            for (; it != CPX_warmStarts.end(); it++){
                CPX_effortlevel.push_back(CPX_MIPSTART_REPAIR);
                std::vector<double> solValues = it->getValues();
                std::vector<int> solIdx = it->getVarColIdx();
                CPX_warmStartVal.insert(CPX_warmStartVal.end(), solValues.begin(), solValues.end());
                CPX_warmStartIdx.insert(CPX_warmStartIdx.end(), solIdx.begin(), solIdx.end());
                if (CPX_warmStartBegIdx.empty())
                    CPX_warmStartBegIdx.push_back(0);

                int last = CPX_warmStartBegIdx.back();
                CPX_warmStartBegIdx.push_back(last +  it->getNumElements());
            }

            status = CPXaddmipstarts(env, lp,
                                     CPX_warmStarts.size(),
                                     CPX_warmStartIdx.size(),
                                     CPX_warmStartBegIdx.data(),
                                     CPX_warmStartIdx.data(),
                                     CPX_warmStartVal.data(),
                                     CPX_effortlevel.data(),
                                     NULL);
            if (status){
                std::cerr<<"CPXaddmipstarts: Failed when adding warm start solutions"<<std::endl;
                return;
            }
        }


        //set objective direction
        if (mModel->getObjectiveDirection() == MIPModeler::MIP_MAXIMIZE)
            CPXchgobjsen(env, lp, CPX_MAX);
        else if (mModel->getObjectiveDirection() == MIPModeler::MIP_MINIMIZE)
            CPXchgobjsen(env, lp, CPX_MIN);

        //write .lp file for debugg
        if (mLpFile)
        {
            std::string optimFile = mLocation ;
            optimFile += "_model.lp";
            char* stdLocation ;
            stdLocation = new char [optimFile.size()+1];
            std::strcpy( stdLocation, optimFile.c_str() );
            char const *filename = stdLocation ;

            CPXwriteprob(env, lp, filename, NULL);
        }
        if(mFileMipStart!=""){
            status = CPXreadcopymipstarts(env,lp,mFileMipStart);
        }
        //set mip parameters
        if (mModel->isMip()) {
            if(mReadParamFile){
                std::string paramFile = mLocation ;
                paramFile += "_cplexParam.prm";
                char* stdLocation ;
                stdLocation = new char [paramFile.size()+1];
                std::strcpy( stdLocation, paramFile.c_str() );
                char const *filename = stdLocation ;

                CPXreadcopyparam(env, filename);
            }
            //set gap limit
            status = CPXsetdblparam(env, CPX_PARAM_EPGAP, mGap);
            if (status){
                std::cout<< "Failed to set Cplex gap"<<std::endl;
            }

            // set time limit option
            status = CPXsetdblparam(env, CPXPARAM_TimeLimit, mTimeLimit);
            if (status){
                 std::cout<<"Failed to set Cplex time limit"<<std::endl;
            }
            status = CPXsetdblparam(env,CPXPARAM_MIP_Limits_TreeMemory,50000);
            // set number of threads
            status = CPXsetintparam(env, CPXPARAM_Threads, mThreads);
            if (status){
                std::cout<<"Failed to set Cplex number of threads"<<std::endl;
            }

        }

        //solve mip or lp depending on problem type
        status = CPXmipopt(env, lp);
        if ( status ){
            std::cerr<<"CPXmipopt: Failed when solving optimisation problem"<<std::endl;
            return;
         }

        double* x = (double*)malloc( numCols * sizeof(double) );
        double objval;
        int lpstat;
        status = CPXsolution (env,
                              lp,
                              &lpstat,
                              &objval,
                              x,
                              NULL, NULL, NULL);


        if (lpstat == CPX_STAT_OPTIMAL ||
            lpstat == CPXMIP_OPTIMAL ||
            lpstat == CPXMIP_OPTIMAL_TOL){
            mOptimisationStatus = "Optimal";
        }
        else if (lpstat == CPX_STAT_NUM_BEST){
            mOptimisationStatus = "Abandoned";
        }
        else if (lpstat == CPX_STAT_UNBOUNDED ||
                 lpstat == CPXMIP_UNBOUNDED){
             mOptimisationStatus = "Unbounded";
        }
        else if (lpstat == CPX_STAT_INFEASIBLE ||
                 lpstat == CPX_STAT_INForUNBD ||
                 lpstat == CPXMIP_INForUNBD ||
                 lpstat == CPXMIP_OPTIMAL_INFEAS ||
                 lpstat == CPXMIP_INFEASIBLE){
            mOptimisationStatus = "Infeasible";
        }
        else if (lpstat == CPX_STAT_ABORT_TIME_LIM ||
                 lpstat == CPXMIP_TIME_LIM_FEAS){
            mOptimisationStatus = "Best Feasible (TimeLimit Reached)";
        }
        else if (lpstat == CPXMIP_FEASIBLE ||
                 lpstat == CPX_STAT_FEASIBLE){
            mOptimisationStatus = "Best Feasible";
        }
        else{
            mOptimisationStatus = "Unknown";
        }
        if (mWriteMipStart){
            std::string mipStartFile = mLocation ;
            mipStartFile += "_mipstart.mst";
            char* stdLocation ;
            stdLocation = new char [mipStartFile.size()+1];
            std::strcpy( stdLocation, mipStartFile.c_str() );
            char const *filename = stdLocation ;

            CPXwritemipstarts(env, lp, filename, 0,0);
        }

        mObjectiveValue = objval;
        mOptimalSolution = x;

        status = CPXgetbestobjval(env, lp, &mLpValue);
        if ( status ){
            std::cerr <<"CPXgetbestobjval: Failed when getting best possible obj"<<std::endl;
            return;
        }
    }

    if (lp)
        CPXfreeprob (env, &lp);

    if (env)
        CPXcloseCPLEX (&env);

    std::cout <<"Finish solving using Cplex"<<std::endl;
}
// --------------------------------------------------------------------------
MIPCpxSolver::~MIPCpxSolver() {

}
// --------------------------------------------------------------------------
}
