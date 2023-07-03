#pragma once
#include <QtPlugin>
#include <QString>
#include "MIPModel.h"

class MIPSolverParams {
public:
    //typedef QString u_SolverParam;
    struct MIPSolverParam {
        double value;
        QString str;
        int* signal;
        MIPSolverParam() { value = 0; signal = nullptr; str = ""; };        
        ~MIPSolverParam() {};
    };
    typedef std::map<QString, MIPSolverParam >  t_MIPSolverParams;

    MIPSolverParams() {}
    void addParam(const QString& a_Name, const QString& a_Value) {  m_Params[a_Name].str = a_Value; }
    void addParam(const QString& a_Name, const double& a_Value) { m_Params[a_Name].value = a_Value; }
    void addParam(const QString& a_Name, int *a_Value) { m_Params[a_Name].signal = a_Value; }
   
    t_MIPSolverParams::const_iterator begin() const { return m_Params.begin(); }
    t_MIPSolverParams::const_iterator end() const { return m_Params.end(); }
protected:    
    t_MIPSolverParams m_Params; // mapping name, value
};

class MIPSolverResults {
public:
    MIPSolverResults() {}
    const std::string& getOptimisationStatus() { return m_OptimisationStatus; }
    const double *getOptimalSolution() { return m_OptimalSolution;  }

    void setResults(const std::string &a_OptimisationStatus, const double* ap_OptimalSolution)
    {
        m_OptimisationStatus = a_OptimisationStatus;
        m_OptimalSolution = ap_OptimalSolution;
    }
protected:
    std::string m_OptimisationStatus;
    const double* m_OptimalSolution { nullptr };
};


class IMIPSolver {
public:
    virtual ~IMIPSolver() {}
    virtual QString Infos() = 0;
    virtual int solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults &a_Results) = 0;
};


#define SolverInInterface_iid "Cea.MIPSolver.SolverInterface"

Q_DECLARE_INTERFACE(IMIPSolver, SolverInInterface_iid)
