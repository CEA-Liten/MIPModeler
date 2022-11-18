/*
 * GAMSModeler - General Algebraic Modeling System C++ API
 *
 * Author: Yacine Gaoua
 * @mail : yacine.gaoua@cea.fr
 */

#ifndef GAMSDATAPARAM1D_H
#define GAMSDATAPARAM1D_H

#include <string>
#include <vector>

#include "GAMSModeler_global.h"
#include "GAMSData.h"

namespace GAMSModeler {

class GAMSMODELERSHARED_EXPORT GAMSDataParam1D : public GAMSData {

    public:
        /// Standard constructor.
        GAMSDataParam1D() = default;

        /// Standard constructor.
        /// \param gams parameter name.
        /// \param gams parameter set name.
        /// \param parameter values.
        GAMSDataParam1D(std::string name, std::string setName, std::vector<double> value);

        /// Desctructor.
        ~GAMSDataParam1D();

        /// Get gams parameter set name.
        /// \return Return gams parameter set name.
        std::string getSet() {return mSetName;};

        /// Get parameter 1d values.
        /// \return Return parameter 1d values.
        std::vector<double>& getValue() {return mValue;};

    private:
        std::string mSetName;
        std::vector<double> mValue;

};
}

#endif // GAMSDATAPARAM1D_H
