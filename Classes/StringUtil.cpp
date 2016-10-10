#include "StringUtil.h"
#include <algorithm>
#include <ctype.h>

using namespace std;

namespace StringUtil
{

const string Tokenizer::DEFAULT_DELIMITERS(" ");

Tokenizer::Tokenizer(const std::string& str)
	: m_String(str), m_Offset(0), m_Delimiters(DEFAULT_DELIMITERS) {}

Tokenizer::Tokenizer(const std::string& str, const std::string& delimiters)
	: m_String(str), m_Offset(0), m_Delimiters(delimiters) {}

bool Tokenizer::nextToken() {
	return nextToken(m_Delimiters);
}

bool Tokenizer::nextToken(const std::string& delimiters) {
	// find the start charater of the next token.
	size_t i = m_String.find_first_not_of(delimiters, m_Offset);
	if (i == string::npos) {
		m_Offset = m_String.length();
		return false;
	}

	// find the end of the token.
	size_t j = m_String.find_first_of(delimiters, i);
	if (j == string::npos) {
		m_Token = m_String.substr(i);
		m_Offset = m_String.length();
		return true;
	}

	// to intercept the token and save current position
	m_Token = m_String.substr(i, j - i);
	m_Offset = j;
	return true;
}

const string Tokenizer::getToken() const {
	return m_Token;
}

void Tokenizer::reset() {
	m_Offset = 0;
}

string trimLeft(const string& str) {
	string t = str;
	t.erase(0, t.find_first_not_of(" \t\n\r"));
	return t;
}

string trimRight(const string& str) {
	string t = str;
	t.erase(t.find_last_not_of(" \t\n\r") + 1);
	return t;
}

string trim(const string& str) {
	string t = str;
	t.erase(0, t.find_first_not_of(" \t\n\r"));
	t.erase(t.find_last_not_of(" \t\n\r") + 1);
	return t;
}

string toLower(const string& str) {
	string t = str;
	transform(t.begin(), t.end(), t.begin(), ::tolower);
	return t;
}

string toUpper(const string& str) {
	string t = str;
	transform(t.begin(), t.end(), t.begin(), ::toupper);
	return t;
}

bool startsWith(const string& str, const string& substr) {
	return str.find(substr) == 0;
}

bool endsWith(const string& str, const string& substr) {
	return str.rfind(substr) == (str.length() - substr.length());
}

bool equalsIgnoreCase(const string& str1, const string& str2) {
	return toLower(str1) == toLower(str2);
}

std::vector<std::string> split(const std::string& str, const std::string& delimiters) {
	std::vector<std::string> ss;

	Tokenizer tokenizer(str, delimiters);
	while (tokenizer.nextToken()) {
		ss.push_back(tokenizer.getToken());
	}

	return ss;
}

std::string replaceAll(std::string& str, const std::string& pattern, const std::string& replaceWith)
{
	std::string output = str;
	const size_t nsize = replaceWith.size();
	const size_t psize = pattern.size();

	for(size_t pos = output.find(pattern, 0);
			pos != std::string::npos;
			pos = output.find(pattern , pos + nsize))
	{
		output.replace(pos, psize, replaceWith);
	}

	return output;
}

int getNumChars(const std::string& s) {
	const char * pszText = s.c_str();
	int n = 0;
	char ch = 0;
	while ((ch = *pszText))
	{
		if(!ch)
		{
			break;
		}

		if (0x80 != (0xC0 & ch))
		{
			++n;
		}
		++pszText;
	}

	return n;
}

std::string getFitString(const std::string& str, int len)
{
	if(str.size() <= len)
	{
		return str;
	}

	int lastFitPos = 0;

	int j = 0;
    for (int i = 0; i < str.size(); i = j + 1)
    {
        char c = str.at(i);
        
        j = i;
        while(j+1 < str.size())
        {
            unsigned char nextChar = str.at(j+1);
            if((nextChar >> 6 ) == 0x2)
            {
                j++;
            }
            else
            {	
            	//find next utf-8 char boundary
                break;
            }
        }

        
        if(j < len)
        {
        	lastFitPos = j;
        }
        else
        {
        	break;
        }
	}

	std::string s;
    for(int k = 0; k <= lastFitPos; k++)
    {
        char ch = str.at(k);
        s.append(1, ch);
    } 	

	if(lastFitPos < len)
	{
		s += "..";
	}
	
	return s;
}

CCPoint toVecs(const std::string& val)
{
	float pos[2] = {0,0};

	std::vector<std::string> strlist = split(val,",");

	for(int i=0;i<strlist.size();++i)
	{
		pos[i] = parseString<float>( strlist[i] );
	}

	return ccp(pos[0],pos[1]);
}


CCRect toRect(const std::string& val)
{
	float pos[4] = {0,0,0,0};

	std::vector<std::string> strlist = split(val,",");

	for(int i=0;i<strlist.size();++i)
	{
		pos[i] = parseString<float>( strlist[i] );
	}

	return CCRect(pos[0],pos[1],pos[2],pos[3]);
}


void spit2Int(const std::string val,std::vector<int>& data, std::string spit)
{
	data.clear();

	std::vector<std::string> databuf = StringUtil::split(val, spit );

	for( int i=0;i< databuf.size();++i )
	{
		data.push_back( StringUtil::parseString<int> (databuf[i]) );
	}
}

void spit2Float(const std::string val,std::vector<float>& data, std::string spit)
{
	data.clear();

	std::vector<std::string> databuf = StringUtil::split(val, spit );

	for( int i=0;i< databuf.size();++i )
	{
		data.push_back( StringUtil::parseString<float> (databuf[i]) );
	}
}







}
