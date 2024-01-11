/**
 * @file MIPExpression.h
 * @brief MIP expression definition
 * @version 1.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 07/2019
*/

#include "MIPModeler_global.h"
#include "MIPVariable0D.h"
#include <Eigen/SparseCore>
#include <list>

typedef Eigen::Triplet<double> Node;

#ifndef MIPEXPRESSION_H
#define MIPEXPRESSION_H

namespace MIPModeler {

class MIPVariable0D;

class MIPMODELERSHARED_EXPORT MIPExpression {
public:
//-----------------------------------------------------------------------------
    MIPExpression(const double& constPart = 0.0);
    virtual ~MIPExpression();
//-----------------------------------------------------------------------------
    MIPExpression& operator += (const double& val);
    MIPExpression& operator += (const MIPVariable0D& var);
    MIPExpression& operator += (const MIPExpression& expr);
    MIPExpression& operator -= (const double& val);
    MIPExpression& operator -= (const MIPVariable0D& var);
    MIPExpression& operator -= (const MIPExpression& expr);
    MIPExpression& operator *= (const double& val);
    MIPExpression& operator /= (const double& val);
    MIPExpression& operator = (const MIPExpression& expr);
    MIPExpression& operator = (const MIPVariable0D& var);
    MIPExpression& operator = (const double& val);
//-----------------------------------------------------------------------------
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator * (const MIPVariable0D& var, const double& val);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator * (const double& val, const MIPVariable0D& var);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator * (const double& val, const MIPExpression& var);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator * (const MIPExpression& expr, const double& val);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator / (const MIPExpression& expr, const double& val);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator / (const MIPVariable0D& var, const double& val);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator + (const MIPExpression& expr, const MIPVariable0D& var);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator + (const MIPVariable0D& var, const MIPExpression& expr);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator + (const MIPExpression& expr1, const MIPExpression& expr2);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator + (const MIPVariable0D& var1, const MIPVariable0D& var2);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator + (const MIPExpression& expr, const double& val);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator + (const double& val, const MIPExpression& expr);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator + (const double& val, const MIPVariable0D& var);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator + (const MIPVariable0D& var, const double& val);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator - (const MIPExpression& expr, const MIPVariable0D& var);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator - (const MIPVariable0D& var, const MIPExpression& expr);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator - (const MIPExpression& expr1, const MIPExpression& expr2);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator - (const MIPVariable0D& var1, const MIPVariable0D& var2);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator - (const MIPExpression& expr, const double& val);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator - (const double& val, const MIPExpression& expr);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator - (const double& val, const MIPVariable0D& var);
    friend MIPExpression MIPMODELERSHARED_EXPORT
        operator - (const MIPVariable0D& var, const double& val);
//-----------------------------------------------------------------------------
    void setRowIndex(int& idx);
//-----------------------------------------------------------------------------
    std::list<Node>const& getNode() const {return mNodes;}
    double getConstPart() const {return mConstPart;}
//-----------------------------------------------------------------------------
    const double evaluate(const double*) const;
    MIPExpression& close();
//-----------------------------------------------------------------------------
private:
    std::list<Node> mNodes;
    double mConstPart;
};

#if  !defined(WIN32) &&  !defined(_WIN32)
MIPExpression operator * (const MIPVariable0D& var, const double& val);
MIPExpression operator * (const double& val, const MIPVariable0D& var);
MIPExpression operator * (const double& val, const MIPExpression& var);
MIPExpression operator * (const MIPExpression& expr, const double& val);
MIPExpression operator / (const MIPExpression& expr, const double& val);
MIPExpression operator / (const MIPVariable0D& var, const double& val);
MIPExpression operator + (const MIPExpression& expr, const MIPVariable0D& var);
MIPExpression operator + (const MIPVariable0D& var, const MIPExpression& expr);
MIPExpression operator + (const MIPExpression& expr1, const MIPExpression& expr2);
MIPExpression operator + (const MIPVariable0D& var1, const MIPVariable0D& var2);
MIPExpression operator + (const MIPExpression& expr, const double& val);
MIPExpression operator + (const double& val, const MIPExpression& expr);
MIPExpression operator + (const double& val, const MIPVariable0D& var);
MIPExpression operator + (const MIPVariable0D& var, const double& val);
MIPExpression operator - (const MIPExpression& expr, const MIPVariable0D& var);
MIPExpression operator - (const MIPVariable0D& var, const MIPExpression& expr);
MIPExpression operator - (const MIPExpression& expr1, const MIPExpression& expr2);
MIPExpression operator - (const MIPVariable0D& var1, const MIPVariable0D& var2);
MIPExpression operator - (const MIPExpression& expr, const double& val);
MIPExpression operator - (const double& val, const MIPExpression& expr);
MIPExpression operator - (const double& val, const MIPVariable0D& var);
MIPExpression operator - (const MIPVariable0D& var, const double& val);
#endif

}
#endif /* MIPExpression */
