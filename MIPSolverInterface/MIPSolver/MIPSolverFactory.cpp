#if defined(WIN32) || defined(_WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#include <QCoreApplication>
#include <QDir>

#include "MIPSolverFactory.h"
#include <QDebug>

std::string MIPSolverFactory::sModuleName = "createSolver";
std::map<QString, MIPSolverFactory::SolverDescriptor> MIPSolverFactory::m_PlugIns;

MIPSolverFactory::MIPSolverFactory()
{     
    // recherche les solvers
    if (!findSolvers(QCoreApplication::applicationDirPath())) {
        QString appDir = qEnvironmentVariable("CAIRN_BIN", QDir::currentPath());
        findSolvers(appDir);
    }
}

void MIPSolverFactory::getAllInfos(QStringList& a_Infos)
{   
    // retourne les noms
    a_Infos.clear();
    t_mapPlugIns::iterator end = m_PlugIns.end();
    for (t_mapPlugIns::iterator it = m_PlugIns.begin(); it != end; it++) {
        a_Infos.push_back(it->second.getInfos());
    }    
}

int MIPSolverFactory::solve(const QString& a_Cmd, MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results)
{
    int vRet = -1;        
    t_mapPlugIns::iterator vIter = m_PlugIns.find(a_Cmd);
    if (vIter != m_PlugIns.end()) {
        vRet = vIter->second.solve(ap_Model, a_Params, a_Results);
    }    
    else {
        qWarning() << "cannot find solver " << a_Cmd;
    }
    return vRet;
}

bool MIPSolverFactory::findSolvers(const QString& a_Path)
{
    bool vRet = false;
    QString filterExt, filterStart;
#if (defined (_WIN32) || defined (_WIN64))
    filterExt = ".dll";
    filterStart = "MIP";
#else
    filterExt = ".so";
    filterStart = "libMIP";
#endif

    QDir vDir(a_Path, "*"+filterExt);
    qDebug() << "Search solvers in: " << a_Path;
    QFileInfoList vFiles(vDir.entryInfoList());
    for (auto& vFile : vFiles) {
        if (vFile.baseName().startsWith(filterStart)) {
            if (vFile.baseName().contains("Solver")) {                
                QStringList pathCuts = vFile.absoluteFilePath().split("/");
                QString dllName = pathCuts.takeLast();
                QString solverName = dllName;
                solverName = solverName.replace(filterExt, "").replace(filterStart, "").replace("Solver", "");
                if (solverName != "") {                    
                    SolverDescriptor vPlugIn;
                    if (vPlugIn.Init(vFile.absoluteFilePath())) {
                        QString vKey = vPlugIn.getInfos();                        
                        m_PlugIns[vKey] = vPlugIn;
                        vRet = true;
                    }
                }                                
            }
        }
    }
    return vRet;
}

//*******************************************************************************************
MIPSolverFactory::SolverDescriptor::SolverDescriptor()
{
    m_IPlugIn = nullptr;    
}

bool MIPSolverFactory::SolverDescriptor::Init(const QString& a_FileName)
{    
    if (a_FileName == "")
        return false;

    std::string vFileName = a_FileName.toStdString();

#if defined(WIN32) || defined(_WIN32)   
    // 1ier essai (pour Cplex)
    HINSTANCE hGetProcIDDLL = LoadLibraryEx(vFileName.c_str(), 0, LOAD_WITH_ALTERED_SEARCH_PATH);
    if (!hGetProcIDDLL) {
        // 2ieme essai
        hGetProcIDDLL = LoadLibraryEx(vFileName.c_str(), 0, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
    }
    if (!hGetProcIDDLL) {
        DWORD dError = GetLastError();
        qCritical() << "could not load the dynamic library " << a_FileName << ", error: " << dError;
        throw(std::exception_ptr());
    }
#else   
    void* hGetProcIDDLL = dlopen((const char*)vFileName.c_str(), RTLD_NOW);
    if (!hGetProcIDDLL) {        
        qCritical() << "could not load the dynamic library " << a_FileName);
        throw(std::exception_ptr());
    }
#endif
    
    typedef IMIPSolver* (*f_Solver)();
    f_Solver vFunct;
    // resolve function address here
#if defined(WIN32) || defined(_WIN32)
    vFunct = (f_Solver)GetProcAddress(hGetProcIDDLL, sModuleName.c_str());
    if (!vFunct) {
        DWORD dError = GetLastError();
        qCritical() << "could not locate the function createSolver" << ", error: " << dError;
        throw(std::exception_ptr());
    }
#else
    vFunct = (f_Solver)dlsym(hGetProcIDDLL, sModuleName.c_str());
    if (!vFunct) {        
        qCritical() << "could not locate the function createSolver";
        throw(std::exception_ptr());
    }
#endif
    m_IPlugIn = (*vFunct)();

    if (!m_IPlugIn) {
        qCritical() << "could not create the Solver " << m_Infos;
        throw(std::exception_ptr());
    }
    else {
        m_Infos = m_IPlugIn->Infos();
        qDebug() << "Find solver " << m_Infos << " in " << a_FileName;
    }
    
    return true;
}

int MIPSolverFactory::SolverDescriptor::solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results)
{
    int vRet = -1;    
    if (m_IPlugIn) {
        // solve return -1 if critical , 0 if problem is Feasible, 1 if problem is Infeasible
        vRet = m_IPlugIn->solve(ap_Model, a_Params, a_Results);

        // 
        if (vRet == 1) {
            // Transform results
            a_Results.modifyResults(ap_Model);            
        }
    }
    return vRet;
}

const QString& MIPSolverFactory::SolverDescriptor::getInfos()
{
    return m_Infos;
}
