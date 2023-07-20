#pragma once
#include <QString>
#include <iostream>
#include <sstream>
#include <vector>

#include "modelerinterface_global.h"
#include "ModelerInterface.h"

class ABSTRACTMODELER_EXPORT ModelerFactory
{
public:
    ModelerFactory();
    static void getModelersName(QStringList& a_Modelers);
    static ModelerInterface* getModeler(QString& a_Name);


protected:
    static bool findModelers(const QString& a_Path);
    static  ModelerInterface* load(const QString& a_Name);
    
    typedef std::map<QString, ModelerInterface*> t_mapPlugIns;
    static t_mapPlugIns m_PlugIns;

    //template <typename  First, typename  Second, typename ... Rest>
    //void addModelFromFile(const First& fileName, const Second& modelName, const Rest&... modelOption);

    //
    //void addData(std::vector<GAMSData*>& data, const bool& importToGMS = false);


};
