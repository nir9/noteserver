#pragma once

#include <string>

class ILogger
{
public:
	void virtual Log(const std::string& message) = 0;
};

class ConsoleLogger : public ILogger
{
public:
	void virtual Log(const std::string& message) override;
};

// TODO
class FileLogger : public ILogger
{
public:

	FileLogger(const std::string& filepath);

	void virtual Log(const std::string& message) override;
};

ConsoleLogger g_logger;