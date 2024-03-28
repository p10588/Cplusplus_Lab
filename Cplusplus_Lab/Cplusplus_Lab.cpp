// DesignPatternTesting.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Singleton.h"
#include "MultiJson/Settings.h"
#include "SqliteORMTesting/Settings.h"
//#include "SQL/person.hxx"
using namespace MulitJson;
//using namespace SQL;

int main()
{
	MultiJsonTest();
	
	TestODBMain();
}


