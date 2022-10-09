#include "Parser.h"
#include <Sprite.h>
#include <GameObject.h>
#include <BoxBounds.h>


Parser::~Parser()
{
    delete[] Parser::characters;
    Parser::characters = nullptr;
}

void Parser::openFile(std::string name)
{
	std::ifstream myfile("levels/" + name + ".json");
    if (myfile.is_open())
    {
        std::string contents((std::istreambuf_iterator<char>(myfile)), std::istreambuf_iterator<char>());
        
        // length of characters[]
        Parser::length = contents.size();
        Parser::characters = new char[contents.size() + 1];
        // copy contetns into characters array 
        strcpy_s(Parser::characters, contents.size() + 1, contents.c_str());
        myfile.close();
    }
    else return;
}

void Parser::skipWhitespace()
{
    while (!atEnd() && (peek() == ' ' || peek() == '\n' || peek() == '\t' || peek() == '\r'))
    {
        if (peek() == '\n')
        {
            Parser::line++;
        }
        advance();
    }
}

char Parser::peek()
{
    return characters[offset];
}

char Parser::advance()
{
    char c = characters[offset];
    ++offset;
    return c;
}

void Parser::consume(char c)
{
    char actual = peek();
    if (actual != c)
    {
        std::cout << "Error: Expected '" << c << "' but instead got: '" << actual << "' at line: " << Parser::line << std::endl;
        exit(-1);
    }
    ++offset;
}

bool Parser::atEnd()
{
    return offset == Parser::length;
}

bool Parser::isDigit(char c)
{
    return c >= '0' && c <= '9';
}

void Parser::checkString(std::string str)
{
    std::string title = Parser::parseString();
    if (title.compare(str) != 0)
    {
        std::cout << "Expected '" << str << "' instead got '" << title << "' at line " << Parser::line << std::endl;
        exit(-1);
    }
}

int Parser::parseInt()
{
    skipWhitespace();
    char c;
    std::string builder;

    while (!atEnd() && isDigit(peek()) || peek() == '-')
    {
        c = advance();
        builder += c;
    }

    return std::stoi(builder);
}

bool Parser::parseBool()
{
    skipWhitespace();
    std::string builder;

    if (!atEnd() && peek() == 't')
    {
        builder.append("true");
        consume('t');
        consume('r');
        consume('u');
        consume('e');
    }
    else if (!atEnd() && peek() == 'f')
    {
        builder.append("false");
        consume('f');
        consume('a');
        consume('l');
        consume('s');
        consume('e');
    }
    else 
    {
        std::cout << "Expecting t or f, but got: " << peek() << " at line " << Parser::line << std::endl;
        exit(-1);
    }
    return builder.compare("true") == 0;
}

float Parser::parseFloat()
{
    skipWhitespace();
    char c;
    std::string builder;

    while (!atEnd() && isDigit(peek()) || peek() == '-' || peek() == '.')
    {
        c = advance();
        builder += c;
    }
    consume('f');
    return std::stof(builder);
}

std::string Parser::parseString()
{
    skipWhitespace();
    char c;
    std::string builder;
    consume('"');

    while (!atEnd() && peek() != '"')
    {
        c = advance();
        builder += c;
    }

    consume('"');
    return builder;
}

Component* Parser::parseComponent()
{
    std::string componentTitle = Parser::parseString();
    skipWhitespace();
    Parser::consume(':');
    skipWhitespace();
    Parser::consume('{');
    if (componentTitle == "Sprite")
    {
        return Sprite::deserialise(); 
    }
    else if (componentTitle == "BoxBounds")
    {
        return BoxBounds::deserialise();
    }
    else 
    {
        std::cout << "Couldn't find component '" << componentTitle << "' at line " << Parser::line << std::endl;
        exit(-1);
    }
    return nullptr;
}

GameObject* Parser::parseGameObject()
{
    if (length == 0 || atEnd())
    {
        return nullptr;
    }

    if (peek() == ',')  Parser::consume(',');

    skipWhitespace();

    if (atEnd()) 
    {
        return nullptr;
    }

    return GameObject::deserialise();
}

void Parser::consumeBeginObjectProperty(std::string name)
{
    skipWhitespace();
    checkString(name);
    skipWhitespace();
    consume(':');
    skipWhitespace();
    consume('{');
}

void Parser::consumeEndObjectProperty()
{
    skipWhitespace();
    consume('}');
}

std::string Parser::consumeStringProperty(std::string name)
{
    skipWhitespace();
    checkString(name);
    consume(':');
    return parseString();
}

int Parser::consumeIntProperty(std::string name)
{
    skipWhitespace();
    checkString(name);
    consume(':');
    return parseInt();
}

float Parser::consumeFloatProperty(std::string name)
{
    skipWhitespace();
    checkString(name);
    consume(':');
    return parseFloat();
}

bool Parser::consumeBoolProperty(std::string name)
{
    skipWhitespace();
    checkString(name);
    consume(':');
    return parseBool();
}


int Parser::offset = 0; 
int Parser::line = 1; 
int Parser::length = 0;
//std::string Parser::contents = "";
char* Parser::characters = nullptr;


