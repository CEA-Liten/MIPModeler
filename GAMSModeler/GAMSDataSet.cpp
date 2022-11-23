#include "GAMSDataSet.h"

namespace GAMSModeler {

GAMSDataSet::GAMSDataSet(std::string name, std::vector<std::string> reccords)
    : GAMSData(name, GAMSDataType::GAMS_SET),
      mReccords(reccords)
{

}

GAMSDataSet::~GAMSDataSet()
{

}

};
