# tinylog
A tiny c++ log library. It records log messages to a file in current directory and print these to screen. I try my best to make it as easy
as log4j(java) library. Actually the log level is set as log4j level.

# advantages
- It's very easy to be integrated into your project by putting two files (logger.cc logger.h) into your project. No other dependencies.
- It's singal safe, your log operation won't be interrupted.
- It's thread safe, we use pthread_mutex to make sure log operation thread won't give up cpu time.

# demo
## 1.example code
Just use the logger class in your code, such as example.cc
```c++
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
```
## 2.compile
Remember to add pthread library into your compile commands, because we use pthread_mutex to handle thread congestions.
```
gcc -o example example.cc logger.cc -lphtread
```
Or you can refer to our example makefile.
```Makefile
ALL=example

example:example.cc logger.o
        g++ -o example example.cc logger.o
logger.o:logger.h logger.cc
        g++ -c logger.cc -lpthread

clean:
        - rm -f *.o
        - rm -f example

```
## 3.result
You console screen will print colorful logger messages and a log file will be created in current directory.

- screen
<div align=center><img src="https://github.com/WarEric/tinylog/raw/master/images/console.jpg"/></div>

- exmaple.log
<div align=center><img src="https://github.com/WarEric/tinylog/raw/master/images/example.jpg"/></div>

# screen and level control

|constructor|initial result|
|:----------|:-------|
|Logger()|opencli(1),  clilevel(INFO)|
|Logger(std::string file, LEVEL lev)|logfile(file),  fdlevel(lev)|
|Logger(int openflag, LEVEL lev)|opencli(openflag),  clilevel(lev)|
|Logger(std::string file, LEVEL filelev, int openflag, LEVEL clilev)|logfile(file), fdlevel(filelev), opencli(openflag), clilevel(clilev)|

### screen
You can choose to open or close logger messages printed on your screen by set openflag to 1 or 0 (0 represent close, others represent open).
### level
level orders
```
TRACE < DEBUG < INFO < WARN < ERROR < FATAL
```
If you set log level to A, the log level which smaller than A won't be logged.
# attentions
- Don't forget to append '-lphtread' when you compile logger.cc, otherwise this compile order will fail.
