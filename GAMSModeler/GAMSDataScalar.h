#ifndef GAMSDATASCALAR_H
#define GAMSDATASCALAR_H

#include <string>
#include <vector>
#include "GAMSData.h"

namespace GAMSModeler {

class GAMSMODELERSHARED_EXPORT GAMSDataScalar : public GAMSData {

    public:
        /// Standard constructor.
        GAMSDataScalar() = default;

        /// Standard constructor.
        /// \param gams scalar name.
        /// \param scalar value.
        GAMSDataScalar(std::string name, double value);

        /// Desctructor.
        ~GAMSDataScalar();

        /// Get scalar value.
        /// \return Return scalar value.
        double getValue() {return mValue; } ;

    private:
        double mValue;
};

}

#endif // GAMSDATASCALAR_H
