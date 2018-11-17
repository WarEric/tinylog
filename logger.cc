/**
 * by wareric@163.com 2018-10-21
 **/
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include "logger.h"

namespace tinylog{

Logger::Logger():clilevel(INFO)
{
	fd = -1;
	opencli = 1;
	
	if(pthread_mutex_init(&mutex, NULL) != 0)
	{
		std::cerr << "logger pthread_mutex_init fail" << std::endl;
	}
}

Logger::Logger(std::string file, LEVEL lev):fdlevel(lev)
{
	opencli = 0;
	if((fd = open(file.c_str(), O_WRONLY|O_CREAT|O_TRUNC|O_CLOEXEC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0){
		std::cerr << "create logfile " << file << " fail." << std::endl;
		fd = -1;
	}
	
	if(pthread_mutex_init(&mutex, NULL) != 0)
	{
		std::cerr << "logger pthread_mutex_init fail" << std::endl;
	}
}

Logger::Logger(int openflag, LEVEL lev):clilevel(lev)
{
	fd = -1;
	opencli = openflag;
	
	if(pthread_mutex_init(&mutex, NULL) != 0)
	{
		std::cerr << "logger pthread_mutex_init fail" << std::endl;
	}
}

Logger::Logger(std::string file, LEVEL filelev, int openflag, LEVEL clilev):fdlevel(filelev), clilevel(clilev)
{
	opencli = openflag;
	if((fd = open(file.c_str(), O_WRONLY|O_CREAT|O_TRUNC|O_CLOEXEC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0){
		std::cerr << "create logfile " << file << " fail." << std::endl;
		fd = -1;
	}
	
	if(pthread_mutex_init(&mutex, NULL) != 0)
	{
		std::cerr << "logger pthread_mutex_init fail" << std::endl;
	}
}

Logger::~Logger()
{
	if(fd > 0) close(fd);
	pthread_mutex_destroy(&mutex);
	if(opencli)
		write(STDOUT_FILENO, "\033[0m", strlen("\033[0m"));
}

void Logger::trace(std::string msg)
{
	pthread_mutex_lock(&mutex);

	//block all sinal
	sigset_t newmask, oldmask;
	sigfillset(&newmask);
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	{
		std::string str("logger sigprocmask SIG_BLOCK error");
		if(fd > 0)
			write_log(FATAL, fd, str);
		if(opencli)
			write_screen(FATAL, STDOUT_FILENO, str);
		exit(EXIT_FAILURE);
	}

	if(fd > 0)
	{
		if(fdlevel <= TRACE)
			write_log(TRACE, fd, msg);
	}

	if(opencli != 0)
	{
		if(clilevel <= TRACE)
			write_screen(TRACE, STDOUT_FILENO, msg);
	}

	//resume old singal
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		std::string str("logger sigprocmask SIG_SETMASK error");
		if(fd > 0)
			write_log(FATAL, fd, str);
		if(opencli)
			write_screen(FATAL, STDOUT_FILENO, str);
		exit(EXIT_FAILURE);
	}

	pthread_mutex_unlock(&mutex);
}

void Logger::debug(std::string msg)
{
	pthread_mutex_lock(&mutex);

	//block all sinal
	sigset_t newmask, oldmask;
	sigfillset(&newmask);
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	{
		std::string str("logger sigprocmask SIG_BLOCK error");
		if(fd > 0)
			write_log(FATAL, fd, str);
		if(opencli)
			write_screen(FATAL, STDOUT_FILENO, str);
		exit(EXIT_FAILURE);
	}

	if(fd > 0)
	{
		if(fdlevel <= DEBUG)
			write_log(DEBUG, fd, msg);
	}

	if(opencli != 0)
	{
		if(clilevel <= DEBUG)
			write_screen(DEBUG, STDOUT_FILENO, msg);
	}

	//resume old singal
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		std::string str("logger sigprocmask SIG_SETMASK error");
		if(fd > 0)
			write_log(FATAL, fd, str);
		if(opencli)
			write_screen(FATAL, STDOUT_FILENO, str);
		exit(EXIT_FAILURE);
	}

	pthread_mutex_unlock(&mutex);
}

void Logger::info(std::string msg)
{
	pthread_mutex_lock(&mutex);

	//block all sinal
	sigset_t newmask, oldmask;
	sigfillset(&newmask);
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	{
		std::string str("logger sigprocmask SIG_BLOCK error");
		if(fd > 0)
			write_log(FATAL, fd, str);
		if(opencli)
			write_screen(FATAL, STDOUT_FILENO, str);
		exit(EXIT_FAILURE);
	}

	if(fd > 0)
	{
		if(fdlevel <= INFO)
			write_log(INFO, fd, msg);
	}

	if(opencli != 0)
	{
		if(clilevel <= INFO)
			write_screen(INFO, STDOUT_FILENO, msg);
	}

	//resume old singal
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		std::string str("logger sigprocmask SIG_SETMASK error");
		if(fd > 0)
			write_log(FATAL, fd, str);
		if(opencli)
			write_screen(FATAL, STDOUT_FILENO, str);
		exit(EXIT_FAILURE);
	}

	pthread_mutex_unlock(&mutex);
}

void Logger::warn(std::string msg)
{
	pthread_mutex_lock(&mutex);

	//block all sinal
	sigset_t newmask, oldmask;
	sigfillset(&newmask);
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	{
		std::string str("logger sigprocmask SIG_BLOCK error");
		if(fd > 0)
			write_log(FATAL, fd, str);
		if(opencli)
			write_screen(FATAL, STDOUT_FILENO, str);
		exit(EXIT_FAILURE);
	}

	if(fd > 0)
	{
		if(fdlevel <= WARN)
			write_log(WARN, fd, msg);
	}

	if(opencli != 0)
	{
		if(clilevel <= WARN)
			write_screen(WARN, STDOUT_FILENO, msg);
	}

	//resume old singal
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		std::string str("logger sigprocmask SIG_SETMASK error");
		if(fd > 0)
			write_log(FATAL, fd, str);
		if(opencli)
			write_screen(FATAL, STDOUT_FILENO, str);
		exit(EXIT_FAILURE);
	}

	pthread_mutex_unlock(&mutex);
}

void Logger::error(std::string msg)
{
	pthread_mutex_lock(&mutex);

	//block all sinal
	sigset_t newmask, oldmask;
	sigfillset(&newmask);
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	{
		std::string str("logger sigprocmask SIG_BLOCK error");
		if(fd > 0)
			write_log(FATAL, fd, str);
		if(opencli)
			write_screen(FATAL, STDOUT_FILENO, str);
		exit(EXIT_FAILURE);
	}

	if(fd > 0)
	{
		if(fdlevel <= ERROR)
			write_log(ERROR, fd, msg);
	}

	if(opencli != 0)
	{
		if(clilevel <= ERROR)
			write_screen(ERROR, STDOUT_FILENO, msg);
	}

	//resume old singal
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		std::string str("logger sigprocmask SIG_SETMASK error");
		if(fd > 0)
			write_log(FATAL, fd, str);
		if(opencli)
			write_screen(FATAL, STDOUT_FILENO, str);
		exit(EXIT_FAILURE);
	}

	pthread_mutex_unlock(&mutex);
}

void Logger::fatal(std::string msg)
{
	pthread_mutex_lock(&mutex);

	//block all sinal
	sigset_t newmask, oldmask;
	sigfillset(&newmask);
	if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	{
		std::string str("logger sigprocmask SIG_BLOCK error");
		if(fd > 0)
			write_log(FATAL, fd, str);
		if(opencli)
			write_screen(FATAL, STDOUT_FILENO, str);
		exit(EXIT_FAILURE);
	}

	if(fd > 0)
	{
		if(fdlevel <= FATAL)
			write_log(FATAL, fd, msg);
	}

	if(opencli != 0)
	{
		if(clilevel <= FATAL)
			write_screen(FATAL, STDOUT_FILENO, msg);
	}

	//resume old singal
	if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	{
		std::string str("logger sigprocmask SIG_SETMASK error");
		if(fd > 0)
			write_log(FATAL, fd, str);
		if(opencli)
			write_screen(FATAL, STDOUT_FILENO, str);
		exit(EXIT_FAILURE);
	}

	pthread_mutex_unlock(&mutex);
}

int Logger::write_log(LEVEL level, int fd, std::string msg)
{
	switch(level){
		case TRACE:
			msg.insert(0, " TRACE: ");
			break;
		case DEBUG:
			msg.insert(0, " DEBUG: ");
			break;
		case INFO:
			msg.insert(0, " INFO:  ");
			break;
		case WARN:
			msg.insert(0, " WARN:  ");
			break;
		case ERROR:
			msg.insert(0, " ERROR: ");
			break;
		case FATAL:
			msg.insert(0, " FATAL: ");
			break;
		default:
			break;
	}
	msg.insert(0, logtime());
	msg.append("\n");
	int n = write(fd, msg.c_str(), msg.size());
	return n;
}

int Logger::write_screen(LEVEL level, int fd, std::string msg)
{
	switch(level){
		case TRACE:
			msg.insert(0, " TRACE: ");
			msg.insert(0, logtime());
			msg.insert(0, "\033[36m");			//deepgreen
			break;
		case DEBUG:
			msg.insert(0, " DEBUG: ");
			msg.insert(0, logtime());
			msg.insert(0, "\033[32m");			//green
			break;
		case INFO:
			msg.insert(0, " INFO:  ");
			msg.insert(0, logtime());
			msg.insert(0, "\033[34m");			//blue
			break;
		case WARN:
			msg.insert(0, " WARN:  ");
			msg.insert(0, logtime());
			msg.insert(0, "\033[35m");			//purple
			break;
		case ERROR:
			msg.insert(0, " ERROR: ");
			msg.insert(0, logtime());
			msg.insert(0, "\033[33m");			//yellow
			break;
		case FATAL:
			msg.insert(0, " FATAL: ");
			msg.insert(0, logtime());
			msg.insert(0, "\033[31m");			//red
			break;
		default:
			break;
	}
	msg.append("\033[0m\n");
	int n = write(fd, msg.c_str(), msg.size());
	return n;
}

/**
 * I got the time code from internet, though it isn't efficient.
 **/
std::string Logger::logtime()
{
	struct timeval  tv;
	char	timeArray[40];

        gettimeofday(&tv, NULL);
        memset(timeArray, 0, sizeof(timeArray));
        strftime(timeArray, sizeof(timeArray) - 1, "%F %T", localtime(&tv.tv_sec));

	std::string usecond(std::to_string(tv.tv_usec) + "(us)               "); // blank is essential format
	usecond = usecond.substr(0, 6+4);

	std::stringstream ss;
	ss << std::string(timeArray) << "." << usecond;
	return ss.str();
}

}
