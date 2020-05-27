/**
 * @file MIPConstraint.h
 * @brief MIP constraint definition
 * @version 2.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 07/2019
*/

#include "MIPModeler_global.h"
#include <string>
#include <vector>
#include "MIPExpression.h"

#ifndef MIPCONSTRAINT_H
#define MIPCONSTRAINT_H

namespace MIPModeler {

class MIPExpression;

class MIPMODELERSHARED_EXPORT MIPConstraint {
public:
//-----------------------------------------------------------------------------
    MIPConstraint();
    MIPConstraint(const MIPExpression& expr, const char& sense,
                  const double& val);
    virtual ~MIPConstraint();
//-----------------------------------------------------------------------------
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator == (const MIPExpression& expr, const double& val);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator == ( const double& val, const MIPExpression& expr);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator == (const MIPVariable0D& var, const double& val);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator == (const double& val, const MIPVariable0D& var);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator == (const MIPExpression& expr1, const MIPExpression& expr2);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator == (const MIPExpression& expr, const MIPVariable0D& var);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator == (const MIPVariable0D& var, const MIPExpression& expr);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator == (const MIPVariable0D& var1, const MIPVariable0D& var2);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator >= (const double& val, const MIPExpression& expr);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator >= (const MIPExpression& expr, const double& val);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator >= (const MIPVariable0D& var, const double& val);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator >= (const double& val, const MIPVariable0D& var);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator >= (const MIPExpression& expr1, const MIPExpression& expr2);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator >= (const MIPExpression& expr, const MIPVariable0D& var);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator >= (const MIPVariable0D& var, const MIPExpression& expr);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator >= (const MIPVariable0D& var1, const MIPVariable0D& var2);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator <= (const double& val, const MIPExpression& expr);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator <= (const MIPExpression& expr, const double& val);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator <= (const MIPVariable0D& var, const double& val);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator <= (const double& val, const MIPVariable0D& var);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator <= (const MIPExpression& expr1, const MIPExpression& expr2);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator <= (const MIPExpression& expr, const MIPVariable0D& var);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator <= (const MIPVariable0D& var, const MIPExpression& expr);
    friend MIPConstraint MIPMODELERSHARED_EXPORT
        operator <= (const MIPVariable0D& var1, const MIPVariable0D& var2);
//-----------------------------------------------------------------------------
    void setRowIndex(int& idx);
    void setName(const std::string& name);
//-----------------------------------------------------------------------------
    const MIPExpression& getExpression() const {return mExpression;}
    double getConstPart() const {return mValue;}
    char getSense() const {return mSense;}
    std::string getName() const {return mName;}
//-----------------------------------------------------------------------------
private:
    MIPExpression mExpression;
    double mValue;
    char mSense;
    std::string mName;
};

}
#endif /* MIPConstraint */
