#pragma once
#include "MIPSolver_global.h"
#include <QString>
#include <map>
#include "IMIPSolver.h"


class MIPSOLVERSHARED_EXPORT MIPSolverFactory
{
public:
    MIPSolverFactory();

    static void getAllInfos(QStringList& a_Infos);
    static int solve(const QString& a_Cmd, MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results);

protected:
    class SolverDescriptor
    {
    public:
        SolverDescriptor();
        bool Init(const QString& a_Name);
        const QString& getInfos();
        int solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results);
       

    protected:
        IMIPSolver* m_IPlugIn;
        QString m_Infos;
    };


    static bool findSolvers(const QString& a_Path);
    typedef std::map<QString, SolverDescriptor> t_mapPlugIns;
    static t_mapPlugIns m_PlugIns;    
};
