#include "GAMSDataParam2D.h"

namespace GAMSModeler{

GAMSDataParam2D::GAMSDataParam2D(std::string name, std::string setName1, std::string setName2, std::vector<std::vector<double>> value)
    : GAMSData(name, GAMSDataType::GAMS_PARAM2D),
      mValue(value)
{
    std::vector<std::string> setName(2);
    setName[0] = setName1;
    setName[1] = setName2;
    mSetName   = setName;
}

GAMSDataParam2D::~GAMSDataParam2D()
{

}

};
