#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "modelerinterface_global.h"
#include "ModelerInterface.h"

class ABSTRACTMODELER_EXPORT ModelerFactory
{
public:
    ModelerFactory();
    static void getModelersName(std::vector< std::string>& a_Modelers);
    static ModelerInterface* getModeler(std::string& a_Name);


protected:
    static bool findModelers(const std::string& a_Path);
    static  ModelerInterface* load(const std::string& a_Name);
    
    typedef std::map<std::string, ModelerInterface*> t_mapPlugIns;
    static t_mapPlugIns m_PlugIns;
    
};
