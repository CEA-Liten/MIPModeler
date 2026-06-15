#if defined(WIN32) || defined(_WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#include "MIPSolverFactory.h"
#include <filesystem>

namespace fs = std::filesystem;

std::string MIPSolverFactory::sModuleName = "createSolver";
std::map<std::string, MIPSolverFactory::SolverDescriptor> MIPSolverFactory::m_PlugIns;

MIPSolverFactory::MIPSolverFactory()
{     
    spdlog::set_default_logger(MIPModeler::GetLogger());
    // recherche les solvers QCoreApplication::applicationDirPath()
    if (!findSolvers(fs::current_path().string())) {        
        findSolvers(std::getenv("CAIRN_BIN"));
    }
}

void MIPSolverFactory::getAllInfos(std::vector<std::string>& a_Infos)
{   
    // retourne les noms
    a_Infos.clear();
    t_mapPlugIns::iterator end = m_PlugIns.end();
    for (t_mapPlugIns::iterator it = m_PlugIns.begin(); it != end; it++) {
        a_Infos.push_back(it->second.getInfos().c_str());
    }    
}

int MIPSolverFactory::solve(const std::string& a_Cmd, MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results)
{
    int vRet = -1;
    t_mapPlugIns::iterator vIter = m_PlugIns.find(a_Cmd);
    if (vIter != m_PlugIns.end()) {
        vRet = vIter->second.solve(ap_Model, a_Params, a_Results);
    }
    else {
        spdlog::warn("cannot find solver " + a_Cmd);
    }
    return vRet;
}

bool MIPSolverFactory::findSolvers(const std::string& a_Path)
{
    bool vRet = false;
    std::string filterExt, filterStart;
#if (defined (_WIN32) || defined (_WIN64))
    filterExt = ".dll";
    filterStart = "MIP";
#else
    filterExt = ".so";
    filterStart = "libMIP";
#endif

    spdlog::debug("Search solvers in: " + a_Path);
    fs::path vPath(a_Path);
    for (auto const& dir_entry : fs::directory_iterator{ vPath }) {
        if (!dir_entry.is_directory()) {
            const fs::path& vFile = dir_entry.path();
            if (vFile.extension() == filterExt) {
                std::string vSolverName = vFile.stem().string();
                if (vSolverName.rfind(filterStart, 0) != std::string::npos) {
                    size_t vPos = vSolverName.rfind("Solver");
                    if (vPos != std::string::npos) {
                        vSolverName.replace(0, filterStart.size(), "");
                        vPos -= filterStart.size();
                        vSolverName.replace(vPos, vPos +  6, "");
                        if (vSolverName != "") {
                            SolverDescriptor vPlugIn;                            
                            if (vPlugIn.Init(fs::absolute(vFile).string())) {
                                m_PlugIns[vPlugIn.getInfos()] = vPlugIn;
                                vRet = true; // find a solver
                            }
                        }
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

bool MIPSolverFactory::SolverDescriptor::Init(const std::string& a_FileName)
{    
    if (a_FileName == "")
        return false;
  
#if defined(WIN32) || defined(_WIN32)   
    // 1ier essai (pour Cplex)
    HINSTANCE hGetProcIDDLL = LoadLibraryEx(a_FileName.c_str(), 0, LOAD_WITH_ALTERED_SEARCH_PATH);
    if (!hGetProcIDDLL) {
        // 2ieme essai
        hGetProcIDDLL = LoadLibraryEx(a_FileName.c_str(), 0, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
    }
    if (!hGetProcIDDLL) {
        DWORD dError = GetLastError();
        spdlog::warn("could not load the dynamic library " + a_FileName + ", error: " + std::to_string(dError));
        return false;
    }
#else   
    void* hGetProcIDDLL = dlopen((const char*)a_FileName.c_str(), RTLD_NOW);
    if (!hGetProcIDDLL) {        
        spdlog::warn("could not load the dynamic library " + a_FileName);
        return false;
    }
#endif
    
    typedef IMIPSolver* (*f_Solver)();
    f_Solver vFunct;
    // resolve function address here
#if defined(WIN32) || defined(_WIN32)
    vFunct = (f_Solver)GetProcAddress(hGetProcIDDLL, sModuleName.c_str());
    if (!vFunct) {
        DWORD dError = GetLastError();
        spdlog::warn("could not locate the function createSolver, error: " + std::to_string(dError));
        return false;
    }
#else
    vFunct = (f_Solver)dlsym(hGetProcIDDLL, sModuleName.c_str());
    if (!vFunct) {        
        spdlog::warn("could not locate the function createSolver");
        return false;
    }
#endif
    m_IPlugIn = (*vFunct)();

    if (!m_IPlugIn) {
        spdlog::warn("could not create the Solver " + m_Infos);
        return false;
    }
    else {
        m_Infos = m_IPlugIn->Infos();
        spdlog::debug("Find solver " + m_Infos + " in " + a_FileName);
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

const std::string& MIPSolverFactory::SolverDescriptor::getInfos()
{
    return m_Infos;
}
