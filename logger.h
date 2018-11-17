/**
 * A simple log class. It record log messages to a file in current directory.
 * I try my best to make it as easy as log4j(java) library. You must remember
 * to append "-lpthread" in your compile command because I use pthread mutex
 * to maintain thread safe. 
 *
 * by wareric@163.com 2018-10-21
 **/
#ifndef LOGGER_H_H
#define LOGGER_H_H
#include <string>

namespace tinylog{
class Logger{
	public:
		enum LEVEL{
			TRACE,
			DEBUG,
			INFO,
			WARN,
			ERROR,
			FATAL
		};

		Logger();
		Logger(std::string file, LEVEL lev);
		Logger(int openflag, LEVEL lev);
		Logger(std::string file, LEVEL filelev, int openflag, LEVEL clilev);

		~Logger();
		
		void trace(std::string msg);
		void debug(std::string msg);
		void info(std::string msg);
		void warn(std::string msg);
		void error(std::string msg);
		void fatal(std::string msg);
	private:
		Logger(const Logger&);			// forbide copy construct
		Logger& operator=(const Logger&);	// forbide assignment contruct

		//this will add time and level in head, insert a new line
		int write_log(LEVEL level, int fd, std::string msg);
		int write_screen(LEVEL level, int fd, std::string msg);
		
		std::string logtime();

		int fd;					// logfd
		LEVEL fdlevel;				// trace < debug < info < warn < error < fatal
		int opencli;				// 1 represent print to CLI, 0 represent not.
		LEVEL clilevel;				// trace < debug < info < warn < error < fatal
		pthread_mutex_t mutex;
};
}
#endif
