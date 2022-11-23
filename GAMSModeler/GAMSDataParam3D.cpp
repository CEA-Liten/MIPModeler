#include "GAMSDataParam3D.h"

namespace GAMSModeler {

GAMSDataParam3D::GAMSDataParam3D(std::string name,
                                 std::string setName1,
                                 std::string setName2,
                                 std::string setName3,
                                 std::vector<std::vector<std::vector<double>>> value)
    : GAMSData(name, GAMSDataType::GAMS_PARAM3D),
      mValue(value)
{
    std::vector<std::string> setName(3);
    setName[0] = setName1;
    setName[1] = setName2;
    setName[2] = setName3;
    mSetName   = setName;
}

GAMSDataParam3D::~GAMSDataParam3D()
{

}

};
