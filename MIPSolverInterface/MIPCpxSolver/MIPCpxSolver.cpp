/**
 * @file MIPCpxSolver.cpp
 * @version 2.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 08/2019
*/


#include "MIPCpxSolver.h"
#include <cstring>

// --------------------------------------------------------------------------
#define TIME_LIMIT 10e+8
#define GAP 1e-4
#define THREADS 0
#define TREEMEMORYLIMIT 50000

namespace MIPSolverInterface {
// --------------------------------------------------------------------------
MIPCpxSolver::MIPCpxSolver()
    : mModel(nullptr),
      mTimeLimit(TIME_LIMIT),
      mGap(GAP),
      mThreads(THREADS),
      mTreeMemoryLimit(TREEMEMORYLIMIT),
      mLpFile(false),
      mSolverPrint(CPX_ON),
      mLocation("cplex"),
      mWriteMipStart(false),
      mFileMipStart(""),
      mReadParamFile(false),
      mTerminate(NULL)
{    
}

QString MIPCpxSolver::Infos()
{
    return "Cplex";
}

int MIPCpxSolver::solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results)
{
    int vRet = -1;
    if (ap_Model) {
        mModel = ap_Model;
        if (mModel->isProblemBuilt() == false) {
            try {
                mModel->buildProblem();
            }
            catch(...) {
                qCritical() << "An Exception is detected in MIPModel::buildProblem()!";
                return -1;
            }
        }

        for (auto& vParam : a_Params) {

            if (vParam.first == "Gap") setGap(vParam.second.value);
            else if (vParam.first == "TimeLimit") setTimeLimit(vParam.second.value);
            else if (vParam.first == "Threads") setThreads(vParam.second.value);
            else if (vParam.first == "TreeMemoryLimit") setTreeMemoryLimit(vParam.second.value);
            else if (vParam.first == "Location") {                
                setLocation(vParam.second.str.QString::toStdString());
            }
            else if (vParam.first == "SolverPrint") setSolverPrint(vParam.second.value);
            else if (vParam.first == "WriteLp") {
                if (vParam.second.value) writeLp();
            }
            else if (vParam.first == "ReadParamFile") {
                if (vParam.second.value) setReadParamFile();
            }
            else if (vParam.first == "WriteMipStart") {
                if (vParam.second.value) writeMipStart();
            }
            else if (vParam.first == "FileMipStart") {
                if (vParam.second.str != "") {                    
                    setFileMipStart(vParam.second.str.QString::toStdString());
                }
            }
            else if (vParam.first == "TerminateSignal") {
                setTerminateSignal(vParam.second.signal);
            }
        }
        vRet = solve();
        a_Results.setResults(getOptimisationStatus(), getOptimalSolution());        
    }        
    return vRet;
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

void MIPCpxSolver::setTerminateSignal(int *terminate){
    mTerminate=terminate;
}

int* MIPCpxSolver::getTerminateSignal(){
    return mTerminate;
}

void MIPCpxSolver::log(logLevel level, const std::string msg)
{
    if (mlogFile == nullptr) {        
        mlogFile = new std::fstream(mLocation + "_cplex.log", std::ios_base::out);
    }
    if (mlogFile->is_open()) {
        if (level==INFO)
            *mlogFile << "INFO: ";
        else
            *mlogFile << "ERROR: ";
        *mlogFile << msg << std::endl;
    }
}

void MIPCpxSolver::log(logLevel level, const std::string msg, double value)
{
    std::stringstream vMsg;
    vMsg << msg << value;
    log(level, vMsg.str());
}

// --------------------------------------------------------------------------
void MIPCpxSolver::setFileMipStart(const std::string &mipStartFile){
    mFileMipStart = mipStartFile;
}
// --------------------------------------------------------------------------

void MIPCpxSolver::setThreads(const int& threads) {
    mThreads = threads;
}

// --------------------------------------------------------------------------
void MIPCpxSolver::setTreeMemoryLimit(const int& a_TreeMemoryLimit)
{
    if (a_TreeMemoryLimit > 0)
        mTreeMemoryLimit = a_TreeMemoryLimit;
}
// --------------------------------------------------------------------------
void MIPCpxSolver::setMaxNumberOfSolutions(const int &maxNumberOfSolutions){
    if (maxNumberOfSolutions>=1){
        mMaxNumberOfSolutions = maxNumberOfSolutions;
    }
    else{
        mMaxNumberOfSolutions=1;
    }
}
// --------------------------------------------------------------------------
void MIPCpxSolver::setLocation(const std::string& location)
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
int MIPCpxSolver::solve() {

    int vRet = -1;
    log(INFO, "Start Solving using Cplex");
    std::string optimFile = mLocation + "_optim.log";
    std::string lpFile = mLocation + "_model.lp";
    std::string paramFile = mLocation + "_cplexParam.prm";
    std::string mipStartFile = mLocation + "_mipstart.mst";
    CPXENVptr env = NULL;
    CPXLPptr lp = NULL;
    int status;

    //create cplex environment
    env = CPXopenCPLEX(&status);
    if ( env == NULL ) {
        std::string errmsg; errmsg.resize(1024);
        CPXgeterrorstring (env, status, (char*)errmsg.c_str());
        log(ERR, "CPXopenCPLEX: Failed to open Cplex env. " + errmsg);
        return -1;
    }
   

    CPXsetlogfilename (env, optimFile.c_str(), "a");

    // show solving information
    status = CPXsetintparam(env, CPX_PARAM_SCRIND, mSolverPrint);

    //give a pointer to terminate

    status = CPXsetterminate (env, mTerminate);

    //create model
    lp = CPXcreateprob(env, &status, "problem");
    if ( lp == NULL ){
        log(ERR, "CPXcreateprob: Failed to create model");
        return -1;
    }
    else {
        //create variables
        int numCols = mModel->getNumCols();
        std::vector<char> coltype(numCols);
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
                             coltype.data(),
                             colNames.data());   //variable names
        if (status){
            log(ERR, "CPXnewcols: Failed when creating variables");
            return -1;
        }
        //add subobjectives
        if(*(mModel->getNumSubobj())>1){
            CPXsetnumobjs (env, lp, *(mModel->getNumSubobj()));
            for(int i = 0 ; i< *(mModel->getNumSubobj()); i++){
                MIPModeler::MIPSubobjective subObj = mModel->getListSubobjectives()[i];
                /*std::string name(subObj.getName());
                char* charName = new char[name.length() + 1];
                strcpy(charName, name.c_str());*/
                int rank = subObj.getRank();
                int cpxNumObj = CPXgetnumobjs(env,lp);
                if (rank >= cpxNumObj){
                    rank = cpxNumObj-1;
                }
                status = CPXmultiobjsetobj(env,lp,
                                           subObj.getRank(),
                                           subObj.getSubObjectiveExpression().getNode().size(),
                                           mModel->getSubobjectiveIndices()[i],
                                           mModel->getSubobjectiveCoefficients()[i],
                                           subObj.getSubObjectiveExpression().getConstPart(),
                                           1,
                                           subObj.getRank(),
                                           subObj.getAbsTol(),
                                           subObj.getRelTol(),
                                           subObj.getName().c_str());
                if (status){
                    log(ERR, "CPXmutliobjsetobj: Failed when creating subobj" + subObj.getName());
                }
            }

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
            log(ERR, "CPXaddrows: Failed when creating constraints");
            return -1;
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
                log(ERR, "CPXaddsos: Failed when setting SOS variables");
                return -1;
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
                log(ERR, "CPXaddmipstarts: Failed when adding warm start solutions");
                return -1;
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
            CPXwriteprob(env, lp, lpFile.c_str(), NULL);
        }
        if(mFileMipStart!=""){
            status = CPXreadcopymipstarts(env,lp,mFileMipStart.c_str());
        }
        //set mip parameters
        if (mModel->isMip()) {
            if(mReadParamFile){                
                CPXreadcopyparam(env, paramFile.c_str());
            }
            //set gap limit
            status = CPXsetdblparam(env, CPX_PARAM_EPGAP, mGap);
            if (status){
                log(ERR, "Failed to set Cplex gap");
            }

            // set time limit option
            status = CPXsetdblparam(env, CPXPARAM_TimeLimit, mTimeLimit);
            if (status){
                 log(ERR, "Failed to set Cplex time limit");
            }
            status = CPXsetdblparam(env,CPXPARAM_MIP_Limits_TreeMemory,mTreeMemoryLimit);
            // set number of threads
            status = CPXsetintparam(env, CPXPARAM_Threads, mThreads);
            if (status){
                log(ERR, "Failed to set Cplex number of threads");
            }

        }

        //solve mip or lp depending on problem type
        if(*(mModel->getNumSubobj())>1){
            status = CPXsetintparam(env,CPXPARAM_MultiObjective_Display,2);
            status = CPXmultiobjopt(env,lp,NULL);
            if ( status ){
                log(ERR, "CPXmipopt: Failed when solving mutliobj optimisation problem");
                return -1;
             }
        }
        else{
            status = CPXmipopt(env, lp);
            if ( status ){
                log(ERR, "CPXmipopt: Failed when solving optimisation problem");
                return -1;
             }
        }
        mOptimalSolution.resize(numCols, 0);
        double objval;
        int lpstat;
        status = CPXsolution (env,
                              lp,
                              &lpstat,
                              &objval,
                              mOptimalSolution.data(),
                              NULL, NULL, NULL);


        if (lpstat == CPX_STAT_OPTIMAL ||
            lpstat == CPXMIP_OPTIMAL ||
            lpstat == CPXMIP_OPTIMAL_TOL ||
            lpstat == CPX_STAT_MULTIOBJ_OPTIMAL){
            mOptimisationStatus = "Optimal";
            vRet = 0;
        }
        else if (lpstat == CPX_STAT_NUM_BEST){
            mOptimisationStatus = "Abandoned";
            vRet = 1;
        }
        else if (lpstat == CPX_STAT_UNBOUNDED ||
                 lpstat == CPXMIP_UNBOUNDED ||
                 lpstat == CPXMIP_ABORT_RELAXATION_UNBOUNDED){
             mOptimisationStatus = "Unbounded";
             vRet = 1;
        }
        else if (lpstat == CPX_STAT_INFEASIBLE ||
                 lpstat == CPX_STAT_INForUNBD ||
                 lpstat == CPXMIP_INForUNBD ||
                 lpstat == CPXMIP_OPTIMAL_INFEAS ||
                 lpstat == CPXMIP_INFEASIBLE ||
                 lpstat == CPXMIP_ABORT_INFEAS){
            mOptimisationStatus = "Infeasible";
            vRet = 1;
        }
        else if (lpstat == CPX_STAT_ABORT_TIME_LIM ||
                 lpstat == CPXMIP_TIME_LIM_FEAS||
                 lpstat == CPXMIP_ABORT_FEAS ){
            mOptimisationStatus = "Best Feasible (TimeLimit Reached)";
            vRet = 0;
        }
        else if (lpstat == CPXMIP_FEASIBLE ||
                 lpstat == CPX_STAT_FEASIBLE){
            mOptimisationStatus = "Best Feasible";
            vRet = 0;
        }
        else if (lpstat == CPXMIP_MEM_LIM_FEAS){
            mOptimisationStatus = "Best Feasible (TreeMemoryLimit Reached)";
            vRet = 0;
        }
        else{
            mOptimisationStatus = "Unknown Cplex code:"+std::to_string(lpstat);
            vRet = 1;
        }
        if (mWriteMipStart){            
            CPXwritemipstarts(env, lp, mipStartFile.c_str(), 0, 0);
        }

        mObjectiveValue = objval;        

        status = CPXgetbestobjval(env, lp, &mLpValue);
        if ( status ){
            log(ERR, "CPXgetbestobjval: Failed when getting best possible obj");
            return -1;
        }

        int nbSolTrouvees = CPXgetsolnpoolnumsolns(env,lp);        
        log(INFO, "Number of solutions trouvees:", nbSolTrouvees);
        if (nbSolTrouvees>mMaxNumberOfSolutions)
            mNbSolutionsGardees=mMaxNumberOfSolutions;
        else{
            mNbSolutionsGardees=nbSolTrouvees;
        }
        
        log(INFO, "Number max of solutions gardees:",  mMaxNumberOfSolutions);        
        log(INFO, "Number of solutions gardees:",  mNbSolutionsGardees);        
        for(int i=0; i<mNbSolutionsGardees;i++){
            mOtherSolutions.push_back(std::vector<double>( numCols, 0 ));
            pOtherSolutions.push_back(mOtherSolutions[i].data());
            status = CPXgetsolnpoolx(env,lp, i, mOtherSolutions[i].data(), 0, numCols - 1);
            mObjectiveOtherSolutions.push_back(0);
            CPXgetsolnpoolobjval(env,lp,i,&mObjectiveOtherSolutions[i]);
            std::stringstream msg1;
            msg1 <<"Solution "<<i<<":"<<mObjectiveOtherSolutions[i];            
            log(INFO, msg1.str());
        }
    }

    if (lp)
        CPXfreeprob (env, &lp);

    if (env)
        CPXcloseCPLEX (&env);

    log(INFO, "Finish solving using Cplex");    
    if (mlogFile) mlogFile->close();
    mlogFile = nullptr;
    return vRet;
}
// --------------------------------------------------------------------------
MIPCpxSolver::~MIPCpxSolver() {

}

// --------------------------------------------------------------------------
}
