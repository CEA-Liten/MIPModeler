/**
 * @file  tst_testTransport.cpp
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 11/2022
 * @abstract transportation problem is one of typical LP optimisation problems
  in operation research. In this example, transportation problem is modeled using MIPModeler.
*/

#include <QtTest>
#include "MIPModeler.h"
#include "MIPClpSolver.h"
#include "MIPCpxSolver.h"
#include "GAMSModeler.h"

class testTransport : public QObject{
    Q_OBJECT

private slots:
    void initTestCase();
    void test_Standalone_GAMSModeler();
    void test_MIPModeler_ClpSolver();
    void test_MIPModeler_CplexSolver();
    void test_MIPModeler_GAMSModeler();
    void cleanupTestCase();

public:
    int mFactory = 2;
    int mClient  = 3;
    std::vector<double> mCapacity {350 , 600};
    std::vector<double> mDemand   {325, 300, 275};
    std::vector<std::vector<double>> mCost {{0.225, 0.153, 0.162}, {0.225, 0.162, 0.126}};
};

void testTransport::initTestCase()
{
}

void testTransport::test_Standalone_GAMSModeler()
{
    GAMSModeler::GAMSModel* model = new GAMSModeler::GAMSModel();

    std::vector<std::string> factorySet(mFactory);
    for (int i=0; i < mFactory; i++)
        factorySet[i] = "factory" + std::to_string(i);

    std::vector<std::string> clientSet(mClient);
    for (int i=0; i < mClient; i++)
        clientSet[i] = "client" + std::to_string(i);

    std::vector<GAMSModeler::GAMSData*> modelData;
    modelData.push_back(new GAMSModeler::GAMSDataSet("factory", factorySet));
    modelData.push_back(new GAMSModeler::GAMSDataSet("client" , clientSet));
    modelData.push_back(new GAMSModeler::GAMSDataParam1D("capacity" , "factory", mCapacity));
    modelData.push_back(new GAMSModeler::GAMSDataParam1D("demand", "client", mDemand));
    std::vector<std::vector<double>> x;
    x = std::vector<std::vector<double>> {{0.225, 0.153, 0.162}, {0.225, 0.162, 0.126}};
    modelData.push_back(new GAMSModeler::GAMSDataParam2D("cost", "factory", "client", x));
    model->addData(modelData);
    modelData.clear();

    model->addText ("* $ set inputGDXData _gams_cpp_gdb0                                          \n"
                   "  Sets                                                                       \n"
                   "       client                                                                \n"
                   "       factory;                                                              \n"
                   "                                                                             \n"
                   "  Parameters                                                                 \n"
                   "       demand(client)          client demands                                \n"
                   "       capacity(factory)       factory capacities                            \n"
                   "       cost(factory, client)   distance in thousands of miles ;              \n"
                   "                                                                             \n"
                   "$ gdxin %inputGDXData%                                                       \n"
                   "$ load client factory demand capacity cost                                   \n"
                   "$ gdxin                                                                      \n"
                   "                                                                             \n"
                   "  Variables                                                                  \n"
                   "       x(factory ,client)  shipment quantities in cases                      \n"
                   "       Problem_v_Objective total transportation costs ;                      \n"
                   "                                                                             \n"
                   "  Equations                                                                  \n"
                   "       eq_cost              define objective function                        \n"
                   "       eq_supply(factory)   observe supply limit at each factory             \n"
                   "       eq_demand(client)    satisfy client demand ;                          \n"
                   "                                                                             \n"
                   "  eq_cost.. Problem_v_Objective =e= sum((factory,client),                    \n"
                   "                                 cost(factory,client) * x(factory ,client)); \n"
                   "                                                                             \n"
                   "  eq_supply(factory).. sum(client, x(factory,client)) =l= capacity(factory); \n"
                   "                                                                             \n"
                   "  eq_demand(client).. sum(factory, x(factory,client)) =g= demand(client);    \n"
                   "                                                                             \n"
                   "  x.lo(factory ,client) = 0                                                  \n");

    model->setObjectiveDirection("Min");
    model->buildProblem();
    model->solve();

    QVERIFY(fabs(model->getOptValue("Problem_v_Objective")[0] - 153.6750) < 1e-4);

    delete model;
}

void testTransport::test_MIPModeler_ClpSolver()
{
    MIPModeler::MIPModel model;

    MIPModeler::MIPVariable2D transp(mFactory, mClient, 0.0, MIP_INFINITY);
    model.add(transp, "Transp");

    for (int iclient = 0; iclient < mClient; iclient++){
        MIPModeler::MIPExpression dem;
        for (int ifactory = 0; ifactory < mFactory; ifactory++)
            dem += transp(ifactory, iclient);
        model.add (dem >= mDemand[iclient], "demand_"+ std::to_string(iclient));
        dem.close();
    }

    for (int ifactory = 0; ifactory < mFactory; ifactory++){
        MIPModeler::MIPExpression cap;
        for (int iclient = 0; iclient < mClient; iclient++)
            cap += transp(ifactory, iclient);
        model.add(cap <= mCapacity[ifactory], "capacity_"+ std::to_string(ifactory));
        cap.close();
    }

    MIPModeler::MIPExpression obj;
    for (int ifactory = 0; ifactory < mFactory; ifactory++)
        for (int iclient = 0; iclient < mClient; iclient++)
            obj += transp(ifactory, iclient) * mCost[ifactory][iclient];
    model.setObjective(obj, MIPModeler::MIP_MINIMIZE);
    obj.close();

    MIPSolverInterface::MIPClpSolver clpSolver(&model);
    clpSolver.solve();
    QVERIFY(fabs(clpSolver.getObjectiveValue() - 153.6750) < 1e-4);
}

void testTransport::test_MIPModeler_CplexSolver()
{
    MIPModeler::MIPModel model;

    MIPModeler::MIPVariable2D transp(mFactory, mClient, 0.0, MIP_INFINITY);
    model.add(transp, "Transp");

    for (int iclient = 0; iclient < mClient; iclient++){
        MIPModeler::MIPExpression dem;
        for (int ifactory = 0; ifactory < mFactory; ifactory++)
            dem += transp(ifactory, iclient);
        model.add (dem >= mDemand[iclient], "demand_"+ std::to_string(iclient));
        dem.close();
    }

    for (int ifactory = 0; ifactory < mFactory; ifactory++){
        MIPModeler::MIPExpression cap;
        for (int iclient = 0; iclient < mClient; iclient++)
            cap += transp(ifactory, iclient);
        model.add(cap <= mCapacity[ifactory], "capacity_"+ std::to_string(ifactory));
        cap.close();
    }

    MIPModeler::MIPExpression obj;
    for (int ifactory = 0; ifactory < mFactory; ifactory++)
        for (int iclient = 0; iclient < mClient; iclient++)
            obj += transp(ifactory, iclient) * mCost[ifactory][iclient];
    model.setObjective(obj, MIPModeler::MIP_MINIMIZE);
    obj.close();

    MIPSolverInterface::MIPCpxSolver cpxSolver(&model);
    cpxSolver.solve();
    QVERIFY( fabs(cpxSolver.getObjectiveValue() - 153.6750) < 1e-4);
}

void testTransport::test_MIPModeler_GAMSModeler()
{
    MIPModeler::MIPModel model;

    GAMSModeler::GAMSModel* aGAMSModel = model.getGAMSModel();

    std::vector<std::string> factorySet(mFactory);
    for (int i=0; i < mFactory; i++)
        factorySet[i] = "factory" + std::to_string(i);

    std::vector<std::string> clientSet(mClient);
    for (int i=0; i < mClient; i++)
        clientSet[i] = "client" + std::to_string(i);

    std::vector<GAMSModeler::GAMSData*> modelData;
    modelData.push_back(new GAMSModeler::GAMSDataSet("factory", factorySet));
    modelData.push_back(new GAMSModeler::GAMSDataSet("client" , clientSet));
    modelData.push_back(new GAMSModeler::GAMSDataParam1D("capacity" , "factory", mCapacity));
    modelData.push_back(new GAMSModeler::GAMSDataParam1D("demand", "client", mDemand));
    std::vector<std::vector<double>> x;
    x = std::vector<std::vector<double>> {{0.225, 0.153, 0.162}, {0.225, 0.162, 0.126}};
    modelData.push_back(new GAMSModeler::GAMSDataParam2D("cost", "factory", "client", x));
    aGAMSModel->addData(modelData);
    modelData.clear();

    aGAMSModel->addText ("* $ set inputGDXData _gams_cpp_gdb0                                          \n"
                   "  Sets                                                                       \n"
                   "       client                                                                \n"
                   "       factory;                                                              \n"
                   "                                                                             \n"
                   "  Parameters                                                                 \n"
                   "       demand(client)          client demands                                \n"
                   "       capacity(factory)       factory capacities                            \n"
                   "       cost(factory, client)   distance in thousands of miles ;              \n"
                   "                                                                             \n"
                   "$ gdxin %inputGDXData%                                                       \n"
                   "$ load client factory demand capacity cost                                   \n"
                   "$ gdxin                                                                      \n"
                   "                                                                             \n"
                   "  Variables                                                                  \n"
                   "       x(factory ,client)  shipment quantities in cases                      \n"
                   "       Problem_v_Objective total transportation costs ;                      \n"
                   "                                                                             \n"
                   "  Equations                                                                  \n"
                   "       eq_cost              define objective function                        \n"
                   "       eq_supply(factory)   observe supply limit at each factory             \n"
                   "       eq_demand(client)    satisfy client demand ;                          \n"
                   "                                                                             \n"
                   "  eq_cost.. Problem_v_Objective =e= sum((factory,client),                    \n"
                   "                                 cost(factory,client) * x(factory ,client)); \n"
                   "                                                                             \n"
                   "  eq_supply(factory).. sum(client, x(factory,client)) =l= capacity(factory); \n"
                   "                                                                             \n"
                   "  eq_demand(client).. sum(factory, x(factory,client)) =g= demand(client);    \n"
                   "                                                                             \n"
                   "  x.lo(factory ,client) = 0                                                  \n");

    aGAMSModel->setObjectiveDirection("Min");
    aGAMSModel->buildProblem();
    aGAMSModel->solve();

    QVERIFY(fabs(aGAMSModel->getOptValue("Problem_v_Objective")[0] - 153.6750) < 1e-4);
}

void testTransport::cleanupTestCase()
{
}

QTEST_APPLESS_MAIN(testTransport)
#include "tst_testTransport.moc"
