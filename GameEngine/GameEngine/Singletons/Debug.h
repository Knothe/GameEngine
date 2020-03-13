#pragma once
#include <windows.h>
#include <iostream>
#include "../String.h"
#include "../FileManipulation.h"

class Debug
{
public:
	static Debug* GetPtr();
	void Log(std::string s);
	void Log(String s);
	void LogError(std::string s);
	void LogError(char const* s);
	void LogError(String s);
	void LogError(int s);
	void LogFatalError(char const* s);
	void LogFatalError(String s);
	void LogFatalError(int s);
	void LogWarning(std::string s);
	void LogWarning(String s);
	void LogWarning(int s);

private:
	Debug();
	static Debug* ptr;
	HANDLE hConsole;
	String log;
	FileManipulation errors;
};

