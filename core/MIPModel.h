/**
 * @file MIPModel.h
 * @brief MIP model definition
 * @version 2.0
 *  @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 08/2019
*/

#include "MIPModeler_global.h"
#include <string>
#include "MIPVariable0D.h"
#include "MIPVariable1D.h"
#include "MIPVariable2D.h"
#include "MIPVariable3D.h"
#include "MIPExpression.h"
#include "MIPConstraint.h"
#include "MIPSubobjective.h"
#include "MIPSpecialOrderedSet.h"
#include "MIPWarmStart.h"
#include <Eigen/SparseCore>

#include "ModelerInterface.h"

#ifndef MIPMODEL_H
#define MIPMODEL_H

namespace MIPModeler {

class MIPVariable0D;
class MIPVariable1D;
class MIPVariable2D;
class MIPVariable3D;
class MIPExpression;
class MIPConstraint;
class MIPSpecialOrderedSet;
class MIPWarmStart;
class MIPSubobjective;

#ifndef MIPDIRECTION
#define MIPDIRECTION
enum MIPDirection { MIP_MINIMIZE = 1, MIP_MAXIMIZE = -1 };
#endif

#ifndef MIPSOSTYPE
#define MIPSOSTYPE
enum MIPSOSType { MIP_SOS1 = '1', MIP_SOS2 = '2' };
#endif

class MIPMODELERSHARED_EXPORT MIPModel {
public:
// --------------------------------------------------------------------------
    MIPModel(const std::string& modelName = "");
    virtual ~MIPModel();
    void setExternalModeler(ModelerInterface *ap_modeler);
    ModelerInterface* getExternalModeler() { return mExternalModeler; }
// --------------------------------------------------------------------------
    void add(MIPVariable0D& variable0D, const std::string& name = "");
    void add(MIPVariable1D& variable1D, const std::string& name = "");
    void add(MIPVariable2D& variable2D, const std::string& name = "");
    void add(MIPVariable3D& variable3D, const std::string& name = "");
    void add(MIPConstraint constraint, const std::string& name = "");
    void add(const MIPSpecialOrderedSet& sos, const MIPSOSType& sosType);
    void add(const MIPWarmStart& warmStartSolution);
//---------------------------------------------------------------------------
    void buildProblem();
//---------------------------------------------------------------------------
    bool isMip();
    bool isProblemBuilt() const {return mProblemBuilt;}
// --------------------------------------------------------------------------
    void setObjective(const MIPExpression& objective = MIPExpression(),
                      const MIPDirection& objectiveDirection = MIP_MINIMIZE);
    void setObjectiveDirection(const MIPDirection& objectiveDirection);
    void addSubobjective(MIPSubobjective& subobj);
// --------------------------------------------------------------------------
    int getNumCols() const {return mNumCols;}
    int getNumRows() const {return mNumRows;}
    int getNumIntegerCols() const {return mNumIntegerCols;}
    int getNumNonZeroElements() const {return mNumNonZeroElements;}
    MIPDirection getObjectiveDirection() const {return mObjectiveDirection;}
    std::vector<MIPSpecialOrderedSet> const& getSOS() const {return mSOS;}
    std::vector<MIPSOSType> const& getSOSType() const {return mSOSType;}
    std::vector<std::string> const& getColNames() const {return mColNames;}
    std::vector<std::string> const& getRowNames() const {return mRowNames;}
    std::string const getModelName() const {return mModelName;}
    std::vector<MIPWarmStart> const& getWarmStarts() const {return mWarmStarts;}
// --------------------------------------------------------------------------
    const double* getObjectiveCoefficients() const {return mObjectiveCoefficients.data();}
    const double* getNonZeroElements() const {return mNonZeroElements;}
    const int* getIndexes() const {return mIndexes;}
    const int* getStartIndexes() const {return mStartIndexes;}
    const int* getLengths() const {return mLengths;}
    const double* getColUpperBounds() const {return mColUpperBounds.data();}
    const double* getColLowerBounds() const {return mColLowerBounds.data();}
    const int* getColIntegers() const {return (mNumIntegerCols>0 ? mColIntegers.data(): nullptr);}
    const double* getRhs() const {return mRhs.data();}
    const char* getSense() const {return mSense.data();}
    const int* getNumSubobj() const {return  &mNumObj;}
    const std::vector<MIPSubobjective> getListSubobjectives() const {return mListSubobjectives;}
    const std::vector<double*> getSubobjectiveCoefficients() const {return mSubObjCoeff;}
    const std::vector<int*> getSubobjectiveIndices() const {return mSubObjIndices;}
    const std::vector<double> &getColUpperBoundsVec() const { return mColUpperBounds; }
    const std::vector<double> &getColLowerBoundsVec() const { return mColLowerBounds; }
    const std::vector<double> &getObjectiveCoefficientsVec() const { return mObjectiveCoefficients; }
// --------------------------------------------------------------------------
private:
    MIPExpression mObjectiveExpression;
    MIPDirection mObjectiveDirection;
    std::list<MIPVariable0D*> mVariables;
    std::list<MIPConstraint> mConstraints;
    std::vector<MIPSpecialOrderedSet> mSOS;
    std::vector<MIPSOSType> mSOSType;
    std::vector<MIPSubobjective> mListSubobjectives;

    int mNumCols;
    int mNumIntegerCols;
    int mNumRows;
    int mNumNonZeroElements;
    int mNumObj;

    std::vector<int> mColIntegers;
    std::vector<double> mColLowerBounds;
    std::vector<double> mColUpperBounds;
    std::vector<MIPWarmStart> mWarmStarts;
    std::vector<double> mRhs;
    std::vector<char> mSense;
    std::vector<std::string> mColNames;
    std::vector<std::string> mRowNames;

    std::vector<double> mObjectiveCoefficients;
    double* mNonZeroElements;
    std::vector<int> mSubObjNz;
    int mObjNz;
    std::vector<int*> mSubObjIndices;
    int* mObjIndices;
    double* mObjCoeff;
    std::vector<double*> mSubObjCoeff;
    int* mIndexes;
    int* mStartIndexes;
    int* mLengths;

    bool mProblemBuilt;

    std::string mModelName;
    ModelerInterface* mExternalModeler{ nullptr };
};

}
#endif /* MIPModel */
