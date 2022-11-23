#include "GAMSDataScalar.h"

namespace GAMSModeler {

GAMSDataScalar::GAMSDataScalar(std::string name, double value)
    : GAMSData(name, GAMSDataType::GAMS_SCALAR),
      mValue(value)
{

}

GAMSDataScalar::~GAMSDataScalar()
{

}

};
