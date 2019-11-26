#ifndef AUTO_H_
#define AUTO_H_

#include "main.h"

struct AutonomousInfo {

	int mode;
	int alliance;

}typedef AutonomousInfo;

extern AutonomousInfo autonomousInfoStruct;

#define DO_NOTHING 0
#define TEST 1
#define TOWERS 2

#endif
