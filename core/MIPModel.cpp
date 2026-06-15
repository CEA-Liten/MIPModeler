/**
    @file MIPModel.cpp
    @version 2.0
    @author Yacine Gaoua (yacine.gaoua@cea.fr)
    @date 08/2019
*/

#include "MIPModel.h"


namespace MIPModeler {
// --------------------------------------------------------------------------
MIPModel::MIPModel(const std::string& modelName)
    : mObjectiveDirection(MIP_MINIMIZE),
      mNumCols(0),
      mNumIntegerCols(0),
      mNumRows(0),
      mNumObj(0),
      mProblemBuilt(false),
      mModelName(modelName)
{
}

void MIPModel::setExternalModeler(ModelerInterface* ap_modeler)
{
    mExternalModeler = ap_modeler;
}
// --------------------------------------------------------------------------
void MIPModel::setObjective(const MIPExpression& objective, const  MIPDirection& objectiveDirection) {
    mObjectiveExpression = objective;
    mObjectiveDirection = objectiveDirection;
    mNumObj += 1;
    std::string strName = "FirstObj";
    MIPSubobjective subObj(strName);
    double tol = 1;
    subObj.setSubObjective(mObjectiveExpression,mObjectiveDirection,0,tol,tol); //TODO : changer tolérances
    mListSubobjectives.insert(mListSubobjectives.begin(),subObj);
}
//---------------------------------------------------------------------------
void MIPModel::setObjectiveDirection(const MIPDirection& objectiveDirection){
    mObjectiveDirection = objectiveDirection;
    if (mExternalModeler) {
        ModelerParams vParam;
        vParam.addParam("ObjectiveDirection", (double)objectiveDirection);
        mExternalModeler->setParams(vParam);
    }
}
//---------------------------------------------------------------------------
void MIPModel::addSubobjective(MIPSubobjective &subobj){
    mListSubobjectives.push_back(subobj);
    mNumObj += 1;
}
// --------------------------------------------------------------------------
bool MIPModel::isMip() {
    if (mNumIntegerCols > 0 || mSOS.size() > 0)
        return true;
    return false;
}
// --------------------------------------------------------------------------
void MIPModel::add(MIPVariable0D& variable0D, const std::string& name) {
    variable0D.setColIdx(mNumCols);
    if (!name.empty())
        variable0D.setName(name);
    mVariables.insert(mVariables.end(), &variable0D);
}
// --------------------------------------------------------------------------
void MIPModel::add(MIPVariable1D& variable1D, const std::string& name) {
    variable1D.setColIdx(mNumCols);
    if (!name.empty())
        variable1D.setName(name);
    std::vector<MIPVariable0D*> variables = variable1D.getVariables();
    mVariables.insert(mVariables.end(), variables.begin(), variables.end());
}
// --------------------------------------------------------------------------
void MIPModel::add(MIPVariable2D& variable2D, const std::string& name) {
    variable2D.setColIdx(mNumCols);
    if (!name.empty())
        variable2D.setName(name);
    std::vector<MIPVariable0D*> variables = variable2D.getVariables();
    mVariables.insert(mVariables.end(), variables.begin(), variables.end());
}
// --------------------------------------------------------------------------
void MIPModel::add(MIPVariable3D& variable3D, const std::string& name) {
    variable3D.setColIdx(mNumCols);
    if (!name.empty())
        variable3D.setName(name);
    std::vector<MIPVariable0D*> variables = variable3D.getVariables();
    mVariables.insert(mVariables.end(), variables.begin(), variables.end());
}
// --------------------------------------------------------------------------
void MIPModel::add(MIPConstraint constraint, const std::string& name) {
    constraint.setRowIndex(mNumRows);
    if (!name.empty())
        constraint.setName(name);
    mConstraints.insert(mConstraints.end(), constraint);
}
// --------------------------------------------------------------------------
void MIPModel::add(const MIPSpecialOrderedSet& sos, const MIPSOSType& sosType) {
    mSOS.push_back(sos);
    mSOSType.push_back(sosType);
}
//---------------------------------------------------------------------------
void MIPModel::add(const MIPWarmStart& warmStartSolutions) {
    mWarmStarts.push_back(warmStartSolutions);
}
// --------------------------------------------------------------------------
void MIPModel::buildProblem() 
{
    mProblemBuilt = true;

    // =========================== Variables information ===========================
    mColLowerBounds.reserve(mNumCols);
    mColUpperBounds.reserve(mNumCols);
    mColIntegers.reserve(mNumCols);
    mColNames.reserve(mNumCols);

    for (auto itVar = mVariables.begin(); itVar != mVariables.end(); itVar++) 
    {
        // --- Validate lower bound ---
        if (std::isnan((*itVar)->getLowerBound())) {
            mProblemBuilt = false;
            spdlog::critical("The Lower Bound of {} is NAN!", (*itVar)->getName());
            throw std::runtime_error("Invalid model: NAN lower bound");
        }

        // --- Validate upper bound ---
        if (std::isnan((*itVar)->getUpperBound())) {
            mProblemBuilt = false;
            spdlog::critical("The Upper Bound of {} is NAN!", (*itVar)->getName());
            throw std::runtime_error("Invalid model: NAN upper bound");
        }

        mColLowerBounds.push_back((*itVar)->getLowerBound());
        mColUpperBounds.push_back((*itVar)->getUpperBound());
        mColNames.push_back((*itVar)->getName());

        // --- Validate integer variable index ---
        if ((*itVar)->isInteger()) {
            if (std::isnan(static_cast<float>((*itVar)->getColIdx()))) {
                mProblemBuilt = false;
                spdlog::critical("The index of {} is NAN!", (*itVar)->getName());
                throw std::runtime_error("Invalid model: NAN column index");
            }
            mColIntegers.push_back((*itVar)->getColIdx());
            mNumIntegerCols++;
        }
    }

    // =========================== Objective information ===========================

    Eigen::SparseMatrix<double, Eigen::RowMajor> sprarseMatrixObjective(1, mNumCols);
    std::list<Node> objectiveNodes = mObjectiveExpression.getNode();

    // --- Validate objective expression ---
    for (auto& node : objectiveNodes) {
        if (node.col() < 0 || node.row() < 0) {
            mProblemBuilt = false;
            spdlog::critical("error at the objective expression : col or row is -1");
            throw std::runtime_error("Invalid objective: negative row/col index");
        }
    }

    sprarseMatrixObjective.setFromTriplets(objectiveNodes.begin(), objectiveNodes.end());

    double* value = sprarseMatrixObjective.valuePtr();
    int* idx = sprarseMatrixObjective.innerIndexPtr();
    mObjectiveCoefficients.resize(mNumCols, 0);

    for (int i = 0; i < sprarseMatrixObjective.nonZeros(); i++) {
        if (std::isnan(value[i])) {
            mProblemBuilt = false;
            spdlog::critical("The Objective Coefficient of {} is NAN!", mColNames[idx[i]]);
            throw std::runtime_error("Invalid model: NAN objective coefficient");
        }
        mObjectiveCoefficients[idx[i]] = value[i];
    }

    /// =========================== Subobjective information ===========================

    if(mNumObj>1) {
        for(int j = 0; j<mNumObj; j++) {
            std::list<Node> objectiveNodes = mListSubobjectives[j].getSubObjectiveExpression().getNode();
            int nbNodes = objectiveNodes.size();
            mSubObjNz.push_back(nbNodes);
            mSubObjIndices.push_back(new int[nbNodes]());
            mSubObjCoeff.push_back(new double[nbNodes]());

            int i=0;
            for (auto& node : objectiveNodes) {
                mSubObjIndices[j][i] = node.col();

                // --- Validate subobjective coefficient ---
                if (std::isnan(node.value())) {
                    mProblemBuilt = false;
                    spdlog::critical("A NAN value found in subobjective: {}", mListSubobjectives[j].getName());
                    throw std::runtime_error("Invalid model: NAN subobjective coefficient");
                }

                mSubObjCoeff[j][i] = node.value();
                i++;
            }
        }
    }

    // =========================== Constraint matrix information ===========================

    mRhs.reserve(mNumRows);
    mSense.reserve(mNumRows);

    std::list<Node> allConstraintNodes;

    for (auto itConstr = mConstraints.begin(); itConstr != mConstraints.end(); ++itConstr) 
    {
        std::list<Node> constraintNodes = itConstr->getExpression().getNode();

        for (auto& node : constraintNodes) {
            // --- Validate constraint matrix ---
            if (node.row() < 0 || node.col() < 0) {
                mProblemBuilt = false;
                spdlog::critical("ERROR constraint {}: bad variable reference r {} c {} v {}",
                    itConstr->getName(),
                    node.row(),
                    node.col(),
                    node.value());
                throw std::runtime_error("Invalid constraint: negative row/col index");
            }

            if (std::isnan(node.value())) {
                mProblemBuilt = false;
                spdlog::critical("A NAN value found in constraint: {}", itConstr->getName());
                throw std::runtime_error("Invalid model: NAN constraint coefficient");
            }
        }

        allConstraintNodes.insert(allConstraintNodes.end(), constraintNodes.begin(), constraintNodes.end());

        // --- Validate constant part ---
        if (std::isnan(itConstr->getConstPart())) {
            mProblemBuilt = false;
            spdlog::critical("The Constant Part of constraint {} is NAN!", itConstr->getName());
            throw std::runtime_error("Invalid model: NAN constraint constant");
        }

        mRhs.push_back(itConstr->getConstPart());
        mSense.push_back(itConstr->getSense());
        mRowNames.push_back(itConstr->getName());
    }

    // =========================== Build constraint matrix =========================== 

    Eigen::SparseMatrix<double, Eigen::RowMajor>* sparseMatrixConstraints;
    sparseMatrixConstraints = new Eigen::SparseMatrix<double, Eigen::RowMajor>(mNumRows, mNumCols);
    sparseMatrixConstraints->setFromTriplets(allConstraintNodes.begin(), allConstraintNodes.end());

    mNonZeroElements = sparseMatrixConstraints->valuePtr();
    mIndexes = sparseMatrixConstraints->innerIndexPtr();
    mStartIndexes= sparseMatrixConstraints->outerIndexPtr();
    mNumNonZeroElements = sparseMatrixConstraints->nonZeros();

    mLengths = new int[mNumRows];
    for (int i = 0; i < mNumRows; i++)
        mLengths[i] = mStartIndexes[i + 1] - mStartIndexes[i];
}

MIPModel::~MIPModel() 
{
    mColIntegers.clear();
    mColLowerBounds.clear();
    mColUpperBounds.clear();
    mWarmStarts.clear();
    mRhs.clear();
    mSense.clear();
    mColNames.clear();
    mRowNames.clear();
    mListSubobjectives.clear();
}

}
