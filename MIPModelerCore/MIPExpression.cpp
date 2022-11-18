/**
    @file MIPExpression.cpp
    @version 1.0
    @author Yacine Gaoua (yacine.gaoua@cea.fr)
    @date 07/2019
*/

#include "MIPExpression.h"

namespace MIPModeler {
//---------------------------------------------------------------------------
MIPExpression::MIPExpression(const double& constPart)
    : mConstPart(constPart)
{

}
//---------------------------------------------------------------------------
void MIPExpression::setRowIndex(int& idx) {
    std::list<Node>::iterator it = mNodes.begin();
    for (; it != mNodes.end(); it++)
    	*it = Eigen::Triplet<double>(idx,it->col(),it->value());
}
//---------------------------------------------------------------------------
MIPExpression operator * (const MIPVariable0D& var, const double& val) {
    MIPExpression temp;
    if (val != 0) {
        temp += var;
        temp *= val;
    }
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator * (const double& val, const MIPVariable0D& var) {
    MIPExpression temp;
    if (val != 0) {
        temp += var;
        temp *= val;
    }
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator * (const MIPExpression& expr, const double& val) {
    MIPExpression temp;
    if (val != 0) {
        temp += expr;
        temp *= val;
    }
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator * (const double& val, const MIPExpression& expr) {
    MIPExpression temp;
    if (val != 0) {
        temp += expr;
        temp *= val;
    }
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator / (const MIPExpression& expr, const double& val) {
    MIPExpression temp = expr;
    temp /= val;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator / (const MIPVariable0D& var, const double& val) {
    MIPExpression temp;
    temp += var;
    temp /= val;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator + (const MIPExpression& expr, const MIPVariable0D& var) {
    MIPExpression temp = expr;
    temp += var;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator + (const MIPVariable0D& var, const MIPExpression& expr) {
    MIPExpression temp = expr;
    temp += var;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator + (const MIPExpression& expr1, const MIPExpression& expr2) {
    MIPExpression temp = expr1;
    temp += expr2;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator + (const MIPVariable0D& var1, const MIPVariable0D& var2) {
    MIPExpression temp;
    temp += var1;
    temp += var2;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator + (const MIPVariable0D& var, const double& val) {
    MIPExpression temp;
    temp += var;
    temp.mConstPart += val;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator + (const double& val, const MIPVariable0D& var) {
    MIPExpression temp;
    temp += var;
    temp.mConstPart += val;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator + (const MIPExpression& expr, const double& val) {
    MIPExpression temp = expr;
    temp.mConstPart += val;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator + (const double& val, const MIPExpression& expr) {
    MIPExpression temp = expr;
    temp.mConstPart += val;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator - (const MIPExpression& expr, const MIPVariable0D& var) {
    MIPExpression temp = expr;
    temp -= var;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator - (const MIPVariable0D& var, const MIPExpression& expr) {
    MIPExpression temp;
    temp += var;
    temp -= expr;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator - (const MIPExpression& expr1, const MIPExpression& expr2) {
    MIPExpression temp = expr1;
    temp -= expr2;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator - (const MIPVariable0D& var1, const MIPVariable0D& var2) {
    MIPExpression temp;
    temp += var1;
    temp -= var2;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator - (const MIPVariable0D& var, const double& val) {
    MIPExpression temp;
    temp += var;
    temp.mConstPart -= val;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator - (const double& val, const MIPVariable0D& var) {
    MIPExpression temp;
    temp -= var;
    temp.mConstPart += val;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator - (const MIPExpression& expr, const double& val) {
    MIPExpression temp = expr;
    temp.mConstPart -= val;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression operator - (const double& val, const MIPExpression& expr) {
    MIPExpression temp = expr;
    temp *= -1;
    temp.mConstPart += val;
    return temp;
}
//---------------------------------------------------------------------------
MIPExpression& MIPExpression::operator *= (const double& val) {
    std::list<Node>::iterator it = mNodes.begin();
    for (; it != mNodes.end(); ++it)
    	*it = Eigen::Triplet<double>(it->row(),it->col(),it->value()*val);
    mConstPart *= val;
    return *this;
}
//---------------------------------------------------------------------------
MIPExpression& MIPExpression::operator /= (const double& val) {
    std::list<Node>::iterator it = mNodes.begin();
    for (; it != mNodes.end(); it++)
    	*it = Eigen::Triplet<double>(it->row(),it->col(),it->value()/val);
    mConstPart /= val;
    return *this;
}
//---------------------------------------------------------------------------
MIPExpression& MIPExpression::operator += (const MIPVariable0D& var) {
    mNodes.push_back(Node(0, var.getColIdx(), 1.0));
    return *this;
}
//---------------------------------------------------------------------------
MIPExpression& MIPExpression::operator += (const MIPExpression& expr) {
    std::list<Node> nodes = expr.getNode();
    mNodes.insert(mNodes.end(), nodes.begin(), nodes.end());
    mConstPart += expr.mConstPart;
    return *this;
}
//---------------------------------------------------------------------------
MIPExpression& MIPExpression::operator += (const double& val) {
    mConstPart += val;
    return *this;
}
//---------------------------------------------------------------------------
MIPExpression& MIPExpression::operator -= (const MIPVariable0D& var) {
    mNodes.push_back(Node(0, var.getColIdx(), -1.0));
    return *this;
}
//---------------------------------------------------------------------------
MIPExpression& MIPExpression::operator -= (const MIPExpression& expr) {
    std::list<Node> nodes = expr.getNode();
    std::list<Node>::iterator it = nodes.begin();
    for (; it != nodes.end(); it++)
    	*it = Eigen::Triplet<double>(it->row(),it->col(),-it->value());
    mNodes.insert(mNodes.end(), nodes.begin(), nodes.end());
    mConstPart -= expr.mConstPart;
    return *this;
}
//---------------------------------------------------------------------------
MIPExpression& MIPExpression::operator -= (const double& val) {
    mConstPart -= val;
    return *this;
}
//---------------------------------------------------------------------------
MIPExpression& MIPExpression::operator = (const MIPExpression& expr) {
    mNodes = expr.getNode();
    mConstPart = expr.mConstPart;
    return *this;
}
//---------------------------------------------------------------------------
MIPExpression& MIPExpression::operator = (const MIPVariable0D& var) {
    mConstPart = 0.0;
    mNodes = std::list<Node> {Node(0, var.getColIdx(), 1.0)};
    return *this;
}
//---------------------------------------------------------------------------
MIPExpression& MIPExpression::operator = (const double& val) {
    mNodes.clear();
    mConstPart = val;
    return *this;
}
//---------------------------------------------------------------------------
const double MIPExpression::evaluate(const double* solution) const{
    double eval = 0.0;
    std::list<Node>::const_iterator it  = mNodes.begin();
    for (; it != mNodes.end(); it++)
        eval += (it->value()) * solution[it->col()];
    eval += mConstPart;
    return eval;
}
//---------------------------------------------------------------------------
MIPExpression& MIPExpression::close() {
    mNodes.clear();
    mConstPart = 0.0;
    return *this;
}
//---------------------------------------------------------------------------
MIPExpression::~MIPExpression() {
    mNodes.clear();
}
//---------------------------------------------------------------------------
}
