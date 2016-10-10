#ifndef __STRING_UTIL_H_
#define __STRING_UTIL_H_

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include "cocos2d.h"

USING_NS_CC;

namespace StringUtil
{

std::string trimLeft(const std::string& str);
std::string trimRight(const std::string& str);
std::string trim(const std::string& str);

std::string toLower(const std::string& str);
std::string toUpper(const std::string& str);

bool startsWith(const std::string& str, const std::string& substr);
bool endsWith(const std::string& str, const std::string& substr);
bool equalsIgnoreCase(const std::string& str1, const std::string& str2);


CCPoint toVecs(const std::string& val);

CCRect toRect(const std::string& val);


template<class T> T parseString(const std::string& str);
template<int> int parseString(const std::string& str);

template<class T> T parseHexString(const std::string& str);
template<bool> bool parseString(const std::string& str);

template<class T> std::string toString(const T& value);
template<int> std::string toString(const int& value);

template<class T> std::string toHexString(const T& value, int width = 0);
//std::string toString(const bool& value);

std::vector<std::string> split(const std::string& str, const std::string& delimiters);

std::string replaceAll(std::string& str, const std::string& pattern, const std::string& replaceWith);

int getNumChars(const std::string& s);

std::string getFitString(const std::string& str, int len);

}

namespace StringUtil
{

class Tokenizer
{
public:
	static const std::string DEFAULT_DELIMITERS;
	Tokenizer(const std::string& str);
	Tokenizer(const std::string& str, const std::string& delimiters);

	bool nextToken();
	bool nextToken(const std::string& delimiters);
	const std::string getToken() const;

	/**
	* to reset the tokenizer. After reset it, the tokenizer can get
	* the tokens from the first token.
	*/
	void reset();

protected:
	size_t m_Offset;
	const std::string m_String;
	std::string m_Token;
	std::string m_Delimiters;
};

}

namespace StringUtil
{

template<bool>
bool parseString(const std::string& str) {
	bool value;
	std::istringstream iss(str);
	iss >> std::boolalpha >> value;
	return value;
}

/*
std::string toString(const bool& value) {
	std::ostringstream oss;
	oss << std::boolalpha << value;
	return oss.str();
}*/

template<class T> T parseString(const std::string& str) {
	T value;
	std::istringstream iss(str);
	iss >> value;
	return value;
}

template<int> int parseString(const std::string& str) { 
//	int value;
	return atoi(str.c_str());
}


template<class T> T parseHexString(const std::string& str) {
	T value;
	std::istringstream iss(str);
	iss >> std::hex >> value;
	return value;
}

template<class T> std::string toString(const T& value) {
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template<int> std::string toString(const int& value) {
	char str[100] = {0};
	sprintf(str, "%d", value);
	return std::string(str);
}

template<class T> std::string toHexString(const T& value, int width) {
	std::ostringstream oss;
	oss << std::hex;
	if (width > 0) {
		oss << std::setw(width) << std::setfill('0');
	}
	oss << value;
	return oss.str();
}


void spit2Int(const std::string val,std::vector<int>& data,std::string spit);

void spit2Float(const std::string val,std::vector<float>& data, std::string spit);

}





#endif
