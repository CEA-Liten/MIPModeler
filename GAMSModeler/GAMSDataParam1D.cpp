#include "GAMSDataParam1D.h"

namespace GAMSModeler {

GAMSDataParam1D::GAMSDataParam1D(std::string name, std::string setName, std::vector<double> value)
    : GAMSData(name, GAMSDataType::GAMS_PARAM1D),
      mSetName(setName),
      mValue(value)
{

}

GAMSDataParam1D::~GAMSDataParam1D()
{

}

};
