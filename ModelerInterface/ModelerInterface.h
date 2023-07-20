#pragma once
#include <QtPlugin>

class ModelerParams {
public:
    struct ModelerParam {
        double value;
        std::string str;
        std::vector<double> values;
        std::vector<std::string> strs;

        ModelerParam() { value = 0; str = ""; };
        ~ModelerParam() {};
    };
    typedef std::map<std::string, ModelerParam >  t_MIPModelerParams;

    ModelerParams() {}
    void addParam(const std::string& a_Name, const std::string& a_Value) { m_Params[a_Name].str = a_Value; }
    void addParam(const std::string& a_Name, const double& a_Value) { m_Params[a_Name].value = a_Value; }    
    void addParam(const std::string& a_Name, const std::vector<double>& a_Value) { m_Params[a_Name].values = a_Value; }
    void addParam(const std::string& a_Name, const std::vector<std::string>& a_Value) { m_Params[a_Name].strs = a_Value; }

    t_MIPModelerParams::const_iterator find(const std::string& a_Name) const { return m_Params.find(a_Name); }
    t_MIPModelerParams::const_iterator begin() const { return m_Params.begin(); }
    t_MIPModelerParams::const_iterator end() const { return m_Params.end(); }
protected:
    t_MIPModelerParams m_Params; // mapping name, value
};

class MIPModelerResults {
public:
    MIPModelerResults() {}
    const std::string& getOptimisationStatus() { return m_OptimisationStatus; }
    const double* getOptimalSolution() { return m_OptimalSolution; }

    void setResults(const std::string& a_OptimisationStatus, const double* ap_OptimalSolution)
    {
        m_OptimisationStatus = a_OptimisationStatus;
        m_OptimalSolution = ap_OptimalSolution;
    }
protected:
    std::string m_OptimisationStatus;
    const double* m_OptimalSolution{ nullptr };
};


class ModelerInterface {
public:
    virtual ~ModelerInterface() {}
    virtual std::string Infos() = 0;

    // model
    virtual void init(const ModelerParams& a_params) = 0;
    virtual void setParams(const ModelerParams& a_params) = 0;
    virtual void addComment(const std::string& text) = 0;
    virtual void addText(const std::string& text) = 0;
    virtual void addData(const std::vector<std::string&>& data, const bool& importToGMS = false) = 0;

    virtual void addModelFromFile(const std::string& fileName, const std::string& modelName, const std::string& modelOption = "") = 0;

    // solver
    //virtual int solve(const SolverParams& a_Params, SolverResults& a_Results) = 0;

    //void setObjectiveDirection(const std::string& objectiveSens);

    //virtual int solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results) = 0;
};


#define ModelerInterface_iid "Cea.MIPModeler.ModelerInterface"

Q_DECLARE_INTERFACE(ModelerInterface, ModelerInterface_iid)