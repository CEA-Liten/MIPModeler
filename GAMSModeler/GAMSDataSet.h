/*
 * GAMSModeler - General Algebraic Modeling System C++ API
 *
 * Author: Yacine Gaoua
 * @mail : yacine.gaoua@cea.fr
 */

#ifndef GAMSDATASET_H
#define GAMSDATASET_H

#include <string>
#include <vector>

#include "GAMSModeler_global.h"
#include "GAMSData.h"

namespace GAMSModeler{

class GAMSMODELERSHARED_EXPORT GAMSDataSet : public GAMSData {

    public:
        /// Standard constructor.
        GAMSDataSet() = default;

        /// Standard constructor.
        /// \param gams set name.
        /// \param gams set dimension.
        /// \param gams set reccords.
        GAMSDataSet(std::string name, std::vector<std::string> reccords);

        /// Desctructor.
        ~GAMSDataSet();

        /// Get set reccords.
        /// \return return set reccords.
        std::vector<std::string>& getReccords() {return mReccords;};

    private:
        std::vector<std::string> mReccords;
};

}

#endif // GAMSDATASET_H
