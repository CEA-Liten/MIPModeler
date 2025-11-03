#include "MIPLogger.h"

namespace MIPModeler {

	void MIPMODELERSHARED_EXPORT InitLogger(std::shared_ptr<spdlog::logger> default_logger)
	{
		spdlog::set_default_logger(default_logger);
	}

	std::shared_ptr<spdlog::logger>MIPMODELERSHARED_EXPORT GetLogger()
	{
		return spdlog::default_logger();
	}
}
