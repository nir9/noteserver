#include "Logger.h"
#include <iostream>

using namespace std;

void ConsoleLogger::Log(const std::string& message)
{
	cout << message << endl;
}
