#include "GAMSModel.h"
#include <fstream>
#include <QDebug>

namespace GAMSModeler {

GAMSModel::GAMSModel(const std::string& workingDir) :
    mGMSModel(""),
    mProblemType("MIP"),
    mSolverName("CPLEX"),
    mThreads(0),
    mGap(1e-4),
    mTimeLimit(1e+8),
    mObjectiveSens(GAMS_MIN)

{
    mWorkSpace = gams::GAMSWorkspace(workingDir);
    mDataBase  = mWorkSpace.addDatabase();
}

void GAMSModel::addData(std::vector<GAMSData*>& data, const bool& exportToGMS)
{
    std::vector<std::string> dataNames;

    for (size_t ii=0; ii < data.size (); ii++) {

        if (std::find(mDataLabels.begin(), mDataLabels.end(), data[ii]->name()) == mDataLabels.end()) {
            if (data[ii]->type() == GAMSDataType::GAMS_SET) {
                GAMSDataSet* x = dynamic_cast<GAMSDataSet*>(data[ii]);
                std::vector<std::string> reccords = x->getReccords();
                gams::GAMSSet set = mDataBase.addSet(data[ii]->name(), 1, "");
                for (std::string rec: reccords)
                    set.addRecord(rec);
            }

            if (data[ii]->type() == GAMSDataType::GAMS_SCALAR) {
                GAMSDataScalar* x = dynamic_cast<GAMSDataScalar*>(data[ii]);
                gams::GAMSParameter param = mDataBase.addParameter(data[ii]->name(), "");
                param.addRecord().setValue(x->getValue());
            }

            if (data[ii]->type() == GAMSDataType::GAMS_PARAM1D) {
                GAMSDataParam1D* x = dynamic_cast<GAMSDataParam1D*>(data[ii]);
                std::vector<double> values = x->getValue();
                gams::GAMSSet set = mDataBase.getSet(x->getSet());
                gams::GAMSParameter param = mDataBase.addParameter(data[ii]->name(), "", set);
                int i = 0;
                for (gams::GAMSSetRecord rec : set){
                     param.addRecord(rec.key(0)).setValue(values[i]);
                     i++;
                }
            }

            if (data[ii]->type() == GAMSDataType::GAMS_PARAM2D) {
                GAMSDataParam2D* x = dynamic_cast<GAMSDataParam2D*>(data[ii]);
                std::vector<std::vector<double>> values = x->getValue();
                std::vector<std::string> sets = x->getSet();
                gams::GAMSSet set1 = mDataBase.getSet(sets[0]);
                gams::GAMSSet set2 = mDataBase.getSet(sets[1]);
                gams::GAMSParameter param = mDataBase.addParameter(data[ii]->name(), "", set1, set2);
                int i = 0;
                for (gams::GAMSSetRecord rec1 : set1){
                    int j = 0;
                    for (gams::GAMSSetRecord rec2 : set2){
                        param.addRecord(rec1.key(0), rec2.key(0)).setValue(values[i][j]);
                        j++;
                    }
                    i++;
                }
            }

            if (data[ii]->type() == GAMSDataType::GAMS_PARAM3D) {
                GAMSDataParam3D* x = dynamic_cast<GAMSDataParam3D*>(data[ii]);
                std::vector<std::vector<std::vector<double>>> values = x->getValue();
                std::vector<std::string> sets = x->getSet();
                gams::GAMSSet set1 = mDataBase.getSet(sets[0]);
                gams::GAMSSet set2 = mDataBase.getSet(sets[1]);
                gams::GAMSSet set3 = mDataBase.getSet(sets[2]);
                gams::GAMSParameter param = mDataBase.addParameter(data[ii]->name(), "", set1, set2, set3);
                int i = 0;
                for (gams::GAMSSetRecord rec1 : set1){
                    int j = 0;
                    for (gams::GAMSSetRecord rec2 : set2){
                        int k = 0;
                        for (gams::GAMSSetRecord rec3 : set3){
                            param.addRecord(rec1.key(0), rec2.key(0), rec3.key(0)).setValue(values[i][j][k]);
                            k++;
                        }
                        j++;
                    }
                    i++;
                }
            }

            dataNames.push_back (data[ii]->name());
            mDataLabels.push_back(data[ii]->name());
        }
    }

    if (exportToGMS)
    {
        mGMSModel += "\n$\t gdxin %inputGDXData% \n";
        for (size_t ii=0; ii < dataNames.size (); ii++)
            mGMSModel += "$\t load " + dataNames[ii] + "\n";
        mGMSModel += "$\t gdxin";
    }
    dataNames.clear ();
}

void GAMSModel::addComment(const std::string& text)
{
    mGMSModel += "\n*" + text;
}

void GAMSModel::addText(const std::string& text)
{
    mGMSModel += "\n" + text;
}

void GAMSModel::setThreads(const int& threads)
{
    mThreads = threads;
}

void GAMSModel::setGap(const double& gap)
{
    mGap = gap;
}

void GAMSModel::setTimeLimit(const double& timeLimit)
{
    mTimeLimit = timeLimit;
}

void GAMSModel::setObjectiveDirection(const std::string& objectiveSens)
{
    if ((objectiveSens == "min") || (objectiveSens == "Min") || (objectiveSens == "MIN"))
        mObjectiveSens = GAMSDirection::GAMS_MIN;
    if ((objectiveSens == "max") || (objectiveSens == "Max") || (objectiveSens == "MAX"))
        mObjectiveSens = GAMSDirection::GAMS_MAX;
}

void GAMSModel::setSolver(const std::string& solverName)
{
    mSolverName = solverName;
}

void GAMSModel::setProblemType(const std::string& problemType)
{
    mProblemType = problemType;
}

void GAMSModel::buildProblem()
{
    mGMSModel += "\n*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
                 "*+++++++++++++++++++++++++ SOLVE ++++++++++++++++++++++++++++++++++ \n"
                 "*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ \n"
                 "Scalars \n"
                 "\tModelStat\n"
                 "\tSolveStat \n;\n"
                 "Model Problem /all/ ;\n"
                 "Option " + mProblemType + " = " + mSolverName + ";\n";

    if (mObjectiveSens == GAMSDirection::GAMS_MAX)
        mGMSModel += "Solve Problem Using " + mProblemType + " Maximizing Problem_v_Objective ;\n";
    if (mObjectiveSens == GAMSDirection::GAMS_MIN)
        mGMSModel += "Solve Problem Using " + mProblemType + " Minimizing Problem_v_Objective ;\n";

    mGMSModel += "ModelStat = Problem.modelstat ;\n"
                 "SolveStat = Problem.solvestat ;\n";
}

void GAMSModel::solve()
{
    mJob = mWorkSpace.addJobFromString(mGMSModel);
    gams::GAMSOptions option = mWorkSpace.addOptions();
    option.setDefine("inputGDXData", mDataBase.name());
    option.setAllModelTypes(mSolverName);
    option.setETLim(mTimeLimit);
    option.setOptCR(mGap);
    option.setThreads(mThreads);
    mJob.run(option, mDataBase);
}

std::string GAMSModel::getModelStatus()
{
    int status = int(mJob.outDB().getParameter("ModelStat").firstRecord().value());

    return text(gams::GAMSEnum::ModelStat(status));
}

std::string GAMSModel::getSolveStatus()
{
    int status = int(mJob.outDB().getParameter("SolveStat").firstRecord().value());

    return text(gams::GAMSEnum::SolveStat(status));
}

double* GAMSModel::getOptValue(const std::string& varName)
{
    try {
        gams::GAMSVariable GAMSVar = mJob.outDB().getVariable(varName);

        double* optValue;

        if (GAMSVar.dim() == 0) {
            optValue = new double[1];
            optValue[0] = GAMSVar.firstRecord().level();
        }

        if (GAMSVar.dim() == 1) {
            int i = 0;
            std::vector<gams::GAMSDomain> domain = GAMSVar.domains();
            int size = domain[0].getSet().numberRecords();
            optValue = new double[size];
            for (gams::GAMSVariableRecord rec : GAMSVar) {
                optValue[i] = rec.level();
                i++;
            }
        }
        return optValue;
    }
    catch (...) {
        return nullptr;
    }
}

void GAMSModel::clear()
{
    mGMSModel = "";
    mDataLabels.clear();
    mDataBase.clear();
}

void GAMSModel::exportDataBase(const std::string& GDXfilename)
{
    mDataBase.doExport(GDXfilename);
}

void GAMSModel::exportGMSModel(const std::string& GMSfilename)
{
    std::ofstream file(GMSfilename.c_str());
    file << mGMSModel;
    file.close();
}

GAMSModel::~GAMSModel()
{
    mGMSModel = "";
    mDataLabels.clear();
    mDataBase.clear();
}

}

