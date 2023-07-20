#pragma once
#include <QtPlugin>

class ModelerParams {
public:
    enum eParamType { eScalar=0, eBool=1, eString=2, eVector=3, eStrings=4 };
    struct ModelerParam {                
        eParamType type;
        double value;
        bool flag;
        std::string str;
        std::vector<double> values;
        std::vector<std::string> strs;

        ModelerParam() { type = eScalar; value = 0; str = ""; flag = false; };
        ~ModelerParam() {};
    };
    typedef std::map<std::string, ModelerParam >  t_MIPModelerParams;

    ModelerParams() {}
    void addParam(const std::string& a_Name, const std::string& a_Value) { m_Params[a_Name].type = eString; m_Params[a_Name].str = a_Value; }
    void addParam(const std::string& a_Name, const double& a_Value) { m_Params[a_Name].type = eScalar; m_Params[a_Name].value = a_Value; }
    void addParam(const std::string& a_Name, const bool& a_Value) { m_Params[a_Name].type = eBool; m_Params[a_Name].flag = a_Value; }
    void addParam(const std::string& a_Name, const std::vector<double>& a_Value) { m_Params[a_Name].type = eVector;  m_Params[a_Name].values = a_Value; }
    void addParam(const std::string& a_Name, const std::string& a_setName, const std::vector<double>& a_Value) { m_Params[a_Name].type = eVector;  m_Params[a_Name].values = a_Value; m_Params[a_Name].str = a_setName;  }
    void addParam(const std::string& a_Name, const std::vector<std::string>& a_Value) { m_Params[a_Name].type = eStrings;  m_Params[a_Name].strs = a_Value; }


    t_MIPModelerParams::const_iterator find(const std::string& a_Name) const { return m_Params.find(a_Name); }
    t_MIPModelerParams::const_iterator begin() const { return m_Params.begin(); }
    t_MIPModelerParams::const_iterator end() const { return m_Params.end(); }
protected:
    t_MIPModelerParams m_Params; // mapping name, value
};

class ModelerResults {
public:
    ModelerResults() {}
    const std::string& getModelStatus() { return m_ModelStatus; }
    const std::string& getSolverStatus() { return m_SolverStatus; }

    void setResults(const std::string& a_ModelStatus, const std::string& a_SolverStatus)
    {
        m_ModelStatus = a_ModelStatus;
        m_SolverStatus = a_SolverStatus;
    }
protected:
    std::string m_ModelStatus;
    std::string m_SolverStatus;
};


class ModelerInterface {
public:
    virtual ~ModelerInterface() {}
    virtual std::string Infos() = 0;

    // model
    virtual void init(const ModelerParams& a_params) = 0;
    virtual void setParams(const ModelerParams& a_params) = 0;
    virtual void setModelData(const ModelerParams& a_params) = 0;

    // solver
    virtual int solve(const ModelerParams& a_Params, ModelerResults& a_Results) = 0;
    virtual double* getOptValue(const std::string& varName) = 0;

    virtual void addComment(const std::string& text) = 0;
    virtual void addText(const std::string& text) = 0;
    virtual void addData(const std::vector<std::string&>& data, const bool& importToGMS = false) = 0;

    virtual void addModelFromFile(const std::string& fileName, const std::string& modelName, const ModelerParams& a_params) = 0;

    // solver
    //virtual int solve(const SolverParams& a_Params, SolverResults& a_Results) = 0;

    //void setObjectiveDirection(const std::string& objectiveSens);

    //virtual int solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results) = 0;
};


#define ModelerInterface_iid "Cea.MIPModeler.ModelerInterface"

Q_DECLARE_INTERFACE(ModelerInterface, ModelerInterface_iid)