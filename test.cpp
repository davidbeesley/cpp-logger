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
