#ifndef LOGGER_H_
#define LOGGER_H_


#include <iostream>
#include <stdarg.h>
#include <queue>          // std::queue for passed and failed tests
#include <fstream>        // for logging to a file
#include <mutex>          // for threaded logging
enum class LogLevel {DEBUG, INFO, WARNING, ERROR, NONE};

using namespace std;
class Logger {
public:

	Logger();
	Logger(LogLevel newLogLevel);
	Logger(std::string filePath);
	Logger(LogLevel newLogLevel, std::string filePath);
	~Logger();


	void setLogLevel(LogLevel newLogLevel);


// log functions
	void debug(std::string format, ...);
	void info(std::string format, ...);
	void warning(std::string format, ...);
	void error(std::string format, ...);
	void log(LogLevel stringLogLevel, std::string format, ...);




// Output to stdout and keep record in log
	void print(std::string format, ...);
	void printLine(std::string format, ...);

// test suites
	void newTestSuite();
	void newTestSuite(std:: string testSuiteName);

	// Rework to return number of failed tests
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


private:
	void init(LogLevel newLogLevel);
	void debug(std::string format, va_list args);
	void info(std::string format,  va_list args);
	void warning(std::string format,  va_list args);
	void error(std::string format,  va_list args);


	LogLevel logLevel;
	int totalTests;
	int passedTests;
	std::string testSuiteName;
	std::queue<std::string> passedTestsQueue, failedTestsQueue;

	FILE * outFile;
	bool usingSTDOUT;

	mutex * printingLock;

};






#endif // LOGGER_H_
