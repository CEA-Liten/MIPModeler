
#include "ModelerFactory.h"
#include "spdlog/spdlog.h"
#include <filesystem>

namespace fs = std::filesystem;
ModelerFactory::t_mapPlugIns ModelerFactory::m_PlugIns;

ModelerFactory::ModelerFactory()
{
    // recherche les modelers externe
    if (!findModelers(fs::current_path().string())) {
        findModelers(std::getenv("CAIRN_BIN"));
    }
}

void ModelerFactory::getModelersName(std::vector< std::string>& a_Modelers)
{
    a_Modelers.clear();
    t_mapPlugIns::iterator end = m_PlugIns.end();
    for (t_mapPlugIns::iterator it = m_PlugIns.begin(); it != end; it++) {
        a_Modelers.push_back(it->first);
    }
}

ModelerInterface* ModelerFactory::getModeler(std::string& a_Name)
{
    ModelerInterface* vRet = nullptr;
    t_mapPlugIns::iterator vIter = m_PlugIns.find(a_Name);
    if (vIter != m_PlugIns.end()) {
        vRet = vIter->second;
    }
    else {
        spdlog::warn("cannot find modeler " + a_Name);
    }
    return vRet;
}

bool ModelerFactory::findModelers(const std::string& a_Path)
{
    bool vRet = false;
    std::string filterExt, filterStart;
#if (defined (_WIN32) || defined (_WIN64))
    filterExt = "*.dll";
    filterStart = "MIP";
#else
    filterExt = "*.so";
    filterStart = "libMIP";
#endif
    spdlog::debug("Search modelers in: " + a_Path);
    fs::path vPath(a_Path);
    for (auto const& dir_entry : fs::directory_iterator{ vPath }) {
        if (!dir_entry.is_directory()) {
            const fs::path& vFile = dir_entry.path();
            if (vFile.extension() == filterExt) {
                std::string vName = vFile.stem().string();
                size_t vPos = vName.rfind("Modeler");
                if (vPos != std::string::npos) {
                    if (vName.rfind(filterStart, 0) == std::string::npos) {
                        ModelerInterface* vPlugIn = load(fs::absolute(vFile).string());
                        if (vPlugIn != nullptr) {
                            m_PlugIns[vPlugIn->Infos()] = vPlugIn;
                            vRet = true;
                        }
                    }
                }
            }
        }
    }
    return vRet;
}

ModelerInterface* ModelerFactory::load(const std::string& a_FileName)
{
    ModelerInterface* vRet = nullptr;
    if (a_FileName == "")
        return vRet;

    // TODO


    return vRet;
}
