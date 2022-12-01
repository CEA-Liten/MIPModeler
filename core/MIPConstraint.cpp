/**
    @file MIPConstraint.cpp
    @version 2.0
    @author Yacine Gaoua (yacine.gaoua@cea.fr)
    @date 07/2019
*/

#include "MIPConstraint.h"

namespace MIPModeler {
// --------------------------------------------------------------------------
MIPConstraint::MIPConstraint()
    : mName("")
{

}
// --------------------------------------------------------------------------
MIPConstraint::MIPConstraint(const MIPExpression& expr,
                             const char& sense, const double& val)
    : mExpression(expr),
      mSense(sense),
      mValue(val),
      mName("")
{

}
// --------------------------------------------------------------------------
void MIPConstraint::setRowIndex(int& idx) {
    mExpression.setRowIndex(idx);
    idx++;
}
// --------------------------------------------------------------------------
MIPConstraint operator == (const MIPExpression& expr, const double& val) {
    return MIPConstraint(expr, 'E', val - expr.getConstPart());
}
// --------------------------------------------------------------------------
MIPConstraint operator == (const double& val, const MIPExpression& expr) {
    return MIPConstraint(expr, 'E', val - expr.getConstPart());
}
// --------------------------------------------------------------------------
MIPConstraint operator == (const MIPVariable0D& var, const double& val) {
    MIPExpression temp;
    temp += var;
    return MIPConstraint(temp, 'E', val);
}
// --------------------------------------------------------------------------
MIPConstraint operator == (const double& val, const MIPVariable0D& var) {
    MIPExpression temp;
    temp += var;
    return MIPConstraint(temp, 'E', val);
}
// --------------------------------------------------------------------------
MIPConstraint operator == (const MIPExpression& expr1, const MIPExpression& expr2) {
    MIPExpression temp = expr1;
    temp -= expr2;
    return MIPConstraint(temp, 'E', temp.getConstPart() * -1);
}
// --------------------------------------------------------------------------
MIPConstraint operator == (const MIPExpression& expr, const MIPVariable0D& var) {
    MIPExpression temp = expr;
    temp -= var;
    return MIPConstraint(temp, 'E', temp.getConstPart() * -1);
}
// --------------------------------------------------------------------------
MIPConstraint operator == (const MIPVariable0D& var, const MIPExpression& expr) {
    MIPExpression temp = expr;
    temp -= var;
    return MIPConstraint(temp, 'E', temp.getConstPart() * -1);
}
// --------------------------------------------------------------------------
MIPConstraint operator == (const MIPVariable0D& var1, const MIPVariable0D& var2) {
    MIPExpression temp;
    temp += var1;
    temp -= var2;
    return MIPConstraint(temp, 'E', 0.0);
}
// --------------------------------------------------------------------------
MIPConstraint operator >= (const double& val, const MIPExpression& expr) {
    return MIPConstraint(expr, 'L', val - expr.getConstPart());
}
// --------------------------------------------------------------------------
MIPConstraint operator >= (const MIPExpression& expr, const double& val) {
    return MIPConstraint(expr, 'G', val - expr.getConstPart());
}
// --------------------------------------------------------------------------
MIPConstraint operator >= (const double& val, const MIPVariable0D& var) {
    MIPExpression temp;
    temp += var;
    return MIPConstraint(temp, 'L', val);
}
// --------------------------------------------------------------------------
MIPConstraint operator >= (const MIPVariable0D& var, const double& val) {
    MIPExpression temp;
    temp += var;
    return MIPConstraint(temp, 'G', val);
}
// --------------------------------------------------------------------------
MIPConstraint operator >= (const MIPExpression& expr1, const MIPExpression& expr2) {
    MIPExpression temp = expr1;
    temp -= expr2;
    return MIPConstraint(temp, 'G', temp.getConstPart() * -1);
}
// --------------------------------------------------------------------------
MIPConstraint operator >= (const MIPExpression& expr, const MIPVariable0D& var) {
    MIPExpression temp = expr;
    temp -= var;
    return MIPConstraint(temp, 'G', temp.getConstPart() * -1);
}
// --------------------------------------------------------------------------
MIPConstraint operator >= (const MIPVariable0D& var, const MIPExpression& expr) {
    MIPExpression temp = expr;
    temp -= var;
    return MIPConstraint(temp, 'L', temp.getConstPart() * -1);
}
// --------------------------------------------------------------------------
MIPConstraint operator >= (const MIPVariable0D& var1, const MIPVariable0D& var2) {
    MIPExpression temp;
    temp += var1;
    temp -= var2;
    return MIPConstraint(temp, 'G', 0.0);
}
// --------------------------------------------------------------------------
MIPConstraint operator <= (const double& val, const MIPExpression& expr) {
    return MIPConstraint(expr, 'G', val - expr.getConstPart());
}
// --------------------------------------------------------------------------
MIPConstraint operator <= (const MIPExpression& expr, const double& val) {
    return MIPConstraint(expr, 'L', val - expr.getConstPart());
}
// --------------------------------------------------------------------------
MIPConstraint operator <= (const double& val, const MIPVariable0D& var) {
    MIPExpression temp;
    temp += var;
    return MIPConstraint(temp, 'G', val);
}
// --------------------------------------------------------------------------
MIPConstraint operator <= (const MIPVariable0D& var, const double& val) {
    MIPExpression temp;
    temp += var;
    return MIPConstraint(temp, 'L', val);
}
// --------------------------------------------------------------------------
MIPConstraint operator <= (const MIPExpression& expr1, const MIPExpression& expr2) {
    MIPExpression temp = expr1;
    temp -= expr2;
    return MIPConstraint(temp, 'L', temp.getConstPart()* -1);
}
// --------------------------------------------------------------------------
MIPConstraint operator <= (const MIPExpression& expr, const MIPVariable0D& var) {
    MIPExpression temp = expr;
    temp -= var;
    return MIPConstraint(temp, 'L', temp.getConstPart() * -1);
}
// --------------------------------------------------------------------------
MIPConstraint operator <= (const MIPVariable0D& var, const MIPExpression& expr){
    MIPExpression temp = expr;
    temp -= var;
    return MIPConstraint(temp, 'G', temp.getConstPart() * -1);
}
// --------------------------------------------------------------------------
MIPConstraint operator <= (const MIPVariable0D& var1, const MIPVariable0D& var2) {
    MIPExpression temp;
    temp += var1;
    temp -= var2;
    return MIPConstraint(temp, 'L', 0.0);
}
//---------------------------------------------------------------------------
void MIPConstraint::setName(const std::string& name){
    mName = name;
}
// --------------------------------------------------------------------------
MIPConstraint::~MIPConstraint() {

}
// --------------------------------------------------------------------------
}
