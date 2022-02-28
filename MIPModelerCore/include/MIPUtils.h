/**
 * @file MIPUtils.h
 * @brief helpfull implemented MIP methods.
 * @version 1.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 02/2020
*/

#include "MIPModeler_global.h"
#include "MIPModel.h"
#include <iostream>

#ifndef MIPUTILS_H
#define MIPUTILS_H

namespace MIPModeler {

#ifndef MIPEXPRESSION1D
#define MIPEXPRESSION1D
typedef typename std::vector<MIPExpression> MIPExpression1D;
#endif

#ifndef MIPDATA1D
#define MIPDATA1D
typedef typename std::vector<double> MIPData1D;
#endif

#ifndef MIPDATA2D
#define MIPDATA2D
typedef typename std::vector<std::vector<double>> MIPData2D;
#endif

#ifndef MIPLINEARTYPE
#define MIPLINEARTYPE
enum MIPLinearType {MIP_SOS, MIP_LOG};
#endif

/*
 isConvexSet
 version 1.0
 Author: Yacine Gaoua (yacine.gaoua@cea.fr)
 Date: 09/08/2019
 Description: check if y=f(x) is a convex set or not. This method
 is important in order to used relaxationForm in MIPPiecewiseLinearisation
 method to avoid binary variables
*/
bool MIPMODELERSHARED_EXPORT
     isConvexSet(const MIPData1D& xTable, const MIPData1D& yTable);

/*
 MIPPiecewiseLinearisation
 version 1.0
 Author: Yacine Gaoua (yacine.gaoua@cea.fr)
 Date: 09/08/2019
 Description: Piecewise linearisation to compute
 1D interpolation of y =f(x).
*/
MIPExpression1D MIPMODELERSHARED_EXPORT
                MIPPiecewiseLinearisation(MIPModel& model,
                                          const MIPExpression1D& xInputExpr,
                                          const MIPData1D& xTable, const MIPData1D& yTable,
                                          const MIPLinearType& type = MIP_SOS,
                                          const bool& relaxedForm = false,
                                          MIPVariable2D& xSOS = MIPVariable2D());
MIPExpression MIPMODELERSHARED_EXPORT
              MIPPiecewiseLinearisation(MIPModel& model,
                                        const MIPExpression& xInputExpr,
                                        const MIPData1D& xTable, const MIPData1D& yTable,
                                        const MIPLinearType& type = MIP_SOS,
                                        const bool& relaxedForm = false,
                                        MIPVariable1D& xSOS = MIPVariable1D());
MIPExpression1D MIPMODELERSHARED_EXPORT
                MIPPiecewiseLinearisation(MIPModel& model,
                                          const MIPData1D& xInputData,
                                          const MIPData1D& xTable, const MIPData1D& yTable,
                                          const MIPLinearType& type  = MIP_SOS,
                                          const bool& relaxedForm = false,
                                          MIPVariable2D& xSOS  = MIPVariable2D());
MIPExpression MIPMODELERSHARED_EXPORT
              MIPPiecewiseLinearisation(MIPModel& model,
                                        const double& xInputData,
                                        const MIPData1D& xTable, const MIPData1D& yTable,
                                        const MIPLinearType& type  = MIP_SOS,
                                        const bool& relaxedForm = false,
                                        MIPVariable1D& xSOS  = MIPVariable1D());
MIPExpression1D MIPMODELERSHARED_EXPORT
                MIPPiecewiseLinearisation(MIPModel& model,
                                          const MIPVariable1D& xInputVar,
                                          const MIPData1D& xTable, const MIPData1D& yTable,
                                          const MIPLinearType& type  = MIP_SOS,
                                          const bool& relaxedForm = false,
                                          MIPVariable2D& xSOS  = MIPVariable2D());
MIPExpression MIPMODELERSHARED_EXPORT
              MIPPiecewiseLinearisation(MIPModel& model,
                                        const MIPVariable0D& xInputVar,
                                        const MIPData1D& xTable, const MIPData1D& yTable,
                                        const MIPLinearType& type  = MIP_SOS,
                                        const bool& relaxedForm = false,
                                        MIPVariable1D& xSOS  = MIPVariable1D());
/*
 MIPTriMeshLinearisation
 version 1.0
 Author: Yacine Gaoua (yacine.gaoua@cea.fr)
 Date: 09/08/2019
 Description: 2D linearisation is used to compute
 2 dimensional interpolation on 3D plan z =f(x,y).
 In this model we are using triangular mesh.

                       k=5  k=4 k=3 k=2
                      /    /   /   /
                  j=2/o---o---o---o
                      |  /|  /|  /|  k=1
                      | / | / | / | /
                      |/  |/  |/  |/
                Y j=1 o---o-Z-o---o
                      |  /|  /|  /|
                      | / | / | / |  k=0
                      |/  |/  |/  | /
                  j=0 o---o---o---o/
                      i=0 i=1 i=2 i=3
                            X
*/
MIPExpression1D MIPMODELERSHARED_EXPORT
                MIPTriMeshLinearisation(MIPModel& model,
                                        const MIPExpression1D& xInputExpr, const MIPExpression1D& yInputExpr,
                                        const MIPData1D& xTable, const MIPData1D& yTable, const MIPData2D& zTable,
                                        const MIPLinearType& type = MIP_SOS,
                                        const bool& relaxedForm = false,
                                        MIPVariable3D& weight = MIPVariable3D(),
                                        MIPVariable2D& xSOS = MIPVariable2D(),
                                        MIPVariable2D& ySOS = MIPVariable2D(),
                                        MIPVariable2D& diagSOS = MIPVariable2D());

MIPExpression MIPMODELERSHARED_EXPORT
              MIPTriMeshLinearisation(MIPModel& model,
                                      const MIPExpression& xInputExpr, const MIPExpression& yInputExpr,
                                      const MIPData1D& xTable, const MIPData1D& yTable, const MIPData2D& zTable,
                                      const MIPLinearType& type = MIP_SOS,
                                      const bool& relaxedForm = false,
                                      MIPVariable2D& weight = MIPVariable2D(),
                                      MIPVariable1D& xSOS = MIPVariable1D(),
                                      MIPVariable1D& ySOS = MIPVariable1D(),
                                      MIPVariable1D& diagSOS = MIPVariable1D());
MIPExpression1D MIPMODELERSHARED_EXPORT
                MIPTriMeshLinearisation(MIPModel& model,
                                        const MIPData1D& xInputData, const MIPData1D& yInputData,
                                        const MIPData1D& xTable, const MIPData1D& yTable, const MIPData2D& zTable,
                                        const MIPLinearType& type = MIP_SOS,
                                        const bool& relaxedForm = false,
                                        MIPVariable3D& weight = MIPVariable3D(),
                                        MIPVariable2D& xSOS = MIPVariable2D(),
                                        MIPVariable2D& ySOS = MIPVariable2D(),
                                        MIPVariable2D& diagSOS = MIPVariable2D());

MIPExpression MIPMODELERSHARED_EXPORT
              MIPTriMeshLinearisation(MIPModel& model,
                                      const double& xInputData, const double& yInputData,
                                      const MIPData1D& xTable, const MIPData1D& yTable, const MIPData2D& zTable,
                                      const MIPLinearType& type = MIP_SOS,
                                      const bool& relaxedForm = false,
                                      MIPVariable2D& weight = MIPVariable2D(),
                                      MIPVariable1D& xSOS = MIPVariable1D(),
                                      MIPVariable1D& ySOS = MIPVariable1D(),
                                      MIPVariable1D& diagSOS = MIPVariable1D());
MIPExpression1D MIPMODELERSHARED_EXPORT
                MIPTriMeshLinearisation(MIPModel& model,
                                        const MIPVariable1D& xInputVar, const MIPVariable1D& yInputVar,
                                        const MIPData1D& xTable, const MIPData1D& yTable, const MIPData2D& zTable,
                                        const MIPLinearType& type = MIP_SOS,
                                        const bool& relaxedForm = false,
                                        MIPVariable3D& weight = MIPVariable3D(),
                                        MIPVariable2D& xSOS = MIPVariable2D(),
                                        MIPVariable2D& ySOS = MIPVariable2D(),
                                        MIPVariable2D& diagSOS = MIPVariable2D());

MIPExpression MIPMODELERSHARED_EXPORT
              MIPTriMeshLinearisation(MIPModel& model,
                                      const MIPVariable0D& xInputVar, const MIPVariable0D& yInputVar,
                                      const MIPData1D& xTable, const MIPData1D& yTable, const MIPData2D& zTable,
                                      const MIPLinearType& type = MIP_SOS,
                                      const bool& relaxedForm = false,
                                      MIPVariable2D& weight = MIPVariable2D(),
                                      MIPVariable1D& xSOS = MIPVariable1D(),
                                      MIPVariable1D& ySOS = MIPVariable1D(),
                                      MIPVariable1D& diagSOS = MIPVariable1D());
}

#endif // MIPUTILS_H
