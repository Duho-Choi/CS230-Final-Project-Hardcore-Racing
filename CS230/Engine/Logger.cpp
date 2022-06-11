/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Logger.cpp
Project: CS230
Author: Duho Choi
Creation date: 3/11/2022
-----------------------------------------------------------------*/
#include <iostream>    // cout.rdbuf
#include "Logger.h"

CS230::Logger::Logger(Logger::Severity severity, bool useConsole, std::chrono::system_clock::time_point startTime_) 
	: minLevel(severity), outStream("Trace.log"), startTime(startTime_) {
	if (useConsole == true) {
		outStream.set_rdbuf(std::cout.rdbuf());
	}
}

CS230::Logger::~Logger() {
	outStream.flush();
	outStream.close();
}

void CS230::Logger::Log(CS230::Logger::Severity severity, std::string message) {
	
	if (minLevel <= severity)
	{
		outStream.precision(4);
		outStream << '[' << std::fixed << GetSecondsSinceStart() << "]\t";
		switch(severity)
		{
		case CS230::Logger::Severity::Error:
			outStream << "Error\t" << message << std::endl;
			break;
		case CS230::Logger::Severity::Event:
			outStream << "Event\t" << message << std::endl;
			break;
		case CS230::Logger::Severity::Debug:
			outStream << "Debug\t" << message << std::endl;
			break;
		case CS230::Logger::Severity::Verbose:
			outStream << "Verb\t" << message << std::endl;
			break;
		}
	}
}

double CS230::Logger::GetSecondsSinceStart()
{
	return std::chrono::duration<double>(std::chrono::system_clock::now() - startTime).count();
}