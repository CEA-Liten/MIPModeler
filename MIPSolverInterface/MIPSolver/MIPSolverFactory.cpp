#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>
#include "MIPSolverFactory.h"
#include <QDebug>

std::map<QString, MIPSolverFactory::SolverDescriptor> MIPSolverFactory::m_PlugIns;

MIPSolverFactory::MIPSolverFactory()
{
    // recherche les solvers
    if (!findSolvers(QCoreApplication::applicationDirPath())) {
        QString appDir = qEnvironmentVariable("PERSEE_BIN", QDir::currentPath());
        findSolvers(appDir);
    }    
}

void MIPSolverFactory::getAllInfos(QStringList& a_Infos)
{
    a_Infos.clear();
    t_mapPlugIns::iterator end = m_PlugIns.end();
    for (t_mapPlugIns::iterator it = m_PlugIns.begin(); it != end; it++) {
        a_Infos.push_back(it->second.getInfos());
    }    
}

int MIPSolverFactory::solve(const QString& a_Cmd, MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results)
{
    int vRet = -1;        
    t_mapPlugIns::iterator vIter = m_PlugIns.find(a_Cmd);
    if (vIter != m_PlugIns.end()) {
        vRet = vIter->second.solve(ap_Model, a_Params, a_Results);
    }    
    else {
        qWarning() << "cannot find solver " << a_Cmd;
    }
    return vRet;
}

bool MIPSolverFactory::findSolvers(const QString& a_Path)
{
    bool vRet = false;
    QString filterExt, filterStart;
#if (defined (_WIN32) || defined (_WIN64))
    filterExt = "*.dll";
    filterStart = "MIP";
#else
    filterExt = "*.so";
    filterStart = "libMIP";
#endif
    QDir vDir(a_Path, filterExt);
    qDebug() << "Search solvers in: " << a_Path;
    QFileInfoList vFiles(vDir.entryInfoList());
    for (auto& vFile : vFiles) {
        if (vFile.baseName().startsWith(filterStart)) {
            if (vFile.baseName().contains("Solver")) {
                SolverDescriptor vPlugIn;
                if (vPlugIn.Init(vFile.absoluteFilePath())) {
                    QString vKey = vPlugIn.getInfos();
                    m_PlugIns[vKey] = vPlugIn;
                    vRet = true; 
                }
            }
        }
    }
    return vRet;
}

//*******************************************************************************************
MIPSolverFactory::SolverDescriptor::SolverDescriptor()
{
    m_IPlugIn = nullptr;
}

bool MIPSolverFactory::SolverDescriptor::Init(const QString& a_Name)
{
    bool vRet = false;
    QPluginLoader loader(a_Name);
    //bool vLoaded = loader.load();
    QObject* plugin = loader.instance();
    if (plugin) {
        m_IPlugIn = qobject_cast<IMIPSolver*>(plugin);
        if (m_IPlugIn) {            
            // Récupère les infos du driver
            m_Infos = m_IPlugIn->Infos();
            qDebug() << "Find solver " << m_Infos << " in " << a_Name;
            vRet = true;
        }
    }
    return vRet;
}

int MIPSolverFactory::SolverDescriptor::solve(MIPModeler::MIPModel* ap_Model, const MIPSolverParams& a_Params, MIPSolverResults& a_Results)
{
    int vRet = -1;
    if (m_IPlugIn) {
        vRet = m_IPlugIn->solve(ap_Model, a_Params, a_Results);
    }
    return vRet;
}

const QString& MIPSolverFactory::SolverDescriptor::getInfos()
{
    return m_Infos;
}
