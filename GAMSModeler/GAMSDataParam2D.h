/*
 * GAMSModeler - General Algebraic Modeling System C++ API
 *
 * Author: Yacine Gaoua
 * @mail : yacine.gaoua@cea.fr
 */

#ifndef GAMSDATAPARAM2D_H
#define GAMSDATAPARAM2D_H

#include <string>
#include <vector>

#include "GAMSModeler_global.h"
#include "GAMSData.h"

namespace GAMSModeler {

class GAMSMODELERSHARED_EXPORT GAMSDataParam2D : public GAMSData {

    public:
        /// Standard constructor.
        GAMSDataParam2D();

        /// Standard constructor.
        /// \param gams parameter name.
        /// \param gams parameter first set name.
        /// \param gams parameter second set name.
        /// \param parameter values.
        GAMSDataParam2D(std::string name, std::string setName1, std::string setName2, std::vector<std::vector<double>> value);

        /// Desctructor.
        ~GAMSDataParam2D();

        /// Get gams parameter set names.
        /// \return Return gams parameter set names.
        std::vector<std::string> getSet() {return mSetName;};

        /// Get parameter 2d values.
        /// \return Return parameter 2d values.
        std::vector<std::vector<double>>& getValue() {return mValue;};

    private:
        std::vector<std::string> mSetName;
        std::vector<std::vector<double>> mValue;
};
}

#endif // GAMSDATAPARAM2D_H
