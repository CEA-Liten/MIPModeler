/**
    @file MIPModel.cpp
    @version 2.0
    @author Yacine Gaoua (yacine.gaoua@cea.fr)
    @date 08/2019
*/

#include "MIPModel.h"
#include <QDebug>

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
void MIPModel::add(const QObject* obj, MIPVariable0D& variable0D, const std::string& name) {
    variable0D.setColIdx(mNumCols);
    if (!name.empty())
        variable0D.setName(CName(obj, name));
    mVariables.insert(mVariables.end(), &variable0D);
}
// --------------------------------------------------------------------------
void MIPModel::add(const QObject* obj, MIPVariable1D& variable1D, const std::string& name) {
    variable1D.setColIdx(mNumCols);
    if (!name.empty())
        variable1D.setName(CName(obj,name));
    std::vector<MIPVariable0D*> variables = variable1D.getVariables();
    mVariables.insert(mVariables.end(), variables.begin(), variables.end());
}
// --------------------------------------------------------------------------
void MIPModel::add(const QObject* obj, MIPVariable2D& variable2D, const std::string& name) {
    variable2D.setColIdx(mNumCols);
    if (!name.empty())
        variable2D.setName(CName(obj, name));
    std::vector<MIPVariable0D*> variables = variable2D.getVariables();
    mVariables.insert(mVariables.end(), variables.begin(), variables.end());
}
// --------------------------------------------------------------------------
void MIPModel::add(const QObject* obj, MIPVariable3D& variable3D, const std::string& name) {
    variable3D.setColIdx(mNumCols);
    if (!name.empty())
        variable3D.setName(CName(obj, name));
    std::vector<MIPVariable0D*> variables = variable3D.getVariables();
    mVariables.insert(mVariables.end(), variables.begin(), variables.end());
}
// --------------------------------------------------------------------------
void MIPModel::add(const QObject* obj, MIPConstraint constraint, const std::string& name, const uint& t) {
    constraint.setRowIndex(mNumRows);
    if (!name.empty())
        constraint.setName(CName(obj, name, t));
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
        //Check for NAN values
        if (std::isnan((*itVar)->getLowerBound())) {
            mProblemBuilt = false;
            qCritical() << "The Lower Bound of " + QString::fromStdString((*itVar)->getName()) + " is NAN!";
        }

        if (std::isnan((*itVar)->getUpperBound())) {
            mProblemBuilt = false;
            qCritical() << "The Upper Bound of " + QString::fromStdString((*itVar)->getName()) + " is NAN!";
        }

        mColLowerBounds.push_back((*itVar)->getLowerBound());
        mColUpperBounds.push_back((*itVar)->getUpperBound());
        mColNames.push_back((*itVar)->getName());

        if ((*itVar)->isInteger()){
            if ( std::isnan(static_cast<float>( (*itVar)->getColIdx() )) ) {
                mProblemBuilt = false;
                qCritical() << "The index of " + QString::fromStdString((*itVar)->getName()) + " is NAN!";
            }
            mColIntegers.push_back((*itVar)->getColIdx());
            mNumIntegerCols ++;
        }
    }

    // objective information
    Eigen::SparseMatrix<double, Eigen::RowMajor> sprarseMatrixObjective(1, mNumCols);
    std::list<Node> objectiveNodes = mObjectiveExpression.getNode();
    //checking mObjectiveExpression
    std::list<Node>::iterator itNode;
    for (itNode = objectiveNodes.begin(); itNode != objectiveNodes.end() ; itNode++) {
        if(itNode->col() < 0 || itNode->row() < 0){
            //throw exception 
            qCritical() << "error at the nodeObjective : col val  is -1 ";
            throw (QString("An error found after checking objectiveNodes col/row val (<-1) sparseMatrixObjective ! plesae check added model"));
        }
    }
    sprarseMatrixObjective.setFromTriplets(objectiveNodes.begin(), objectiveNodes.end());

    double* value = sprarseMatrixObjective.valuePtr();
    int* idx = sprarseMatrixObjective.innerIndexPtr();
    mObjectiveCoefficients.resize(mNumCols, 0);
    for (int i = 0; i < sprarseMatrixObjective.nonZeros(); i++){
        if (std::isnan(value[i])) {
            mProblemBuilt = false;
            qCritical() << "The Objective Coefficient of " + QString::fromStdString(mColNames[i]) + " is NAN!";
        }
        mObjectiveCoefficients[idx[i]] = value[i];
    }

    // subobjective information
    if(mNumObj>1){
        for(int j = 0; j<mNumObj; j++){
            std::list<Node> objectiveNodes = mListSubobjectives[j].getSubObjectiveExpression().getNode();
            int nbNodes = objectiveNodes.size();
            mSubObjNz.push_back(nbNodes);
            mSubObjIndices.push_back(new int[nbNodes]());
            mSubObjCoeff.push_back(new double[nbNodes]());
            int i=0;
            std::list<Node>::iterator it = objectiveNodes.begin();
            for (; it != objectiveNodes.end(); it++){
                mSubObjIndices[j][i] = it->col();

                if (std::isnan(it->value())) {
                    mProblemBuilt = false;
                    qCritical() << "A NAN value found in the subobjective expression: "+QString::fromStdString(mListSubobjectives[j].getName());
                }

                mSubObjCoeff[j][i] = it->value();
                i++;
            }
        }
    }

    //constraint matrix information
    mRhs.reserve(mNumRows);
    mSense.reserve(mNumRows);
    std::list<Node> constraintNodes;
    std::list<Node> allConstraintNodes;
    std::list<MIPConstraint>::iterator itConstr = mConstraints.begin();

    for (; itConstr != mConstraints.end(); itConstr++){
        constraintNodes = itConstr->getExpression().getNode();
        for (std::list<Node>::iterator it = constraintNodes.begin(); it != constraintNodes.end(); it++)
        {
            if (it->row() <0  || it->col() <0)
            {
                qDebug()<< " == ERROR constraint == "
                        << QString::fromStdString(itConstr->getName())
                        << " reference to bad variable "
                        << " r " << it->row() << " c " << it->col() << " v " << it->value() ;

                throw (QString("An error found while building the constraint matrix: a negative row or column index is detected!"));
            }

            if (std::isnan(it->value())) {
                mProblemBuilt = false;
                qCritical() << "An NAN value found in the constraint: "+QString::fromStdString(itConstr->getName());
            }
        }
        allConstraintNodes.insert(allConstraintNodes.end(), constraintNodes.begin(), constraintNodes.end());

        if (std::isnan(itConstr->getConstPart())) {
            mProblemBuilt = false;
            qCritical() << "The Constant Part of the constraint "+QString::fromStdString(itConstr->getName())+" is NAN!" << itConstr->getConstPart();
        }

        mRhs.push_back(itConstr->getConstPart());
        mSense.push_back(itConstr->getSense());
        mRowNames.push_back(itConstr->getName());
    }

    //Throw exception -- The exception is thrown at the end in order to report all NAN values in the .log before.
    if (!mProblemBuilt)
        throw (QString("An error has found while building the optimal problem: undefined value (NAN)!"));

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

//    if (mNumCols > 0)
//      delete [] mObjectiveCoefficients ;
//    if (mNumRows > 0)
//       delete [] mLengths ;

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
//---------------------------------------------------------------------------
}
