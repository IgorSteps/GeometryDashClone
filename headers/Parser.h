#pragma once
#include <string>
#include <fstream>
#include <iostream>
class Parser
{
public:
	static void openFile(std::string name);
	static bool atEnd();
	static char peek();
	static char advance();
	static void consume(char c);

	static void skipWhitespace();
	static int parseInt();
	static bool parseBool();
	static float parseFloat();
	static std::string parseString();

private:
	static bool isDigit(char c);

	static int offset;
	static int line;

	static std::string contents;
	static char characters[];
	static int length;

};

