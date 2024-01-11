#pragma once
#include <QtPlugin>
#include <QString>
#include "MIPModel.h"

constexpr double OPTIM_HUGE_VAL = 1e100;
constexpr double OPTIM_SMALL_VAL = 1e-100;


class MIPSolverParams {
public:
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
    const double *getOptimalSolution(int aNsol) { 
        if (!aNsol)
            return m_OptimalSolution;  
        else {
            return m_OtherSolutions[aNsol];
        }    
    }
    int getNumberOfSolutions() { return m_NumberOfSolutions;  };

    void setResults(const std::string &a_OptimisationStatus, const double* ap_OptimalSolution, int a_NumberOfSolutions=1)
    {
        m_OptimisationStatus = a_OptimisationStatus;
        m_OptimalSolution = ap_OptimalSolution;
        m_NumberOfSolutions = a_NumberOfSolutions;

    }
    void setOtherResults(const std::vector<std::vector<double>> &aOtherSolutions)
    {        
        for (auto& vOtherSolution : aOtherSolutions) {
            m_OtherSolutions.push_back(vOtherSolution.data());
        }
    }

    void modifyResults(MIPModeler::MIPModel* ap_Model) {
        if (ap_Model) {
            int numCols = ap_Model->getNumCols();
            double sol = OPTIM_HUGE_VAL;
            if (ap_Model->getObjectiveDirection() == MIPModeler::MIP_MAXIMIZE) {
                sol = OPTIM_SMALL_VAL;
            }
            m_infeasiblesol.resize(numCols, sol);
            m_OptimalSolution = m_infeasiblesol.data();
        }
    }
protected:
    std::string m_OptimisationStatus;
    const double* m_OptimalSolution { nullptr };
    std::vector<double> m_infeasiblesol;
    int m_NumberOfSolutions{ 1 };
    std::vector<const double*> m_OtherSolutions;
};


class IMIPSolver {
public:
    virtual ~IMIPSolver() {}
    virtual QString Infos() = 0;
    virtual int solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults &a_Results) = 0;
};


#define SolverInInterface_iid "Cea.MIPSolver.SolverInterface"

Q_DECLARE_INTERFACE(IMIPSolver, SolverInInterface_iid)
