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
    : mNumCols(0),
      mNumRows(0),
      mNumIntegerCols(0),
      mObjectiveDirection(MIP_MINIMIZE),
      mProblemBuilt(false),
      mModelName(modelName)
{

}
// --------------------------------------------------------------------------
void MIPModel::setObjective(const MIPExpression& objective,
                            const  MIPDirection& objectiveDirection) {
    mObjectiveExpression = objective;
    mObjectiveDirection = objectiveDirection;
}
//---------------------------------------------------------------------------
void MIPModel::setObjectiveDirection(const MIPDirection& objectiveDirection){
    mObjectiveDirection = objectiveDirection;
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
void MIPModel::buildProblem() {
    mProblemBuilt = true;

    // variables informations
    mColLowerBounds.reserve(mNumCols);
    mColUpperBounds.reserve(mNumCols);
    mColIntegers.reserve(mNumCols);
    mColNames.reserve(mNumCols);
    std::list<MIPVariable0D*>::iterator itVar = mVariables.begin();
    for (; itVar != mVariables.end(); itVar++){
        mColLowerBounds.push_back((*itVar)->getLowerBound());
        mColUpperBounds.push_back((*itVar)->getUpperBound());
        mColNames.push_back((*itVar)->getName());
        if ((*itVar)->isInteger()){
            mColIntegers.push_back((*itVar)->getColIdx());
            mNumIntegerCols ++;
        }
    }

    // objective information
    Eigen::SparseMatrix<double, Eigen::RowMajor> sprarseMatrixObjective(1, mNumCols);
    std::list<Node> objectiveNodes = mObjectiveExpression.getNode();
    sprarseMatrixObjective.setFromTriplets(objectiveNodes.begin(), objectiveNodes.end());

    double* value = sprarseMatrixObjective.valuePtr();
    int* idx = sprarseMatrixObjective.innerIndexPtr();
    mObjectiveCoefficients = new double[mNumCols]();
    for (int i = 0; i < sprarseMatrixObjective.nonZeros(); i++)
        mObjectiveCoefficients[idx[i]] = value[i];

    //constraint matrix information
    mRhs.reserve(mNumRows);
    mSense.reserve(mNumRows);
    std::list<Node> constraintNodes;
    std::list<Node> allConstraintNodes;
    std::list<MIPConstraint>::iterator itConstr = mConstraints.begin();
    for (; itConstr != mConstraints.end(); itConstr++){
        constraintNodes = itConstr->getExpression().getNode();
        allConstraintNodes.insert(allConstraintNodes.end(),
                                  constraintNodes.begin(), constraintNodes.end());
        mRhs.push_back(itConstr->getConstPart());
        mSense.push_back(itConstr->getSense());
        mRowNames.push_back(itConstr->getName());
    }

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
// --------------------------------------------------------------------------
MIPModel::~MIPModel() {
    delete (mObjectiveCoefficients) ;
    mColIntegers.clear();
    mColLowerBounds.clear();
    mColUpperBounds.clear();
    mWarmStarts.clear();
    mRhs.clear();
    mSense.clear();
    mColNames.clear();
    mRowNames.clear();
}
//---------------------------------------------------------------------------
}
