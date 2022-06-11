/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Logger.h
Project: CS230
Author: Duho choi
Creation date: 3/22/2022
-----------------------------------------------------------------*/

#pragma once
#include <string>
#include <fstream>
#include <chrono>

namespace CS230 {
	class Logger {
	public:
		enum class Severity {
			Verbose,			// This option is for minor messages, which could be useful 
			Debug,			// This should only be used when you are currently trying to debug something
			Event,			// These are general events, such as key press, exit state, enter state, enter state finish
			Error,			// This is for an error, such as an asset is not found
		};	
		Logger(Severity severity, bool useConsole, std::chrono::system_clock::time_point startTime_);
		~Logger();		
		void LogError(std::string text) { Log(Severity::Error, text); }
		void LogEvent(std::string text) { Log(Severity::Event, text); }
		void LogDebug(std::string text) { Log(Severity::Debug, text); }
		void LogVerbose(std::string text) { Log(Severity::Verbose, text); }

	private:
		void Log(Severity, std::string displayText);
		std::ofstream outStream;
		Severity minLevel; 
		std::chrono::system_clock::time_point startTime;
		double GetSecondsSinceStart();
	};
}