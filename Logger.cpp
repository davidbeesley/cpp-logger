
#include "Logger.h"
#include <bits/stdc++.h>


/* Our color wheel */
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m" // Error
#define KGRN  "\x1B[32m" // Passed
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m" // Debug
#define KMAG  "\x1B[35m" // Info
#define KCYN  "\x1B[36m" // Warning
#define KWHT  "\x1B[37m"

/* LogLevel shortcuts */
#define DEBUG LogLevel::DEBUG
#define INFO LogLevel::INFO
#define WARNING LogLevel::WARNING
#define ERROR LogLevel::ERROR
#define NONE LogLevel::NONE


#define MAX_BUF 500 // test string buffer size

/* Constructors */
Logger::Logger(){
	init(WARNING);
	outFile = stdout;
	usingSTDOUT = true;
	//outFile = stdout;

}
Logger::Logger(LogLevel newLogLevel){
	init(newLogLevel);
	outFile = stdout;
	usingSTDOUT = true;

}
Logger::Logger(LogLevel newLogLevel, std::string filePath){
	init(newLogLevel);
	outFile = std::fopen(filePath.c_str(), "w");
	usingSTDOUT = true;

}

Logger::Logger(std::string filePath){
	init(WARNING);
	outFile = std::fopen(filePath.c_str(), "w");
	usingSTDOUT = true;



}

Logger::~Logger(){
	if (!usingSTDOUT) {
		fclose(outFile);
	}
	delete printingLock;
}

void Logger::init(LogLevel newLogLevel){
	passedTests = 0;
	totalTests = 0;
	logLevel = newLogLevel;
	printingLock = new mutex;
	newTestSuite();
}


void Logger::setLogLevel(LogLevel newLogLevel){
	logLevel = newLogLevel;
	//debug("Changed log level");
}


/* Testing Functions
 * Test suites are for grouping together related tests.
 */
void Logger::newTestSuite(){
	newTestSuite("Unnamed Test Suite");
}
void Logger::newTestSuite(std:: string testSuiteName){
	if (totalTests > 0) {
		debug("Ending Previous Test Suite: %s", this->testSuiteName.c_str());
		endTestSuite();
	}
	std::transform(testSuiteName.begin(), testSuiteName.end(), testSuiteName.begin(), ::toupper);
	this->testSuiteName = testSuiteName;
}

void Logger::endTestSuite(){
	std::string color;
	if (passedTests == totalTests && passedTests > 0)
		color = KGRN;
	else
		color = KRED;

	info("%sTest Results for Test Suite: %s", color.c_str(),testSuiteName.c_str());
	if (totalTests > 0) {
		info("%s%d / %d tests passed", color.c_str(), passedTests, totalTests);
		if (passedTests != totalTests) {
			info("%sFailed Tests:",KRED);
			while(failedTestsQueue.empty() == false) {
				info("  - %s%s", KRED, failedTestsQueue.front().c_str());
				failedTestsQueue.pop();
			}
		}
		if (passedTests > 0)
			debug("%sPassed Tests:",KGRN);
		while(passedTestsQueue.empty() == false) {
			debug("  - %s%s", KGRN, passedTestsQueue.front().c_str());
			passedTestsQueue.pop();
		}
	}
	else {
		info("%sNo Tests Provided", color.c_str());
	}
	totalTests = 0;
	passedTests = 0;


}

bool Logger::test(bool passed, std::string message)
{
	totalTests++;
	char c[MAX_BUF];
	std::string s;
	if (passed == false) {
		snprintf(c, MAX_BUF, "%s", message.c_str());
		warning("Test \"%s\" %s", message.c_str(), " failed.");
		s = c;
		failedTestsQueue.push(s);

	}
	else
	{
		snprintf(c, MAX_BUF, "%s", message.c_str());
		debug("Test \"%s\" %s", message.c_str(), " passed.");
		s = c;
		passedTestsQueue.push(s);
		passedTests++;
	}
	return passed;
}

bool Logger::test(bool passed)
{
	return test(passed, "No Message Provided");
}

bool Logger::testInt(long actual, long expected){
	return testInt(actual, expected,  "No Message Provided");
}
bool Logger::testInt(long actual, long expected, std:: string message){
	bool passed = (actual == expected);
	totalTests++;
	char c[MAX_BUF];
	std::string s;
	if (passed == false) {
		snprintf(c, MAX_BUF, "%s\n\t\tActual:   %10ld\n\t\tExpected: %10ld", message.c_str(), actual, expected);
		warning("Test \"%s\" %s", message.c_str(), " failed.");
		s = c;
		failedTestsQueue.push(s);

	}
	else
	{
		snprintf(c, MAX_BUF, "%s", message.c_str());
		debug("Test \"%s\" %s", message.c_str(), " passed.");
		s = c;
		passedTestsQueue.push(s);
		passedTests++;
	}
	return passed;

}

bool Logger::testHex(long actual, long expected){
	return testHex(actual, expected,  "No Message Provided");
}
bool Logger::testHex(long actual, long expected, std:: string message){
	bool passed = (actual == expected);
	totalTests++;
	char c[MAX_BUF];
	std::string s;
	if (passed == false) {
		snprintf(c, MAX_BUF, "%s\n\t\tActual:   0x%08lx\n\t\tExpected: 0x%08lx", message.c_str(), actual, expected);
		warning("Test \"%s\" %s", message.c_str(), " failed.");
		s = c;
		failedTestsQueue.push(s);

	}
	else
	{
		snprintf(c, MAX_BUF, "%s", message.c_str());
		debug("Test \"%s\" %s", message.c_str(), " passed.");
		s = c;
		passedTestsQueue.push(s);
		passedTests++;
	}
	return passed;

}
bool Logger::testBits(long actual, long expected){
	return testBits(actual, expected,  "No Message Provided");
}
bool Logger::testBits(long actual, long expected, std:: string message){
	bool passed = (actual == expected);
	totalTests++;
	char c[MAX_BUF];
	std::string s;
	if (passed == false) {
		char bitsActual[64+8];
		char bitsExpected[64+8];

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 9; j++) {
				int index = 9 * i + j;
				if (j == 8) {
					if (i != 7) {
						bitsActual[index] = ' ';
						bitsExpected[index] = ' ';
					}
					else {
						bitsActual[index] = 0;
						bitsExpected[index] = 0;
					}
				}
				else {
					int shift = 63 - (8 * i + j);
					int actualBit = (actual >> shift) & 1;
					int expectedBit = (expected >> shift) & 1;
					bitsActual[index] = actualBit ? '1' : '0';
					bitsExpected[index] = expectedBit ? '1' : '0';
				}
			}

		}
		snprintf(c, MAX_BUF, "%s\n\t\tActual:   %s\n\t\tExpected: %10s", message.c_str(), bitsActual, bitsExpected);
		warning("Test \"%s\" %s", message.c_str(), " failed.");
		s = c;
		failedTestsQueue.push(s);

	}
	else
	{
		snprintf(c, MAX_BUF, "%s", message.c_str());
		debug("Test \"%s\" %s", message.c_str(), " passed.");
		s = c;
		passedTests++;
		passedTestsQueue.push(s);
	}
	return passed;

}


bool Logger::testFloat(double actual, double expected){
	return testFloat(actual, expected,  "No Message Provided");

}
bool Logger::testFloat(double actual, double expected, std:: string message){
	bool passed = (actual == expected);
	totalTests++;
	char c[MAX_BUF];
	std::string s;
	if (passed == false) {
		snprintf(c, MAX_BUF, "%s\n\t\tActual:   %21.10F\n\t\tExpected: %21.10F", message.c_str(), actual, expected);
		warning("Test \"%s\" %s", message.c_str(), " failed.");
		s = c;
		failedTestsQueue.push(s);

	}
	else
	{
		snprintf(c, MAX_BUF, "%s", message.c_str());
		debug("Test \"%s\" %s", message.c_str(), " passed.");
		s = c;
		passedTests++;
		passedTestsQueue.push(s);
	}
	return passed;


}
bool Logger::testString(std::string actual, std::string expected){
	return testString(actual, expected,  "No Message Provided");

}
bool Logger::testString(std::string actual, std::string expected, std:: string message){
	bool passed = (actual == expected);
	totalTests++;
	char c[MAX_BUF];
	std::string s;
	if (passed == false) {
		snprintf(c, MAX_BUF, "%s\n\t\tActual:    \"%s\"\n\t\tExpected:  \"%s\"", message.c_str(), actual.c_str(), expected.c_str());
		warning("Test \"%s\" %s", message.c_str(), " failed.");
		s = c;
		failedTestsQueue.push(s);

	}
	else
	{
		snprintf(c, MAX_BUF, "%s", message.c_str());
		debug("Test \"%s\" %s", message.c_str(), " passed.");
		s = c;
		passedTests++;
		passedTestsQueue.push(s);
	}
	return passed;

}


/* Printing Functions */

void Logger::log(LogLevel stringLogLevel, std::string format, ...){
	va_list args;
	va_start(args, format);

	switch (stringLogLevel) {

	case DEBUG:
		debug(format, args);
		break;
	case INFO:
		info(format, args);
		break;
	case WARNING:
		warning(format,args);
		break;
	case ERROR:
		error(format,args);
		break;
	default:
		error("Invalid logLevel");
	}
	va_end(args);
}


void Logger::debug(std::string format, ...){
	va_list args;
	va_start(args, format);
	debug(format, args);
	va_end(args);
}

void Logger::info(std::string format, ...){
	va_list args;
	va_start(args, format);


	info(format, args);
	va_end(args);
}

void Logger::warning(std::string format, ...){
	va_list args;
	va_start(args, format);

	warning(format,args);
	va_end(args);
}

void Logger::error(std::string format, ...){
	va_list args;
	va_start(args, format);


	error(format, args);
	va_end(args);
}


/* THE FOLLOWING FUNCTIONS ARE THREAD SAFE
   The entire message will be printed in one go
 */

void Logger::debug(std::string format, va_list args){
	unique_lock<mutex> lck(*printingLock);

	if (logLevel <= DEBUG)
	{
		fprintf(outFile,"%s",KCYN);
		fprintf(outFile,"[DEBUG]   ");
		vfprintf(outFile,format.c_str(), args);
		fprintf(outFile,"%s\n", KNRM);
	}

}

void Logger::info(std::string format, va_list args){
	unique_lock<mutex> lck(*printingLock);

	if (logLevel <= INFO)
	{
		fprintf(outFile,"%s",KMAG);
		fprintf(outFile,"[INFO]    ");
		vfprintf(outFile,format.c_str(), args);
		fprintf(outFile,"%s\n", KNRM);
	}
}

void Logger::warning(std::string format, va_list args){
	unique_lock<mutex> lck(*printingLock);


	if (logLevel <= WARNING)
	{
		fprintf(outFile,"%s",KYEL);
		fprintf(outFile,"[WARNING] ");
		vfprintf(outFile,format.c_str(), args);
		fprintf(outFile,"%s\n", KNRM);
	}

}

void Logger::error(std::string format, va_list args){
	unique_lock<mutex> lck(*printingLock);


	if (logLevel <= ERROR)
	{
		fprintf(outFile,"%s",KRED);
		fprintf(outFile,"[ERROR]   ");
		vfprintf(outFile,format.c_str(), args);
		fprintf(outFile,"%s\n", KNRM);
	}

}


void Logger::print(std::string format, ...){
	unique_lock<mutex> lck(*printingLock);

	va_list args;
	va_start(args, format);
	vprintf(format.c_str(),args);
	//format = "Printed: \"" + format + "\" to stdout";
	//debug("Printed to stdout: \"%.20s...\"", format.c_str());
	va_end(args);
}

void Logger::printLine(std::string format, ...){
	unique_lock<mutex> lck(*printingLock);

	va_list args;
	va_start(args, format);
	vprintf(format.c_str(),args);
	printf("\n");
	//format = "Printed Line: \"" + format + "\" to stdout";
	//debug("Printed line to stdout: \"%.20s...\"", format.c_str());
	va_end(args);
}
