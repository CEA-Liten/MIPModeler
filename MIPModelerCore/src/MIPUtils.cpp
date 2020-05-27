/**
    @file MIPUtils.cpp
    @version 1.0
    @author Yacine Gaoua (yacine.gaoua@cea.fr)
    @date 02/2020
*/

#include "MIPUtils.h"

namespace MIPModeler {
//-----------------------------------------------------------------------------------------------------
bool isConvexSet(const MIPData1D& xTable, const MIPData1D& yTable){
    try{
        //check data
        if (xTable.size() != yTable.size())
            throw std::length_error("Error: MIPModeler::isConvexSet: "
                                    "Wrong input sizes 'xTable and yTable'");
        else{
            // compute gradiant
            uint64_t nbSeg = xTable.size() - 1;
            MIPData1D gradiant(nbSeg);
            for(int i=0 ; i < nbSeg ; i++)
                gradiant[i] = (yTable[i+1] - yTable[i])/(xTable[i+1] - xTable[i]);

            // check if data set is convex
            bool convex = true;
            for(int i = 0 ; i < nbSeg - 1 ; i++){
                if (gradiant[i] > gradiant[i+1]){
                    convex = false;
                    break;
                }
            }

            // check is data set is concave
            bool concave = true;
            for(int i = 0 ; i < nbSeg-1 ; i++){
                if (gradiant[i] < gradiant[i+1]){
                    concave = false;
                    break;
                }
            }

            return (convex || concave);
        }
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
//-----------------------------------------------------------------------------------------------------
void useLogarithmicForm(MIPModel* model, MIPSpecialOrderedSet& sos) {
    int nbSOSVar = sos.getNumElements();

    // linearisation form using log(n-1) binary variables
    int binVarSize = 1;
    int Value = 2;
    while (Value <= nbSOSVar) {
        binVarSize++; // compute number of binary variables: o(log(n))
        Value = Value * 2;
    }

    MIPVariable1D binVar(binVarSize, 0.0, 1.0, MIP_INT);
    model->add(binVar);

    // build bijective function (using gray code)
    std::vector<std::vector<int>> injectiveTable(nbSOSVar, std::vector<int>(binVarSize));
    for (int i = 0; i < nbSOSVar; i++)
        for (int j = 0; j < binVarSize; j++)
            injectiveTable[i][j] = 0;

    for (int i = 0; i < binVarSize; i++) {
        for (int j = 1 + pow(2.0, i); j < 1 + pow(2.0, i + 1); j++) {
            if (j < nbSOSVar) {
                for (int k = 0; k < i; k++) {
                    injectiveTable[j][k] = injectiveTable[2 * (1 + pow(2.0, i)) - 1 - j][k];
                }
                injectiveTable[j][i] = 1;
            }
            else
                break;
        }
    }

    // linearisation constraints using the bijective function (gray table)
    for(int i = 0; i < binVarSize; i++){
        MIPExpression successors;
        MIPExpression predecessors;
        bool succ = false;
        bool pred = false;
        for(int j = 0 ; j < nbSOSVar ; j++) {
            if (j == 0 || j == nbSOSVar - 1) {
                if (injectiveTable[j][i] == 0) {
                    predecessors += sos(j);
                    pred = true;
                }
                if (injectiveTable[j][i] == 1) {
                    successors += sos(j);
                    succ = true;
                }
            }
            else {
                if (injectiveTable[j][i] == 1 && injectiveTable[j+1][i] == 1) {
                    successors += sos(j);
                    succ = true;
                }
                if (injectiveTable[j][i] == 0 && injectiveTable[j+1][i] == 0) {
                    predecessors += sos(j);
                    pred = true;
                }
            }
        }

        if (succ == true)
            model->add( successors <= binVar(i) );
        successors.close();

        if (pred == true)
            model->add( predecessors <= 1 - binVar(i) );
        predecessors.close();
    }
}
//-----------------------------------------------------------------------------------------------------
MIPExpression1D MIPPiecewiseLinearisation(MIPModel& model,
                                          const MIPExpression1D& xInputExpr,
                                          const MIPData1D& xTable, const MIPData1D& yTable,
                                          const MIPLinearType& type,
                                          const bool& relaxedForm,
                                          MIPVariable2D& xSOS){
    try{
        //check data
        if (xTable.size() != yTable.size ())
            throw std::length_error("Error: "
                                    "MIPModeler::MIPPiecewiseLinearisation: "
                                    "Wrong input sizes 'xTable and yTable'");
        else{
            // 1D interpolation
            int length = xInputExpr.size();
            int xTableSize = xTable.size();

            MIPExpression1D yOutputExpr(length);

            MIPVariable2D xVar(length, xTableSize, 0., 1.);
            model.add(xVar);

            for (int t = 0 ; t < length ; t++) {
                MIPExpression expression_X;
                MIPExpression convexity_X;
                MIPSpecialOrderedSet sos2_X;
                for (int i = 0; i < xTableSize; i++) {
                    expression_X += xTable[i] * xVar(t, i);
                    yOutputExpr[t] += yTable[i] * xVar(t, i);
                    convexity_X += xVar(t, i);
                    sos2_X.add(xVar(t, i));
                }
                model.add( xInputExpr[t] == expression_X );
                expression_X.close();
                model.add( convexity_X == 1 );
                convexity_X.close();

                if (relaxedForm == false) {
                    if (type == MIP_LOG)
                        useLogarithmicForm(&model, sos2_X);
                    else
                        model.add(sos2_X, MIP_SOS2);
                }
                sos2_X.close();
            }

            xSOS = xVar;
            return yOutputExpr;
        }
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
//-----------------------------------------------------------------------------------------------------
MIPExpression MIPPiecewiseLinearisation(MIPModel& model,
                                        const MIPExpression& xInputExpr,
                                        const MIPData1D& xTable, const MIPData1D& yTable,
                                        const MIPLinearType& type,
                                        const bool& relaxedForm,
                                        MIPVariable1D& xSOS){
    try{
        //check data
        if (xTable.size() != yTable.size ())
            throw std::length_error("Error: "
                                    "MIPModeler::MIPPiecewiseLinearisation: "
                                    "Wrong input sizes 'xTable and yTable'");
        else{
            // 1D interpolation
            int xTableSize = xTable.size();

            MIPExpression yOutputExpr;

            MIPVariable1D xVar(xTableSize, 0., 1.);
            model.add(xVar);

            MIPExpression expression_X;
            MIPExpression convexity_X;
            MIPSpecialOrderedSet sos2_X;
            for (int i = 0; i < xTableSize; i++) {
                expression_X += xTable[i] * xVar(i);
                yOutputExpr += yTable[i] * xVar(i);
                convexity_X += xVar(i);
                sos2_X.add(xVar(i));
            }
            model.add( xInputExpr == expression_X );
            expression_X.close();
            model.add( convexity_X == 1 );
            convexity_X.close();

            if (relaxedForm == false) {
                if (type == MIP_LOG)
                    useLogarithmicForm(&model, sos2_X);
                else
                    model.add(sos2_X, MIP_SOS2);
            }
            sos2_X.close();

            xSOS = xVar;
            return yOutputExpr;
        }
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
//-----------------------------------------------------------------------------------------------------
MIPExpression1D MIPPiecewiseLinearisation(MIPModel& model,
                                         const MIPData1D& xInputData,
                                         const MIPData1D& xTable, const MIPData1D& yTable,
                                         const MIPLinearType& type,
                                         const bool& relaxedForm,
                                         MIPVariable2D& xSOS){
    int length = xInputData.size();
    MIPExpression1D xInputExpr(length);
    for (int i = 0; i < length; i++)
        xInputExpr[i] = xInputData[i];

    return MIPPiecewiseLinearisation(model, xInputExpr, xTable, yTable, type, relaxedForm, xSOS);
}
//-----------------------------------------------------------------------------------------------------
MIPExpression MIPPiecewiseLinearisation(MIPModel& model,
                                        const double& xInputData,
                                        const MIPData1D& xTable, const MIPData1D& yTable,
                                        const MIPLinearType& type,
                                        const bool& relaxedForm,
                                        MIPVariable1D& xSOS){
    MIPExpression xInputExpr = xInputData;
    return MIPPiecewiseLinearisation(model, xInputExpr, xTable, yTable, type, relaxedForm, xSOS);
}
//-----------------------------------------------------------------------------------------------------
MIPExpression1D MIPPiecewiseLinearisation(MIPModel& model,
                                         const MIPVariable1D& xInputVar,
                                         const MIPData1D& xTable, const MIPData1D& yTable,
                                         const MIPLinearType& type,
                                         const bool& relaxedForm,
                                         MIPVariable2D& xSOS){
    int length = xInputVar.getDims();
    MIPExpression1D xInputExpr(length);
    for (int i = 0; i < length; i++)
        xInputExpr[i] += xInputVar(i);

    return MIPPiecewiseLinearisation(model, xInputExpr, xTable, yTable, type, relaxedForm, xSOS);
}
//-----------------------------------------------------------------------------------------------------
MIPExpression MIPPiecewiseLinearisation(MIPModel& model,
                                        const MIPVariable0D& xInputVar,
                                        const MIPData1D& xTable, const MIPData1D& yTable,
                                        const MIPLinearType& type,
                                        const bool& relaxedForm,
                                        MIPVariable1D& xSOS){
    MIPExpression xInputExpr;
    xInputExpr += xInputVar;
    return MIPPiecewiseLinearisation(model, xInputExpr, xTable, yTable, type, relaxedForm, xSOS);
}
//-----------------------------------------------------------------------------------------------------
MIPExpression1D MIPTriMeshLinearisation(MIPModel& model,
                                        const MIPExpression1D& xInputExpr, const MIPExpression1D& yInputExpr,
                                        const MIPData1D& xTable, const MIPData1D& yTable, const MIPData2D& zTable,
                                        const MIPLinearType& type, const bool& relaxedForm,
                                        MIPVariable3D& weight,
                                        MIPVariable2D& xSOS,
                                        MIPVariable2D& ySOS,
                                        MIPVariable2D& diagSOS){
    try{
        // check data
        if (xInputExpr.size() != yInputExpr.size()){
            throw std::length_error("Error: "
                                    "MIPModeler::MIPTriMeshLinearisation: "
                                    "Wrong input sizes 'xExpr and yExpr'");
        }

        if (xTable.size() != zTable.size()){
            throw std::length_error("Error: "
                                    "MIPModeler::MIPTriMeshLinearisation: "
                                    "Wrong input sizes 'xTable and zTable'");
        }

        for(int i = 0 ; i < zTable.size() ; i++){
            if (yTable.size() != zTable[i].size()){
                throw std::length_error("Error: "
                                        "MIPModeler::MIPTriMeshLinearisation: "
                                        "Wrong input sizes 'yTable and zTable'");
                break;
            }
        }

            // bilinear interpolation
        int length = xInputExpr.size();
        int xTableSize = xTable.size();
        int yTableSize = yTable.size();
        int diagSize = xTableSize + yTableSize - 1;

        MIPVariable2D xVar(length, xTableSize, 0., 1.);
        MIPVariable2D yVar(length, yTableSize, 0., 1.);
        MIPVariable2D diagVar(length, diagSize, 0., 1.);
        MIPVariable3D weightVar(length, xTableSize, yTableSize, 0., INFINITY);
        model.add(xVar);
        model.add(yVar);
        model.add(diagVar);
        model.add(weightVar);

        //-------------------- sos2 and convexity on x
        //-------------------- mXVar(t,i) = sum(j, mWeightVar(t,i,j))
        for (int t = 0; t < length ; t++) {
            MIPExpression convexity_X;
            MIPSpecialOrderedSet sos2_X;
            for (int i = 0; i < xTableSize; i++) {
                convexity_X += xVar(t,i);
                sos2_X.add(xVar(t,i));
                MIPExpression sum_Y;
                for (int j = 0; j < yTableSize ; j++)
                    sum_Y += weightVar(t,i,j);
                model.add(sum_Y == xVar(t,i));
                sum_Y.close();
            }
            model.add(convexity_X == 1);
            if (relaxedForm == false) {
                if (type == MIP_LOG)
                    useLogarithmicForm(&model, sos2_X);
                else
                    model.add(sos2_X, MIP_SOS2);
            }
            convexity_X.close();
            sos2_X.close();
        }

        //-------------------- sos2 and convexity on y
        //-------------------- mYVar(t,j) = sum(i, mWeightVar(t,i,j))
        for (int t = 0; t < length ; t++) {
            MIPExpression convexity_Y;
            MIPSpecialOrderedSet sos2_Y;
            for (int j = 0; j < yTableSize ; j++) {
                convexity_Y += yVar(t,j);
                sos2_Y.add(yVar(t,j));
                MIPExpression sum_X;
                for (int i = 0; i < xTableSize ; i++)
                    sum_X += weightVar(t,i,j);
                model.add(sum_X == yVar(t,j));
                sum_X.close();
            }
            model.add(convexity_Y == 1);
            if (relaxedForm == false) {
                if (type == MIP_LOG)
                    useLogarithmicForm(&model, sos2_Y);
                else
                    model.add(sos2_Y, MIP_SOS2);
            }
            convexity_Y.close();
            sos2_Y.close();
        }

        //--------------------- sos2 and convexity on diagonals
        //--------------------- mDiagVar(t,k) =e= sum((i,j)$(ord(i)+ord(j)-1=ord(k)), mWeightVar(t,i,j))
        for (int t = 0; t < length ; t++) {
            MIPExpression convexity_Diag;
            MIPSpecialOrderedSet sos2_Diag;
            for (int k = 0; k < diagSize ; k++) {
                convexity_Diag += diagVar(t,k);
                sos2_Diag.add(diagVar(t,k));
                MIPExpression sum_XY;
                for (int i = std::max(0, int(xTableSize - 1 - k));
                     i <= std::min(int(diagSize - k - 1), int(xTableSize - 1)); i++) {
                    sum_XY += weightVar(t, i, i - xTableSize + k + 1);
                }
                model.add(sum_XY == diagVar(t, k));
                sum_XY.close();
            }
            model.add(convexity_Diag == 1);
            if (relaxedForm == false) {
                if (type == MIP_LOG)
                    useLogarithmicForm(&model, sos2_Diag);
                else
                    model.add(sos2_Diag, MIP_SOS2);
            }
            convexity_Diag.close();
            sos2_Diag.close();
        }

        //------------------------ xExpression(t) =e= sum((i,j), xData(i) * mWeightVar(t,i,j));
        //------------------------ yExpression(t) =e= sum((i,j), yData(j) * mWeightVar(t,i,j));
        //------------------------ zExpression(t) =e= sum((i,j), zData(i,j) * mWeightVar(t,i,j));
        MIPExpression1D zOutputExpr(length);
        for (int t = 0; t < length ; t++) {
            MIPExpression expression_X;
            MIPExpression expression_Y;
            for (int i = 0; i < xTableSize; i++) {
                for (int j = 0; j < yTableSize; j++) {
                    expression_X += xTable[i] * weightVar(t,i,j);
                    expression_Y += yTable[j] * weightVar(t,i,j);
                    zOutputExpr[t] += zTable[i][j] * weightVar(t,i,j);
                }
            }
            model.add(expression_X == xInputExpr[t]);
            model.add(expression_Y == yInputExpr[t]);
            expression_X.close();
            expression_Y.close();
        }
        weight = weightVar;
        xSOS = xVar;
        ySOS = yVar;
        diagSOS = diagVar;

        return zOutputExpr;
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
//-----------------------------------------------------------------------------------------------------
MIPExpression MIPTriMeshLinearisation(MIPModel& model,
                                      const MIPExpression& xInputExpr, const MIPExpression& yInputExpr,
                                      const MIPData1D& xTable, const MIPData1D& yTable, const MIPData2D& zTable,
                                      const MIPLinearType& type, const bool& relaxedForm,
                                      MIPVariable2D& weight,
                                      MIPVariable1D& xSOS,
                                      MIPVariable1D& ySOS,
                                      MIPVariable1D& diagSOS){
    try{
        // check data
        if (xTable.size() != zTable.size()){
            throw std::length_error("Error: "
                                    "MIPModeler::MIPTriMeshLinearisation: "
                                    "Wrong input sizes 'xTable and zTable'");
        }

        for(int i = 0 ; i < zTable.size() ; i++){
            if (yTable.size() != zTable[i].size()){
                throw std::length_error("Error: "
                                        "MIPModeler::MIPTriMeshLinearisation: "
                                        "Wrong input sizes 'yTable and zTable'");
                break;
            }
        }

            // bilinear interpolation
        int xTableSize = xTable.size();
        int yTableSize = yTable.size();
        int diagSize = xTableSize + yTableSize - 1;

        MIPVariable1D xVar(xTableSize, 0., 1.);
        MIPVariable1D yVar(yTableSize, 0., 1.);
        MIPVariable1D diagVar(diagSize, 0., 1.);
        MIPVariable2D weightVar(xTableSize, yTableSize, 0., INFINITY);
        model.add(xVar);
        model.add(yVar);
        model.add(diagVar);
        model.add(weightVar);

        //-------------------- sos2 and convexity on x
        //-------------------- mXVar(i) = sum(j, mWeightVar(i,j))
        MIPExpression convexity_X;
        MIPSpecialOrderedSet sos2_X;
        for (int i = 0; i < xTableSize; i++) {
            convexity_X += xVar(i);
            sos2_X.add(xVar(i));
            MIPExpression sum_Y;
            for (int j = 0; j < yTableSize ; j++)
                sum_Y += weightVar(i,j);
            model.add(sum_Y == xVar(i));
            sum_Y.close();
        }
        model.add(convexity_X == 1);
        if (relaxedForm == false) {
            if (type == MIP_LOG)
                useLogarithmicForm(&model, sos2_X);
            else
                model.add(sos2_X, MIP_SOS2);
        }
        convexity_X.close();
        sos2_X.close();

        //-------------------- sos2 and convexity on y
        //-------------------- mYVar(j) = sum(i, mWeightVar(i,j))
        MIPExpression convexity_Y;
        MIPSpecialOrderedSet sos2_Y;
        for (int j = 0; j < yTableSize ; j++) {
            convexity_Y += yVar(j);
            sos2_Y.add(yVar(j));
            MIPExpression sum_X;
            for (int i = 0; i < xTableSize ; i++)
                sum_X += weightVar(i,j);
            model.add(sum_X == yVar(j));
            sum_X.close();
        }
        model.add(convexity_Y == 1);
        if (relaxedForm == false) {
            if (type == MIP_LOG)
                useLogarithmicForm(&model, sos2_Y);
            else
                model.add(sos2_Y, MIP_SOS2);
        }
        convexity_Y.close();
        sos2_Y.close();

        //--------------------- sos2 and convexity on diagonals
        //--------------------- mDiagVar(k) =e= sum((i,j)$(ord(i)+ord(j)-1=ord(k)), mWeightVar(i,j))
        MIPExpression convexity_Diag;
        MIPSpecialOrderedSet sos2_Diag;
        for (int k = 0; k < diagSize ; k++) {
            convexity_Diag += diagVar(k);
            sos2_Diag.add(diagVar(k));
            MIPExpression sum_XY;
            for (int i = std::max(0, int(xTableSize - 1 - k));
                 i <= std::min(int(diagSize - k - 1), int(xTableSize - 1)); i++) {
                sum_XY += weightVar(i, i - xTableSize + k + 1);
            }
            model.add(sum_XY == diagVar(k));
            sum_XY.close();
        }
        model.add(convexity_Diag == 1);
        if (relaxedForm == false) {
            if (type == MIP_LOG)
                useLogarithmicForm(&model, sos2_Diag);
            else
                model.add(sos2_Diag, MIP_SOS2);
        }
        convexity_Diag.close();
        sos2_Diag.close();

        //------------------------ xExpression =e= sum((i,j), xData(i) * mWeightVar(i,j));
        //------------------------ yExpression =e= sum((i,j), yData(j) * mWeightVar(i,j));
        //------------------------ zExpression =e= sum((i,j), zData(i,j) * mWeightVar(i,j));
        MIPExpression zOutputExpr;
        MIPExpression expression_X;
        MIPExpression expression_Y;
        for (int i = 0; i < xTableSize; i++) {
            for (int j = 0; j < yTableSize; j++) {
                expression_X += xTable[i] * weightVar(i,j);
                expression_Y += yTable[j] * weightVar(i,j);
                zOutputExpr += zTable[i][j] * weightVar(i,j);
            }
        }
        model.add(expression_X == xInputExpr);
        model.add(expression_Y == yInputExpr);
        expression_X.close();
        expression_Y.close();

        weight = weightVar;
        xSOS = xVar;
        ySOS = yVar;
        diagSOS = diagVar;

        return zOutputExpr;
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
//-----------------------------------------------------------------------------------------------------
MIPExpression1D MIPTriMeshLinearisation(MIPModel& model,
                                        const MIPData1D& xInputData, const MIPData1D& yInputData,
                                        const MIPData1D& xTable, const MIPData1D& yTable, const MIPData2D& zTable,
                                        const MIPLinearType& type, const bool& relaxedForm,
                                        MIPVariable3D& weight,
                                        MIPVariable2D& xSOS,
                                        MIPVariable2D& ySOS,
                                        MIPVariable2D& diagSOS){
    MIPExpression1D xInputExpr;
    MIPExpression1D yInputExpr;

    try{
        // check data
        if (xInputData.size() != yInputData.size()){
            throw std::length_error("Error: "
                                    "MIPModeler::MIPTriMeshLinearisation: "
                                    "Wrong input sizes 'xInputData and yInputData'");
        }
        else{
            int xlength = xInputData.size();
            xInputExpr.resize(xlength);
            for (int i = 0; i< xlength ; i++)
                xInputExpr[i] = xInputData[i];

            int ylength = yInputData.size();
            yInputExpr.resize(ylength);
            for (int i = 0; i< ylength ; i++)
                yInputExpr[i] = yInputData[i];

        }

        if (xTable.size() != zTable.size()){
            throw std::length_error("Error: "
                                    "MIPModeler::MIPTriMeshLinearisation: "
                                    "Wrong input sizes 'xTable and zTable'");
        }

        for(int i = 0 ; i < zTable.size() ; i++){
            if (yTable.size() != zTable[i].size()){
                throw std::length_error("Error: "
                                        "MIPModeler::MIPTriMeshLinearisation: "
                                        "Wrong input sizes 'yTable and zTable'");
                break;
            }
        }

        return MIPTriMeshLinearisation(model,
                                       xInputExpr, yInputExpr,
                                       xTable, yTable, zTable,
                                       type, relaxedForm,
                                       weight, xSOS, ySOS, diagSOS);
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
//-----------------------------------------------------------------------------------------------------
MIPExpression MIPTriMeshLinearisation(MIPModel& model,
                                      const double& xInputData, const double& yInputData,
                                      const MIPData1D& xTable, const MIPData1D& yTable, const MIPData2D& zTable,
                                      const MIPLinearType& type, const bool& relaxedForm,
                                      MIPVariable2D& weight,
                                      MIPVariable1D& xSOS,
                                      MIPVariable1D& ySOS,
                                      MIPVariable1D& diagSOS){
    MIPExpression xInputExpr = xInputData;
    MIPExpression yInputExpr = yInputData;

    return MIPTriMeshLinearisation(model,
                                   xInputExpr, yInputExpr,
                                   xTable, yTable, zTable,
                                   type, relaxedForm,
                                   weight, xSOS, ySOS, diagSOS);
}
//-----------------------------------------------------------------------------------------------------
MIPExpression1D MIPTriMeshLinearisation(MIPModel& model,
                                        const MIPVariable1D& xInputVar, const MIPVariable1D& yInputVar,
                                        const MIPData1D& xTable, const MIPData1D& yTable, const MIPData2D& zTable,
                                        const MIPLinearType& type, const bool& relaxedForm,
                                        MIPVariable3D& weight,
                                        MIPVariable2D& xSOS,
                                        MIPVariable2D& ySOS,
                                        MIPVariable2D& diagSOS){
    MIPExpression1D xInputExpr;
    MIPExpression1D yInputExpr;

    try{
        // check data
        if (xInputVar.getDims() != yInputVar.getDims()){
            throw std::length_error("Error: "
                                    "MIPModeler::MIPTriMeshLinearisation: "
                                    "Wrong input sizes 'xInputVar and yInputVar'");
        }
        else{
            int xlength = xInputVar.getDims();
            xInputExpr.resize(xlength);
            for (int i = 0; i< xlength ; i++)
                xInputExpr[i] = xInputVar(i);

            int ylength = yInputVar.getDims();
            yInputExpr.resize(ylength);
            for (int i = 0; i< ylength ; i++)
                yInputExpr[i] = yInputVar(i);

        }

        if (xTable.size() != zTable.size()){
            throw std::length_error("Error: "
                                    "MIPModeler::MIPTriMeshLinearisation: "
                                    "Wrong input sizes 'xTable and zTable'");
        }

        for(int i = 0 ; i < zTable.size() ; i++){
            if (yTable.size() != zTable[i].size()){
                throw std::length_error("Error: "
                                        "MIPModeler::MIPTriMeshLinearisation: "
                                        "Wrong input sizes 'yTable and zTable'");
                break;
            }
        }

        return MIPTriMeshLinearisation(model,
                                       xInputExpr, yInputExpr,
                                       xTable, yTable, zTable,
                                       type, relaxedForm,
                                       weight, xSOS, ySOS, diagSOS);
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
//-----------------------------------------------------------------------------------------------------
MIPExpression MIPTriMeshLinearisation(MIPModel& model,
                                      const MIPVariable0D& xInputVar, const MIPVariable0D& yInputVar,
                                      const MIPData1D& xTable, const MIPData1D& yTable, const MIPData2D& zTable,
                                      const MIPLinearType& type, const bool& relaxedForm,
                                      MIPVariable2D& weight,
                                      MIPVariable1D& xSOS,
                                      MIPVariable1D& ySOS,
                                      MIPVariable1D& diagSOS){
    MIPExpression xInputExpr;
    xInputExpr += xInputVar;
    MIPExpression yInputExpr;
    yInputExpr = yInputVar;

    return MIPTriMeshLinearisation(model,
                                   xInputExpr, yInputExpr,
                                   xTable, yTable, zTable,
                                   type, relaxedForm,
                                   weight, xSOS, ySOS, diagSOS);
}
//-----------------------------------------------------------------------------------------------------
}
