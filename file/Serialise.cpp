#include "Serialise.h"


std::string Serialise::addTabs(int tabSize)
{
	return std::string(tabSize, '\t');
}

std::string Serialise::beginObjectProperty(std::string name, int tabSize)
{
	return addTabs(tabSize) + '\"' + name + "\": {" + addEnding(true, false);
}

std::string Serialise::closeObjectProperty(int tabSize)
{
	return addTabs(tabSize) + '}';
}

std::string Serialise::addStringProperty(std::string name, std::string value, int tabSize, bool newLine, bool comma)
{
	return addTabs(tabSize) + '\"' + name + "\": " + '\"' + value + '\"' + addEnding(newLine, comma);
}

std::string Serialise::addIntProperty(std::string name, int value, int tabSize, bool newLine, bool comma)
{
	return addTabs(tabSize) + '\"' + name + "\": " + std::to_string(value) + addEnding(newLine, comma);
}

std::string Serialise::addFloatProperty(std::string name, float value, int tabSize, bool newLine, bool comma)
{
	return addTabs(tabSize) + '\"' + name + "\": " + std::to_string(value) + 'f' + addEnding(newLine, comma);
}

std::string Serialise::addDoublePorperty(std::string name, int value, int tabSize, bool newLine, bool comma)
{
	return std::string();
}

std::string Serialise::addBooleanProperty(std::string name, bool value, int tabSize, bool newLine, bool comma)
{
	return addTabs(tabSize) + '\"' + name + "\": " + std::to_string(value) + addEnding(newLine, comma);
}

std::string Serialise::addEnding(bool newLine, bool comma)
{
	std::string str = "";
	if (comma) str += ',';
	if (newLine) str += '\n';
	return str;
}