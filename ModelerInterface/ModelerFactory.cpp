#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>
#include <QDebug>

#include "ModelerFactory.h"

ModelerFactory::t_mapPlugIns ModelerFactory::m_PlugIns;

ModelerFactory::ModelerFactory()
{
    // recherche les modelers externe
    if (!findModelers(QCoreApplication::applicationDirPath())) {
        QString appDir = qEnvironmentVariable("PERSEE_BIN", QDir::currentPath());
        findModelers(appDir);
    }
}

void ModelerFactory::getModelersName(QStringList& a_Modelers)
{
    a_Modelers.clear();
    t_mapPlugIns::iterator end = m_PlugIns.end();
    for (t_mapPlugIns::iterator it = m_PlugIns.begin(); it != end; it++) {
        a_Modelers.push_back(it->first);
    }
}

ModelerInterface* ModelerFactory::getModeler(QString& a_Name)
{
    ModelerInterface* vRet = nullptr;
    t_mapPlugIns::iterator vIter = m_PlugIns.find(a_Name);
    if (vIter != m_PlugIns.end()) {
        vRet = vIter->second;
    }
    else {
        qWarning() << "cannot find modeler " << a_Name;
    }
    return vRet;
}

bool ModelerFactory::findModelers(const QString& a_Path)
{
    bool vRet = false;
    QDir vDir(a_Path, "*.dll");
    qDebug() << "Search modelers in: " << a_Path;
    QFileInfoList vFiles(vDir.entryInfoList());
    for (auto& vFile : vFiles) {
        if (vFile.baseName().contains("Modeler")) {
            if (!vFile.baseName().startsWith("MIP")) {            
                ModelerInterface *vPlugIn = load(vFile.absoluteFilePath());
                if (vPlugIn != nullptr) {
                    QString vKey = QString(vPlugIn->Infos().c_str());
                    m_PlugIns[vKey] = vPlugIn;
                    qDebug() << "Find modeler " << vKey << " in: " << a_Path;
                    vRet = true;
                }
            }
        }
    }
    return vRet;
}

ModelerInterface* ModelerFactory::load(const QString& a_Name)
{
    ModelerInterface* vRet = nullptr;
    QPluginLoader loader(a_Name);
    QObject* plugin = loader.instance();
    if (plugin) {
        vRet = qobject_cast<ModelerInterface*>(plugin);        
    }
    return vRet;
}
