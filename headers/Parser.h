#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <Component.h>
class Parser
{
public:
	static void openFile(std::string name);
	static bool atEnd();
	static char peek();
	static char advance();
	static void consume(char c);

	static void consumeBeginObjectProperty(std::string name);
	static void consumeEndObjectProperty();
	static std::string consumeStringProperty(std::string name);
	static int consumeIntProperty(std::string name);
	static float consumeFloatProperty(std::string name);
	static bool consumeBoolProperty(std::string name);

	static void skipWhitespace();
	static int parseInt();
	static bool parseBool();
	static float parseFloat();
	static std::string parseString();
	static Component* parseComponent();

private:
	static bool isDigit(char c);
	static void checkString(std::string str);

	static int offset;
	static int line;

	static std::string contents;
	static char characters[];
	static int length;

};

