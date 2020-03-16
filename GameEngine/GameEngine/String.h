#pragma once
#include <iostream>

class String
{
public:
	String();
	String(const char* s);
	String(const wchar_t* s);
	String(std::string s);
	String(std::wstring& s);
	void Set(std::string s);
	std::wstring Get();
	const char* GetChar();
	void Print();

	bool operator==(std::string& s);
	bool operator==(String s);
	void operator=(String s);
	void operator=(std::string& s);
	String operator+(String& s);
	String operator+(const char* s);
	String operator+(const char s);
	String operator+(std::string& s);
	void operator+=(std::string& s);
	void operator+=(String& s);
	void operator+=(const char* s);
	void operator+=(const char s);
	void operator+=(wchar_t* s);
	bool operator>(String s);
	bool operator<(String s);
	bool operator!=(String& s);
	std::string toString();

private:
	std::wstring string;

	std::wstring convert(const std::string& input);


};

