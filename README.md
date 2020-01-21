# cpp-logger
Simple logger and test package for debugging c++ projects.

## Easest way to include in your project
```
wget https://raw.githubusercontent.com/davidbeesley/cpp-logger/master/Logger.cpp
wget https://raw.githubusercontent.com/davidbeesley/cpp-logger/master/Logger.h
```
## Usage
Initialize logger

```cpp
Logger();
Logger(LogLevel newLogLevel);
Logger(std::string filePath);
Logger(LogLevel newLogLevel, std::string filePath);
```

Possible Logging levels
```cpp
enum class LogLevel {DEBUG, INFO, WARNING, ERROR, NONE};
```


### Logging functions
logging functions take same format as printf and automatically print a new line.

set logging level with `l_setLogLevel`

output uses terminal colors, so it won't look very good using a program like less (unless you use the -R flag)
```c

// change logging level
void setLogLevel(LogLevel newLogLevel);

// log functions
void debug(std::string format, ...);
void info(std::string format, ...);
void warning(std::string format, ...);
void error(std::string format, ...);
void log(LogLevel stringLogLevel, std::string format, ...);
```

### Testing functions
```c
// test suites
void newTestSuite();
void newTestSuite(std:: string testSuiteName);
void endTestSuite();

// test functions
bool test(bool passed, std::string message);
bool test(bool passed);
bool testInt(long actual, long expected);
bool testInt(long actual, long expected, std:: string message);
bool testHex(long actual, long expected);
bool testHex(long actual, long expected, std:: string message);
bool testBits(long actual, long expected);
bool testBits(long actual, long expected, std:: string message);
bool testFloat(double actual, double expected);
bool testFloat(double actual, double expected, std:: string message);
bool testString(std::string actual, std::string expected);
bool testString(std::string actual, std::string expected, std:: string message);
```

### Example
```cpp
#include <iostream>
#include "Logger.h"


int main()
{

	Logger logger(LogLevel::DEBUG);
	logger.test(true, "Example Passed Test");
	logger.test(false, "Example Failed Test");
	logger.debug("Example Debug");
	logger.info("Example Info");
	logger.warning("Example Warning");
	logger.error("Example Error");


	logger.setLogLevel(LogLevel::DEBUG);
	logger.newTestSuite("A second test suite");
	logger.test(true, "Example Passed Test");
	logger.test(false, "Example Failed Test");
	logger.endTestSuite();

	logger.newTestSuite("A passed test suite");
	logger.test(true);
	logger.endTestSuite();
	logger.print("Hello World without newline! ");
    	logger.print("Now printing a newline: \n");
	logger.printLine("Hello World with newline!");


	logger.newTestSuite("testInt, testFloat, testString");
	logger.testInt(1,1,"First testInt. should pass");
	logger.testInt(1,0,"Second testInt. should fail");
	int one = 0xffab1;
	int two = 0x2;
	logger.testInt(one, two, "should fail");
	logger.testFloat(1.105215915, 1, "First testFloat, should fail");
	logger.testFloat(1.5, 1.5, "Second testFloat, should pass");
	float f1 = 1.5;
	double f2 = 2.25215129871235;
	logger.testFloat(f1, f2, "Should fail");
	logger.testString("h","j","First stringTest, should fail");
	logger.testHex(one,two, "should fail");
	logger.testBits(1,2, "Should fail");
	logger.testBits(-1000,-1, " Should fail");
	logger.testHex(-1,-2, "Should fail" );
	logger.endTestSuite();


}
```
