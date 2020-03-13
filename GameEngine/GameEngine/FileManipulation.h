#pragma once
#include <sstream>
#include <fstream>
#include <Windows.h>
#include "String.h"
#include "DataStructure/Map.h"

class FileManipulation
{
public:
	FileManipulation();
	FileManipulation(String filename, bool parse);
	FileManipulation(std::string filename, bool parse);
	FileManipulation(const char* filename, bool parse);

	void openFile(std::string filename, bool parse);
	void openFile(String filename, bool parse);

	void createFile(String fileName, String file);

	int GetValueInt(String id);
	float GetValueFloat(String id);
	String GetValueString(String id);
	String GetText();

private:
	void SetValues(String text);
	void ReadFile(String fileName, bool parse);
	Map<String, String> valueMap;
	String text;
};

