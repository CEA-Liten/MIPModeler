#ifndef MIPLOGGER_H
#define MIPLOGGER_H

#include "MIPModeler_global.h"
#include "spdlog/spdlog.h"

namespace MIPModeler {

	void MIPMODELERSHARED_EXPORT InitLogger(std::shared_ptr<spdlog::logger> default_logger);
	std::shared_ptr<spdlog::logger> MIPMODELERSHARED_EXPORT GetLogger();
}


#endif
