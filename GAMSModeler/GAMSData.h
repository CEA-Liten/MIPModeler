/*
 * GAMSModeler - General Algebraic Modeling System C++ API
 *
 * Author: Yacine Gaoua
 * @mail : yacine.gaoua@cea.fr
 */

#ifndef GAMSDATA_H
#define GAMSDATA_H

#include <string>

#include "GAMSModeler_global.h"

namespace GAMSModeler {

enum GAMSDataType {GAMS_SET, GAMS_SCALAR, GAMS_PARAM1D, GAMS_PARAM2D, GAMS_PARAM3D};

class GAMSMODELERSHARED_EXPORT GAMSData {

    public:
        /// Standard constructor.
        GAMSData() = default;

        /// Standard constructor.
        /// \param gams data name.
        /// \param data type.
        GAMSData(const std::string& name, const GAMSDataType& type);

        /// Desctructor.
        virtual ~GAMSData();

        /// Get gams data name.
        /// \return Return gams data name.
        std::string name() const {return mName;};

        /// Get gams data type.
        /// \return Return gams data type.
        GAMSDataType type() const {return mType;};

    protected:
        std::string  mName;
        GAMSDataType mType;
};

}

#endif // GAMSDATA_H
