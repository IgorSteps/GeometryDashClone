#pragma once
#include <string>
class Serialise
{
public:
	virtual std::string serialise(int tabSize) = 0;

	std::string beginObjectProperty(std::string name, int tabSize);
	std::string closeObjectProperty(int tabSize);

	std::string addStringProperty(std::string name, std::string value, int tabSize, bool newLine, bool comma);
	std::string addIntProperty(std::string name, int value, int tabSize, bool newLine, bool comma);
	std::string addFloatProperty(std::string name, float value, int tabSize, bool newLine, bool comma);
	std::string addDoublePorperty(std::string name, int value, int tabSize, bool newLine, bool comma);
	std::string addBooleanProperty(std::string name, bool value, int tabSize, bool newLine, bool comma);

	std::string addEnding(bool newline, bool comma);
	std::string addTabs(int tabSize);
};

