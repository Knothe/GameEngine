#include "Debug.h"
#include "Platform.h"
#include "StackAllocator.h"
#include "Platform.h"
#include "../MessageException.h"
#include <io.h>
#include <fcntl.h>
#include <ctime>

Debug* Debug::ptr;

Debug* Debug::GetPtr() {
	if (!ptr) {
		void* buf = StackAllocator::GetPtr()->alloc(sizeof(Debug));
		ptr = new (buf) Debug();
	}
	return ptr;
}

Debug::Debug() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	String t = Platform::GetPtr()->language;
	t += ".json";
	errors.openFile(t, true);
}

void Debug::Log(std::string s) {
	SetConsoleTextAttribute(hConsole, 15);
	String(s).Print();
}

void Debug::Log(String s) {
	SetConsoleTextAttribute(hConsole, 15);
	s.Print();
}

void Debug::LogError(std::string s) {
	SetConsoleTextAttribute(hConsole, 12);
	String t(s);
	AddToLog(t);
	t.Print();
}

void Debug::LogError(char const* s) {
	SetConsoleTextAttribute(hConsole, 12);
	String t(s);
	AddToLog(t);
	t.Print();

}

void Debug::LogError(String s) {
	SetConsoleTextAttribute(hConsole, 12);
	AddToLog(s);

	s.Print();
}

void Debug::LogFatalError(char const* s) {
	SetConsoleTextAttribute(hConsole, 4);
	String t(s);
	AddToLog(t);
	t.Print();
	SetConsoleTextAttribute(hConsole, 15);
	FileManipulation f;
	f.createFile("log.json", log);
	Platform::GetPtr()->Close();
}

void Debug::LogFatalError(String s) {
	SetConsoleTextAttribute(hConsole, 4);
	s.Print();
	AddToLog(s);
	SetConsoleTextAttribute(hConsole, 15);
	FileManipulation f;
	f.createFile("log.json", log);
	Platform::GetPtr()->Close();
}

void Debug::AddToLog(String s) {
	std::time_t t = std::time(NULL);
	char str[26];
	ctime_s(str, sizeof str, &t);
	log += str;
	log += s;
	log += "\n";
}

void Debug::LogWarning(std::string s) {
	SetConsoleTextAttribute(hConsole, 14);
	String(s).Print();
}

void Debug::LogWarning(String s) {
	SetConsoleTextAttribute(hConsole, 14);
	s.Print();
}

void Debug::LogError(int s) {
	try {
		std::string a = std::to_string(s);
		String t(a);
		t = errors.GetValueString(t);
		LogError(t);
	}
	catch (int e) {

	}
}

void Debug::LogFatalError(int s) {
	try {
		std::string a = std::to_string(s);
		String t(a);
		t = errors.GetValueString(t);
		LogFatalError(t);
	}
	catch (int e) {
		
	}
}

void Debug::LogWarning(int s) {
	try {
		std::string a = std::to_string(s);
		String t(a);
		t = errors.GetValueString(t);
		LogWarning(t);
	}
	catch (int e) {

	}
}

