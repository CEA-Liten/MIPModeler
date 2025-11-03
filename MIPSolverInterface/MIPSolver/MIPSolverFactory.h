#pragma once
#include "MIPSolver_global.h"
#include <string>
#include <vector>
#include <map>
#include "IMIPSolver.h"


class MIPSOLVERSHARED_EXPORT MIPSolverFactory
{
public:
    MIPSolverFactory();

    static void getAllInfos(std::vector<std::string>& a_Infos);
  
    static int solve(const std::string& a_Cmd, MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results);

protected:
    class SolverDescriptor
    {
    public:
        SolverDescriptor();        
        bool Init(const std::string& a_FileName);
        const std::string& getInfos();
        int solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results);
       

    protected:
        IMIPSolver* m_IPlugIn;
        std::string m_Infos;
    };


    static bool findSolvers(const std::string& a_Path);
    typedef std::map<std::string, SolverDescriptor> t_mapPlugIns;
    static t_mapPlugIns m_PlugIns;    
    static std::string sModuleName;
};
