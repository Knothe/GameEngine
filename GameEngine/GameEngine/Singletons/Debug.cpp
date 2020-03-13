#include "Debug.h"
#include "Platform.h"
#include "StackAllocator.h"
#include "Platform.h"
#include "../MessageException.h"
#include <io.h>
#include <fcntl.h>


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
	t += ".txt";
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
	log += s;
	log += 'n';
	String(s).Print();
}

void Debug::LogError(char const* s) {
	SetConsoleTextAttribute(hConsole, 12);
	log += s + '\n';
	String(s).Print();

}

void Debug::LogError(String s) {
	SetConsoleTextAttribute(hConsole, 12);
	log += s;
	log += '\n';
	s.Print();
}

void Debug::LogFatalError(char const* s) {
	SetConsoleTextAttribute(hConsole, 4);
	String(s).Print();
	log += s + '\n';
	SetConsoleTextAttribute(hConsole, 15);
	Platform::GetPtr()->Close();
}

void Debug::LogFatalError(String s) {
	SetConsoleTextAttribute(hConsole, 4);
	s.Print();
	log += s;
	log += '\n';
	SetConsoleTextAttribute(hConsole, 15);
	Platform::GetPtr()->Close();
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
	catch (MessageException e) {

	}
}

void Debug::LogFatalError(int s) {
	try {
		String t;
		t = errors.GetValueString("" + s);
		LogFatalError(t);
	}
	catch (MessageException e) {
		

	}
}

void Debug::LogWarning(int s) {
	try {
		String t;
		t = errors.GetValueString("" + s);
		LogWarning(t);
	}
	catch (MessageException e) {

	}
}

