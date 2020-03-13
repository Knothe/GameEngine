#include "FileManipulation.h"
#include "MessageException.h"
#include "Singletons/Debug.h"
#include <algorithm>
#include <codecvt>

FileManipulation::FileManipulation() {

}

FileManipulation::FileManipulation(String filename, bool parse) {
	ReadFile(filename, parse);
}

FileManipulation::FileManipulation(std::string filename, bool parse) {
	ReadFile(filename, parse);
}

FileManipulation::FileManipulation(const char* filename, bool parse) {
	ReadFile(filename, parse);
}

void FileManipulation::openFile(std::string filename, bool parse) {
	ReadFile(filename, parse);
}

void FileManipulation::openFile(String filename, bool parse) {
	ReadFile(filename, parse);
}

void FileManipulation::createFile(String fileName, String file) {
	std::wofstream fileOut(L"../../Assets/Files/" + fileName.Get());
	fileOut.imbue(std::locale(fileOut.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	fileOut << file.Get();
}

int FileManipulation::GetValueInt(String id) {
	if (valueMap.findKey(id)) {
		String t = valueMap.get(id);
		return std::stoi(t.Get());
	}
	throw 201;
}
	
float FileManipulation::GetValueFloat(String id) {
	if (valueMap.findKey(id)) {
		String t = valueMap.get(id);
		return std::stoi(t.Get());
	}
	throw 201;
}

String FileManipulation::GetValueString(String id) {
	if (valueMap.findKey(id)) {
		String t = valueMap.get(id);
		return t;
	}
	throw 201;
}

void FileManipulation::SetValues(String text) {

}

void FileManipulation::ReadFile(String fileName, bool parse) {
	String fileLoc("../../Assets/Files/");
	fileLoc += fileName;

	std::ifstream file;
	file.open(fileLoc.Get().c_str(), std::ios::out);

	if (file.is_open()) {
		if (parse) {
			std::string l;
			wchar_t* parsed = NULL;
			wchar_t* nextToken = NULL;
			wchar_t* text = NULL;
			while (std::getline(file, l)) {
				String temp(l);
				try {
					text = new wchar_t[temp.Get().length()];
					temp.Get().copy(text, temp.Get().length());
					text[temp.Get().length()] = '\0';
					nextToken = NULL;
					parsed = wcstok_s(text, L" :\n", &nextToken);
					if (parsed != NULL) {
						String key(parsed);
						String value;
						parsed = wcstok_s(NULL, L" :\n", &nextToken);
						while (parsed != NULL) {
							value += parsed;
							parsed = wcstok_s(NULL, L" :\n", &nextToken);
						}
						if (key.Get() != L"" && value.Get() != L"")
							valueMap.push(key, value);
					}
				}
				catch (...) {

				}
			}
		}
	}
	else {
		file.close();
		throw 301;
		//throw MessageException("File " + fileName.toString() + " not found");
	}
	file.close();

}


