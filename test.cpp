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
	for (int i = 0; i < 4; i++) {
		logger.setLogLevel((LogLevel)i);
		for (int j = 0; j < 4; j++) {
			logger.log((LogLevel)j, "%d %d",i,j);

		}
	}

	logger.setLogLevel(LogLevel::DEBUG);
	logger.newTestSuite("A second test suite");
	logger.test(true, "Example Passed Test");
	logger.test(false, "Example Failed Test");
	logger.endTestSuite();

	logger.newTestSuite("A passed test suite");
	logger.test(true);
	logger.endTestSuite();
	logger.print("Hello World!");
	logger.printLine("Hello World!");


	logger.newTestSuite("testInt, testFloat, testString");
	logger.testInt(1,1,"First testInt");
	logger.testInt(1,0,"Second testInt");
	int one = 0xffab1;
	int two = 0x2;
	logger.testInt(one, two);
	logger.testFloat(1.105215915, 1, "First testFloat");
	logger.testFloat(1.5, 1.5, "Second testFloat");
	float f1 = 1.5;
	double f2 = 2.25215129871235;
	logger.testFloat(f1, f2);
	logger.testString("h","j","First stringTest");
	logger.testHex(one,two);
	logger.testBits(1,2);
	logger.testBits(-1000,-1);
	logger.testHex(-1,-2);
	logger.endTestSuite();


}
