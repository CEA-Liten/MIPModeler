/*
 * GAMSModeler - General Algebraic Modeling System C++ API
 *
 * Author: Yacine Gaoua
 * @mail : yacine.gaoua@cea.fr
 */

#ifndef GAMSMODEL_H
#define GAMSMODEL_H

#include <iostream>
#include <sstream>

#include "gams.h"
#include "GAMSModeler_global.h"
#include "GAMSData.h"
#include "GAMSDataSet.h"
#include "GAMSDataScalar.h"
#include "GAMSDataParam1D.h"
#include "GAMSDataParam2D.h"
#include "GAMSDataParam3D.h"

namespace GAMSModeler {

class GAMSMODELERSHARED_EXPORT GAMSModel {

    enum GAMSDirection {GAMS_MIN, GAMS_MAX};

private:
    /// Convert GAMSEnum::ModelStat to string.
    /// \param modelStat: GAMSEnum::ModelStat.
    /// \return Return model status.
    const char* text(gams::GAMSEnum::ModelStat modelStat) {
        switch (modelStat) {
            ///< Optimal solution achieved
            case gams::GAMSEnum::ModelStat::OptimalGlobal:        return "OptimalGlobal";
            ///< Local optimal solution achieved
            case gams::GAMSEnum::ModelStat::OptimalLocal:         return "OptimalLocal";
            ///< Unbounded model found
            case gams::GAMSEnum::ModelStat::Unbounded:            return "Unbounded";
            ///< Infeasible model found
            case gams::GAMSEnum::ModelStat::InfeasibleGlobal:     return "InfeasibleGlobal";
                ///< Locally infeasible model found
            case gams::GAMSEnum::ModelStat::InfeasibleLocal:      return "InfeasibleLocal";
            ///< Solver terminated early and model was still infeasible
            case gams::GAMSEnum::ModelStat::InfeasibleIntermed:   return "InfeasibleIntermed";
            ///< Feasible solution
            case gams::GAMSEnum::ModelStat::Feasible:             return "Feasible";
            ///< Integer solution found
            case gams::GAMSEnum::ModelStat::IntegerSolution:      return "IntegerSolution";
            ///< Solver terminated early with a non integer solution found
            case gams::GAMSEnum::ModelStat::NonIntegerIntermed:   return "NonIntegerIntermed";
            ///< No feasible integer solution could be found
            case gams::GAMSEnum::ModelStat::IntegerInfeasible:    return "IntegerInfeasible";
            ///< Licensing problem
            case gams::GAMSEnum::ModelStat::LicenseError:         return "LicenseError";
            ///< Error - No cause known
            case gams::GAMSEnum::ModelStat::ErrorUnknown:         return "ErrorUnknown";
            ///< Error - No solution attained
            case gams::GAMSEnum::ModelStat::ErrorNoSolution:      return "ErrorNoSolution";
            ///< No solution returned
            case gams::GAMSEnum::ModelStat::NoSolutionReturned:   return "NoSolutionReturned";
            ///< Unique solution in a CNS models
            case gams::GAMSEnum::ModelStat::SolvedUnique:         return "SolvedUnique";
            ///< Feasible solution in a CNS models
            case gams::GAMSEnum::ModelStat::Solved:               return "Solved";
            ///< Singular in a CNS models
            case gams::GAMSEnum::ModelStat::SolvedSingular:       return "SolvedSingular";
            ///< Unbounded - no solution
            case gams::GAMSEnum::ModelStat::UnboundedNoSolution:  return "UnboundedNoSolution";
            ///< Infeasible - no solution
            case gams::GAMSEnum::ModelStat::InfeasibleNoSolution: return "InfeasibleNoSolution";

            default: return "Invalid ModelStat" ;
        }
    }

    /// Convert GAMSEnum::SolveStat to string.
    /// \param modelStat: GAMSEnum::SolveStat.
    /// \return Return solve status.
    const char* text(gams::GAMSEnum::SolveStat solveStat) {
        switch (solveStat) {
            /// Normal termination
            case gams::GAMSEnum::SolveStat::Normal:          return "Normal";
            /// Solver ran out of iterations
            case gams::GAMSEnum::SolveStat::Iteration:       return "Iteration";
            /// Solver exceeded time limit
            case gams::GAMSEnum::SolveStat::Resource:        return "Resource";
            /// Solver quit with a problem
            case gams::GAMSEnum::SolveStat::Solver:          return "Solver";
            /// Solver quit with nonlinear term evaluation errors
            case gams::GAMSEnum::SolveStat::EvalError:       return "EvalError";
            /// Solver terminated because the model is beyond the solvers capabilities
            case gams::GAMSEnum::SolveStat::Capability:      return "Capability";
            /// Solver terminated with a license error
            case gams::GAMSEnum::SolveStat::License:         return "License";
            /// Solver terminated on users request (e.g. Ctrl-C)
            case gams::GAMSEnum::SolveStat::User:            return "User";
            /// Solver terminated on setup error
            case gams::GAMSEnum::SolveStat::SetupErr:        return "SetupErr";
            /// Solver terminated with error
            case gams::GAMSEnum::SolveStat::SolverErr:       return "SolverErr";
            /// Solver terminated with error
            case gams::GAMSEnum::SolveStat::InternalErr:     return "InternalErr";
            /// Solve skipped
            case gams::GAMSEnum::SolveStat::Skipped:         return "Skipped";
            /// Other error
            case gams::GAMSEnum::SolveStat::SystemErr:       return "SystemErr";

            default: return "Invalid SolveStat" ;
        }
    }

private:
    void addArg() { }

    template <typename  T>
    void addArg(const T& arg)
    {
        std::stringstream ss;
        ss << " " << arg;
        mGMSModel += ss.str();
    }

    template <typename  First, typename  Second, typename ... Rest>
    void addArg(const First& first, const Second& second, const Rest&... modelOption)
    {
        std::stringstream ss;
        ss << " " <<first << " " << second;
        mGMSModel += ss.str();
        addArg(modelOption...);
    }

public:
    /// Standard constructor.
    /// \param gams working directory
    GAMSModel(const std::string& workingDir = "./");

    /// Desctructor.
    ~GAMSModel();

    /// Include gams file with arg <$batinclude>.
    /// \param gms file name.
    /// \param model name.
    /// \param model options if exist.
    template <typename  First, typename  Second, typename ... Rest>
    void addModelFromFile(const First& fileName, const Second& modelName, const Rest&... modelOption)
    {
        std::stringstream ss;
        ss <<"\n$\t batInclude " << fileName << " " << modelName;
        mGMSModel += ss.str();
        addArg(modelOption...);
    }

    /// Add gams data.
    /// \param gams datas <GAMSSet, GAMSScalar, GAMSParam1d, GAMSParam2d, GAMSParam3d>
    void addData(std::vector<GAMSData*>& data, const bool& importToGMS=false);

    /// Add text comment in gams file.
    /// \param text comment.
    void addComment(const std::string& text);
	
	/// Add text comment in gams file.
    /// \param text comment.
    void addText(const std::string& text);

    /// Set number of thread for solve.
    /// \param number of threads <default value is 0>.
    void setThreads(const int& threads);

    /// Set relative GAP for solve.
    /// \param relative GAP <default value is 1e-4>.
    void setGap(const double& gap);

    /// Set time limit for solve.
    /// \param time limit in seconds <default value is 1e+8>.
    void setTimeLimit(const double& timeLimit);

    /// Set objective direction.
    /// \param objective sense <default value is "min">.
    void setObjectiveDirection(const std::string& objectiveSens);

    /// Set solver name.
    /// \param solver name <default value is "cplex">.
    void setSolver(const std::string& solverName);

    /// Set problem type.
    /// \param problem type lpn mip, nlp, dnlp, minlp, miqcp, ... <default value is "mip">.
    void setProblemType(const std::string& problemType);

    /// Build optimization problem.
    void buildProblem();

    /// Solve optimization problem.
    void solve();

    /// Get gams job.
    /// \return Return gams job to read optimization results.
    gams::GAMSJob getJob() const {return mJob;}

    /// Get gams model status.
    /// \return Return model status <see GAMSEnum::ModelStat>.
    std::string getModelStatus();

    /// Get gams solve status.
    /// \return Return solve status <see GAMSEnum::SolveStat>.
    std::string getSolveStatus();

    /// Get optimal value of variable.
    /// \param gams variable name.
    /// \param Return optimal value of variable <only 0d and 1d, Nd to be added if necessaty>.
    double* getOptValue(const std::string& varName);

    /// Export gams database.
    /// \param gdx file name to be exported from created gams database.
    void exportDataBase(const std::string& GDXfilename);

    /// Export the created gams file that correspond to the global optimization problem.
    /// \param gams file name of global optimization problem to be exported.
    void exportGMSModel(const std::string& GMSfilename);

    /// Clear gams database.
    void clear();

private:
        std::vector<std::string> mDataLabels;
        gams::GAMSWorkspace mWorkSpace;
        gams::GAMSDatabase mDataBase;
        gams::GAMSJob mJob;
        std::string mGMSModel;
        std::string mProblemType;
        std::string mSolverName;
        int mThreads;
        double mGap;
        double mTimeLimit;
        GAMSDirection mObjectiveSens;
};
}

#endif // GAMSMODEL_H
