#include "String.h"
#include <codecvt>
#include <io.h>
#include <fcntl.h>
#include <comdef.h>

String::String() {
    _setmode(_fileno(stdout), _O_U8TEXT);
    string = L"";
}

String::String(const char* s) {
    _setmode(_fileno(stdout), _O_U8TEXT);
    string = convert(s);
    
}

String::String(std::string& s) {
    _setmode(_fileno(stdout), _O_U8TEXT);
    string = convert(s);
}

String::String(std::wstring& s) {
    _setmode(_fileno(stdout), _O_U8TEXT);
    string = s;
}

void String::Set(std::string s) {
    string = convert(s);
}

std::wstring String::Get() {
    return string;
}
//
const char* String::GetChar() {
    return toString().c_str();
}

void String::Print() {
    std::wcout << string << std::endl;
}

bool String::operator==(std::string& s) {
    return string == convert(s);
}

bool String::operator==(String& s) {
    return string == s.Get();
}

void String::operator=(String& s) {
    string = s.Get();
}

void String::operator=(std::string& s) {
    string = convert(s);
}

String String::operator+(String& s) {
    return String(string += s.Get());
}

String String::operator+(const char* s) {
    return String(string += convert(s));
}

String String::operator+(const char s) {
    return String(string += convert(&s));
}

String String::operator+(std::string& s) {
    return String(string += convert(s));
}

void String::operator+=(std::string& s) {
    string += convert(s);
}

void String::operator+=(String& s) {
    string += s.string;
}

void String::operator+=(const char* s) {
    string += convert(s);
}

void String::operator+=(const char s) {
    string += convert(&s);
}

bool String::operator>(String s) {
    return string > s.Get();
}

bool String::operator<(String s) {
    return string < s.Get();
}

std::wstring String::convert(const std::string& input) {
    try
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(input);
    }
    catch (std::range_error & e)
    {
        size_t length = input.length();
        std::wstring result;
        result.reserve(length);
        for (size_t i = 0; i < length; i++)
        {
            result.push_back(input[i] & 0xFF);
        }
        return result;
    }
}

std::string String::toString() {
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(string);
}