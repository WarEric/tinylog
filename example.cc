#include "logger.h"
using tinylog::Logger;

int main(void)
{
	Logger logger("example.log", Logger::TRACE, 1, Logger::TRACE);

	logger.trace(LOG_FUNC+"this is trace");
	logger.debug(LOG_LINE+"this is debug");
	logger.info(LOG_FILE+"this is info");
	logger.warn(LOG_TIME+"this is warn");
	logger.error(LOG_DATE+"this is error");
	logger.fatal(LOG_FUNC+LOG_LINE+LOG_FILE+LOG_TIME+LOG_DATE+"this is fatal");

	return 0;
}
