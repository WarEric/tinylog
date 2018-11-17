#include "logger.h"
using tinylog::Logger;

int main(void)
{
	Logger logger("example.log", Logger::TRACE, 1, Logger::TRACE);

	logger.trace("this is trace");
	logger.debug("this is debug");
	logger.info("this is info");
	logger.warn("this is warn");
	logger.error("this is error");
	logger.fatal("this is fatal");

	return 0;
}
